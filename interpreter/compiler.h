#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../struct/mlist.h"
#include "../struct/parameter.h"
#include "../globalvar/global.h"
#include "../command/cmdmkdisk.h"
#include "../command/cmdrmdisk.h"
#include "../command/cmdfdisk.h"
#include "../command/cmdmount.h"
#include "../command/cmdrep.h"

/* INTERPRETAR TIPO DE COMANDO */
int getCommandNumber (char * name)
{
    if (strcasecmp(name, "exec") == 0)
        return _EXEC_;
    if (strcasecmp(name, "mkdisk") == 0)
        return _MKDISK_;
    if (strcasecmp(name, "rmdisk") == 0)
        return _RMDISK_;
    if (strcasecmp(name, "fdisk") == 0)
        return _FDISK_;
    if (strcasecmp(name, "mount") == 0)
        return _MOUNT_;
    if (strcasecmp(name, "unmount") == 0)
        return _UNMOUNT_;
    if (strcasecmp(name, "rep") == 0)
        return _REP_;
    return -1;
}

/* INTERPRETAR TIPO DE PARAMETRO */
int getParameterNumber (char * param)
{
    if (strcasecmp(param, "size") == 0)
        return _SIZE_;
    if (strcasecmp(param, "path") == 0)
        return _PATH_;
    if (strcasecmp(param, "unit") == 0)
        return _UNIT_;
    if (strcasecmp(param, "name") == 0)
        return _NAME_;
    if (strcasecmp(param, "type") == 0)
        return _TYPE_;
    if (strcasecmp(param, "fit") == 0)
        return _FIT_;
    if (strcasecmp(param, "delete") == 0)
        return _DELETE_;
    if (strcasecmp(param, "add") == 0)
        return _ADD_;
    if (strcasecmp(param, "id") == 0)
        return _ID_;
    return -1;
}

char * getValue (char * val, int * type_value)
{
    char * value = (char *)malloc(strlen(val));
    memset(value, 0, strlen(val));
    strcpy(value, val);

    if (*type_value == _CHAR_)
        *type_value = (strlen(val) > 1) ? _STRING_ : _CHAR_;
    
    return value;
}

MList * automaton (char * line, int * cmd_type)
{
    int param = 0;
    char * value = NULL;

    MList * parameters = newMList();

    // size_t _SIZE_STRING_ = sizeof(char) * 125;
    char * temp = (char *)malloc(_SIZE_STRING_);
    memset(temp, 0, _SIZE_STRING_);

    int step = 0; // 0:TYPE 1:PARAMETER 2:VALUE
    int type_value = _INT_;
    int quotation_marks = -1; // -1:FALSE 1:TRUE

    char * s = line;
    while (*s)
    {
        if (*s == '#')
        {
            memset(temp, 0, _SIZE_STRING_);
            break;
        }
        if (*s == '\n' || *s == '\r')
        {
            s++;
            continue;
        }

        if (step == 0) // TIPO DE COMANDO
        {
            if (*s != ' ')
            {
                sprintf(temp, "%s%c", temp, tolower(*s));
                s++;
                continue;
            }
            else
            {
                *cmd_type = getCommandNumber(temp);
                if (*cmd_type < 0)
                    break;
                memset(temp, 0, _SIZE_STRING_);
                s += 2;
                step = 1;
            }
        }
        else if (step == 1) // PARAMETRO
        {
            if (*s == ':')
            {
                param = getParameterNumber(temp);
                memset(temp, 0, _SIZE_STRING_);
                s += 2;
                step = 2;
            }
            else if (*s != '~')
            {
                sprintf(temp, "%s%c", temp, tolower(*s));
                s++;
                continue;
            }
            else if (*s == '~')
            {
                s++;
                continue;
            }
        }
        else if (step == 2) // VALUE
        {
            if (*s == '\"')
            {
                quotation_marks *= -1;
                s++;
                continue;
            }

            if (*s != ' ')
            {
                sprintf(temp, "%s%c", temp, tolower(*s));
                type_value = ((isdigit(*s) || *s == '-' || *s == '.') && type_value == _INT_) ? _INT_ : _CHAR_;
                s++;
                continue;
            }
            else if (*s == ' ')
            {
                if (quotation_marks > 0)
                {
                    sprintf(temp, "%s%c", temp, tolower(*s));
                    s++;
                    continue;
                }
                else
                {
                    if (param >= 0 && strlen(temp) > 0)
                    {
                        value = getValue(temp, &type_value);
                        memset(temp, 0, _SIZE_STRING_);
                        Parameter * parameter = newParameter(param, value, type_value);
                        push_back(&parameters, parameter);

                        free(value);
                        value = NULL;
                        type_value = 0;
                    }
                    s += 2;
                    step = 1;
                    continue;
                }
                
            }
        }
    }

    if (param >= 0 && strlen(temp) > 0)
    {
        value = getValue(temp, &type_value);
        memset(temp, 0, _SIZE_STRING_);
        Parameter * parameter = newParameter(param, value, type_value);
        push_back(&parameters, parameter);

        free(value);
        value = NULL;
    }

    free(temp);
    temp = NULL;

    return parameters;
}

