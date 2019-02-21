#ifndef CMDMOUNT_H_INCLUDED
#define CMDMOUNT_H_INCLUDED

#include "../struct/disk.h"
#include "../struct/parameter.h"
#include "../file_manager/manager.h"

void pushDisk (Disk ** disk)
{
    Disk * disk1 = (Disk *)peek_back(mounted);
    (*disk)->letter = (disk1 == NULL) ? 'a' : disk1->letter++;

    push_back(&mounted, *disk);
}

void pushPart (MList * parts, Part *part)
{
    Part * part1 = (Part *)peek_back(parts);
    part->serie = (part1 == NULL) ? 1 : part1->serie++;

    push_back(&parts,part);
}

void mountPart (MBR mbr, char * path, char * name)
{
    int part_number = partitionNumber(mbr, name);
    if (part_number < 0)
    {
        printf("* ERROR: No existe la partición\n");
        return;
    }

    Disk * disk = (Disk *)get_item_unordered(mounted, name, compareDiskPath);
    if (disk == NULL)
    {
        disk = newDisk();
        disk->path = (char *)malloc(sizeof(path));
        memset(disk->path, 0, strlen(path));
        strcpy(disk->path, path);
        disk->Partitions = newMList();
        pushDisk(&disk);
    }
    Part * part = (Part *)get_item_unordered(disk->Partitions, name, comparePartitionName);
    if (part != NULL)
    {
        printf("* ERROR: Partición ya se encuentra montada\n");
        return;
    }
    part = newPart();
    part->name = (char *)malloc(sizeof(name));
    memset(part->name, 0, strlen(name));
    strcpy(part->name, name);
    pushPart(disk->Partitions, part);
}

void exec_mount (MList ** parameters)
{
    if (mounted == NULL)
        mounted = newMList();
    char * path = NULL;
    char * name = NULL;
    MBR mbr;

    while ((*parameters)->size > 0)
    {
        Parameter * param = (Parameter *)pop_front(parameters);
        if (param->type == _PATH_)
        {
            if (param->data_type == _STRING_)
            {
                path = (char *)malloc(strlen(param->value));
                memset(path, 0, strlen(param->value));
                strcpy(path, param->value);
            }
            else
                printf("* ERROR: Path debe ser string\n");
        }
        else if (param->type == _NAME_)
        {
            if (param->data_type == _STRING_)
            {
                name = (char *)malloc(strlen(param->value));
                memset(name, 0, strlen(param->value));
                strcpy(name, param->value);
            }
            else
                printf("* ERROR: Name debe ser string\n");
            
        }

        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL || name == NULL)
    {
        printf("* ERROR: PATH y NAME son requeridos\n");
        if (path != NULL) free(path);
        if (name != NULL) free(name);
        return;
    }

    if (!existDisk(path))
    {
        printf("* ERROR: El disco no existe\n");
        free(path);
        free(name);
        return;
    }

    mbr = getMBR(path);
    mountPart(mbr, path, name);

    free(path);
    free(name);
}

#endif // CMDMOUNT_H_INCLUDED