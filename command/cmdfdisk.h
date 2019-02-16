#ifndef CMDFDISK_H_INCLUDED
#define CMDFDISK_H_INCLUDED

#include "../file_manager/manager.h"
#include "../struct/mlist.h"
#include "../struct/parameter.h"

typedef struct PartAdjust PartAdjust;

struct PartAdjust
{
    int start;
    int free_space;
    int free_after;
};

int existPartition (MBR mbr, char * name)
{
    for(int i = 0; i < 4; i++)
    {
        Partition part = mbr.partitions[i];
        if (strcasecmp(part.part_name, name) == 0)
            return 1;
    }

    return 0;
}

void selectFit (PartAdjust * adjusts, int * first, int * worst, int * best)
{
    if (adjusts[0].free_space >= 0)
        *first = 0;

    for(int i = 0; i < 4; i++)
    {
        if (*first < 0)
        {
            if (adjusts[i].free_after >= 0)
                *first = i;
        }
        if (adjusts[i].free_after < adjusts[*best].free_after)
            *best = i;
        if (adjusts[i].free_after > adjusts[*worst].free_after)
        {
            if (adjusts[i].free_after > 0)
                *worst = i;
        }
    }
}

PartAdjust * scanTableMBR (MBR mbr, int size, int * free_part, int * has_extended)
{
    PartAdjust * adjusts = (PartAdjust *)malloc(sizeof(PartAdjust) * 4);
    int pivote = sizeof(MBR);

    for(int i = 0; i < 4; i++)
    {
        if (!mbr.partitions[i].part_status)
            *free_part = i;
        else if (mbr.partitions[i].part_type == 'e')
            *has_extended = 1;
        
        PartAdjust adjust;
        adjust.start = pivote;
        adjust.free_space = mbr.partitions[i].part_start - pivote;
        adjust.free_after = adjust.free_space - size;
        adjusts[i] = adjust;
        pivote += adjust.free_space;
    }

    return adjusts;
}

MBR sortMBR (MBR mbr)
{
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (mbr.partitions[j].part_start > mbr.partitions[j + 1].part_start)
            {
                Partition p = mbr.partitions[j];
                mbr.partitions[j] = mbr.partitions[j + 1];
                mbr.partitions[j + 1] = p;
            }
        }
    }
    return mbr;
}

void deletePart (MBR mbr, char * path, char * name, char * del)
{
    if (!existPartition(mbr, name)) return;
}

void modifyPart(MBR mbr, char * path, char * name, int add, char unit)
{
    if (!existPartition(mbr, name)) return;
}

void createPart (MBR mbr, char * path, char * name, int size, char unit, char type, char fit)
{
    Partition part;
    int best = 0;
    int worst = 0;
    int first = -1;
    int free_part = -1;
    int has_extended = 0;
    if (size < 0) return;
    if (existPartition(mbr, name)) return;

    PartAdjust * adjusts = scanTableMBR(mbr, size, &free_part, &has_extended);
    selectFit(adjusts, &first, &worst, &best);

    if (free_part < 0) return;;
    if (first < 0) return;

    part.part_fit = fit;
    strcpy(part.part_name, name);
    part.part_size = size;
    part.part_status = 1;
    part.part_type = type;

    if (fit == 'f')
        part.part_start = adjusts[first].start;
    else if (fit == 'w')
        part.part_start = adjusts[worst].start;
    else if (fit == 'b')
     part.part_start = adjusts[best].start;

    mbr.partitions[free_part] = part;
    mbr = sortMBR (mbr);
    updateMBR(path, &mbr);
}

void exec_fdisk (MList ** parameters)
{
    Parameter * param;
    MBR mbr;
    int size = 0;
    char unit = 'k';
    char * path = NULL;
    char type = 'p';
    char fit = 'w';
    char * del = NULL;
    char * name = NULL;
    int add = 0;

    while((*parameters)->size > 0)
    {
        param = (Parameter *)pop_front(parameters);
        if (param->type == _SIZE_)
        {
            if (param->data_type == _INT_)
                size = atoi(param->value);
            else return;
        }
        else if (param->type == _UNIT_)
        {
            if (param->data_type == _CHAR_)
                unit = param->value[0];
        }
        else if (param->type == _PATH_)
        {
            if (param->data_type == _STRING_)
            {
                path = (char *)malloc(sizeof(param->value));
                strcpy(path, param->value);
            }
            else return;
        }
        else if (param->type == _TYPE_)
        {
            if (param->data_type == _CHAR_)
                type = param->value[0];
        }
        else if (param->type == _FIT_)
        {
            if (param->data_type == _STRING_)
                fit = param->value[0];
        }
        else if (param->type == _DELETE_)
        {
            if (param->data_type == _STRING_)
            {
                del = (char *)malloc(strlen(param->value));
                strcpy(del, param->value);
            }
        }
        else if (param->type == _NAME_)
        {
            if (param->data_type == _STRING_)
            {
                name = (char *)malloc(strlen(param->value));
                strcpy(name, param->value);
            }
            else return;
        }
        else if (param->type == _ADD_)
        {
            if (param->data_type == _INT_)
                add = atoi(param->value);
        }

        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL && name == NULL) return;

    if (!existDisk(path)) return;

    if (unit == 'k')
    {
        size *= _KILOBYTE_;
        add *= _KILOBYTE_;
    } 
    else if (unit == 'm')
    {
        size *= _MEGABYTE_;
        add *= _MEGABYTE_;
    }
    else
    {
        size *= _KILOBYTE_;
        add *= _KILOBYTE_;
    }

    mbr = getMBR(path);
    
    if (del != NULL) deletePart(mbr, path, name, del);
    else if (add != 0) modifyPart(mbr, path, name, add, unit);
    else createPart(mbr, path, name, size, unit, type, fit);
}

#endif // CMDFDISK_H_INCLUDED