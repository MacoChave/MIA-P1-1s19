#ifndef CMDRMDISK_H_INCLUDE
#define CMDRMDISK_H_INCLUDE

#include "../file_manager/manager.h"
#include "../struct/mlist.h"
#include "../struct/parameter.h"

void exec_rmdisk (MList ** parameters)
{
    char select = 'n';
    char * path;

    while((*parameters)->size > 0)
    {
        Parameter * param = (Parameter *)pop_back(parameters);
        if (param->type == _PATH_)
        {
            if (param->data_type == _STRING_)
            {
                path = (char *)malloc(strlen(param->value));
                memset(path, 0, strlen(param->value));
                strcpy(path, param->value);
            }
            else
                printf("* ERROR: Path debe ser String\n");
        }

        deleteParameter(&param);
        param = NULL;
    }

    if (path == NULL)
    {
        printf("* ERROR: Path es requerido\n");
        return;
    }
    
    if (!existDisk(path))
    {
        printf("* ERROR: El diso no existe\n");
        free(path);
        return;
    }
    
    printf("¿Eliminar el disco? s/n\n");
    scanf("%c", &select);
    fflush(stdin);

    if (select == 's') deleteDisk(path);
    free(path);
    path = NULL;
}

#endif // CMDRMDISK_H_INCLUDE