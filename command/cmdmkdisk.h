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
                memset(path, 0, strlen(param->value));
                strcpy(path, param->value);
            }
            else
                printf("* ERROR: Path debe ser string\n");
        }
        else if (param->type == _SIZE_)
        {
            if (param->data_type == _INT_)
                size = atoi(param->value);
            else
                printf("* ERROR: Size debe ser int\n");
        }
        else if (param->type == _FIT_)
        {
            if (param->data_type == _STRING_)
                fit = param->value[0];
            else
                printf("* ERROR: Fit debe ser String\n");
            
        }
        else if (param->type == _UNIT_)
        {
            if (param->data_type == _CHAR_)
                unit = param->value[0];
            else
                printf("* ERROR: Unit debe ser char\n");
        }

        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL || size < 0)
    {
        printf("* ERROR: Path o Size son requeridos\n");
        if (path != NULL) free(path);
        return;
    }
    
    if (unit == 'k')
        size *= _KILOBYTE_;
    else if (unit == 'm')
        size *= _MEGABYTE_;
    else 
        size *= _KILOBYTE_;

    if (!createDirectory(path))
    {
        printf("* ERROR: No se pudo crear el directorio\n");
        free(path);
        return;
    }
    
    if (existDisk(path))
    {
        printf("* ERROR: El disco ya existe\n");
        free(path);
        return;
    }
    
    if (!createDisk(path, size))
    {
        printf("* ERROR: No se pudo crear el disco\n");
        free(path);
        return;
    }
    
    mbr = newMBR(size);
    updateMBR(path, &mbr);

    free(path);
}

#endif // CMDMKDISK_H_INCLUDED