/* EJECUTAR COMANDO */
void execute (int cmd_type, MList ** parameters)
{
    printf("\n\tCOMANDO: %d\t\n", cmd_type);
    switch (cmd_type)
    {
        case _MKDISK_:
            /* CREAR DISCO */
            exec_mkdisk(parameters);
            break;
        case _RMDISK_:
            /* ELIMINAR DISCO */
            exec_rmdisk(parameters);
            break;
        case _FDISK_:
            /* EDITAR PARTICIONES */
            exec_fdisk(parameters);
            break;
        case _MOUNT_:
            /* MONTAR PARTICIONES */
            exec_mount(parameters);
            break;
        case _UNMOUNT_:
            /* DESMONTAR PARTICIONES */
            break;
        case _REP_:
            /* CREAR REPORTES */
            exec_rep(parameters);
            break;
        default:
            break;
    }
}

/* ANALIZAR ARCHIVO */
void analizeFile (char * filename)
{
    FILE * file;

    if ((file = fopen(filename, "r")) == NULL)
        return;
    
    while(!feof(file)){
        MList * parameters = NULL;
        int cmd_type = 0;
        char string[200];
        memset(string, 0, 200);
        fgets(string, 200, file);
        parameters = automaton(string, &cmd_type);
        if (parameters->size > 0 && cmd_type > 0)
            execute(cmd_type, &parameters);
            
        free(parameters);
        parameters = NULL;
    }
    fclose(file);
}

/* ANALIZAR LINEA DE CODIGO */
void analizeLine (char * line)
{
    int cmd_type = -1;
    MList * parameters = automaton(line, &cmd_type);

    if (parameters->size == 0 || cmd_type < 0)
    {
        free(parameters);
        parameters = NULL;
        return;
    }
        
    if (cmd_type > _EXEC_)
        execute(cmd_type, &parameters);
    else if (cmd_type == _EXEC_)
    {
        char * filename = NULL;
        Parameter * param = (Parameter *)pop_front(&parameters);
        printf("%d: %s as %d\n", param->type, param->value, param->data_type);
        do
        {    
            if (param->type == _PATH_ && param->data_type == _STRING_)
            {
                filename = (char *)malloc(strlen(param->value));
                memset(filename, 0, strlen(param->value));
                strcpy(filename, param->value);
                deleteParameter(&param);
                param = NULL;
                break;
            }
            deleteParameter(&param);
            param = (Parameter *)pop_front(&parameters);
        } while (param != NULL);

        if (filename != NULL)
        {
            analizeFile(filename);
            free(filename);
            filename = NULL;
        }

        if (param != NULL)
        {
            deleteParameter(&param);
            param = NULL;
        }
    }

    free(parameters);
    parameters = NULL;
}

#endif // COMPILER_H_INCLUDED