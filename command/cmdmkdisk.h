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
            else
            {
                printf("Error: Tipo de dato en parámetro\n");
                return;
            }
        }
        else if (param->type == _SIZE_)
        {
            if (param->data_type == _INT_)
                size = atoi(param->value);
            else
            {
                printf("Error: Tipo de dato en size\n");
                return;
            }
        }
        else if (param->type == _FIT_)
        {
            if (param->data_type == _STRING_)
                fit = param->value[0];
            else
            {
                printf("Error: Tipo de dato en fit\n");
                continue;
            }
        }
        else if (param->type == _UNIT_)
        {
            if (param->data_type == _CHAR_)
                unit = param->value[0];
            else
            {
                printf("Error: Tipo de dato en unit\n");
                continue;
            }
        }
        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL || size < 0)
    {
        printf("Error: path o tamaño erroneo\n");
        return;
    }
    
    if (unit == 'k')
        size *= _KILOBYTE_;
    else if (unit == 'm')
        size *= _MEGABYTE_;
    else
    {
        size *= _KILOBYTE_;
        printf("Unidad no reconocida\n");
    }

    if (!createDirectory(path))
        return;
    
    if (existDisk(path))
        return;
    
    if (!createDisk(path, size))
        return;
    
    mbr = newMBR(size);
    if (!updateMBR(path, &mbr))
        printf("Error al actualizar MBR\n");
}

#endif // CMDMKDISK_H_INCLUDED