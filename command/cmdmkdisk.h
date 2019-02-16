#ifndef CMDMKDISK_H_INCLUDED
#define CMDMKDISK_H_INCLUDED

#include "../file_manager/manager.h"
#include "../struct/mlist.h"
#include "../struct/parameter.h"

void exec_mkdisk (MList ** parameters)
{
    char * path = NULL;
    int size = 0;
    char fit = 'f';
    char unit = 'm';
    MBR mbr;

    while ((*parameters)->size > 0)
    {
        Parameter * param = (Parameter *)pop_front(parameters);
        if (param->type == _PATH_)
        {
            if (param->data_type == _STRING_)
            {
                path = (char *)malloc(strlen(param->value));
                strcpy(path, param->value);
            }
            else return;
        }
        else if (param->type == _SIZE_)
        {
            if (param->data_type == _INT_)
                size = atoi(param->value);
            else return;
        }
        else if (param->type == _FIT_)
        {
            if (param->data_type == _STRING_)
                fit = param->value[0];
        }
        else if (param->type == _UNIT_)
        {
            if (param->data_type == _CHAR_)
                unit = param->value[0];
        }

        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL || size < 0) return;
    
    if (unit == 'k')
        size *= _KILOBYTE_;
    else if (unit == 'm')
        size *= _MEGABYTE_;
    else 
        size *= _KILOBYTE_;

    if (!createDirectory(path))
        return;
    
    if (existDisk(path))
        return;
    
    if (!createDisk(path, size))
        return;
    
    mbr = newMBR(size);
    updateMBR(path, &mbr);
}

#endif // CMDMKDISK_H_INCLUDED