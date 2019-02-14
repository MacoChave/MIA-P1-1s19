#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <stdio.h>
#include "../struct/info_disk.h"

char * getDirectoryPath (char * filename)
{
    char * s = filename;

    char * fileDir = (char *)malloc(strlen(filename));
    memset(fileDir, 0, strlen(filename));

    char * temp = (char *)malloc(strlen(filename));
    memset(temp, 0, strlen(filename));
    while(*s)
    {
        if (*s != '/' && *s != '.')
            sprintf(temp, "%s%c", temp, *s);
        else if (*s == '/')
        {
            strcat(fileDir, temp);
            memset(temp, 0, strlen(filename));
            strcpy(temp, "/");
        }
        else
            break;
        *s++;
    }
    free(temp);
    temp = NULL;

    return fileDir;
}

char * getName (char * filename)
{

}

char * getExtension (char * filename)
{
    
}

#endif // MANAGER_H_INCLUDED