#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

#include <string.h>
#include <stdlib.h>

typedef struct Parameter Parameter;

struct Parameter
{
    int type;
    char * value;
    int data_type;
};

Parameter * newParameter(int type, char * value, int data_type)
{
    Parameter * parameter = (Parameter *)malloc(sizeof(Parameter));
    
    parameter->type = type;
    parameter->value = (char *)malloc(strlen(value) + 1);
    strcpy(parameter->value, value);
    parameter->data_type = data_type;

    return parameter;
}

void deleteParameter(Parameter ** parameter)
{
    free((*parameter)->value);
    (*parameter)->value = NULL;
    (*parameter)->data_type = 0;
    (*parameter)->type = 0;
}

#endif // PARAMETERS_H_INCLUDED