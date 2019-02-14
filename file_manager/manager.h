#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <stdio.h>
#include "../struct/info_disk.h"

#define _DISK_ 0
#define _PNG_ 1
#define _JPG_ 2

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
    char * s = filename;

    char * name = (char *)malloc(strlen(filename));
    memset(name, 0, strlen(filename));
    while(*s)
    {
        if (*s != '/')
            sprintf(name, "%s%c", name, *s);
        else if (*s == '/')
            memset(name, 0, strlen(filename));    
        *s++;
    }

    return name;
}

int getExtensionNumber (char * extension)
{
    if (strcmp(extension, "disk") == 0)
        return _DISK_;
    if (strcmp(extension, "dsk") == 0)
        return _DISK_;
    if (strcmp(extension, "png") == 0)
        return _PNG_;
    if (strcmp(extension, "jpeg") == 0)
        return _JPG_;
    return -1;
}

int getExtension (char * filename)
{
    char * s = filename;

    char * extension = (char *)malloc(strlen(filename));
    memset(extension, 0, strlen(filename));

    while(*s)
    {
        if (*s != '/' && *s != '.')
            sprintf(extension, "%s%c", extension, *s);
        else if (*s == '/' || *s == '.')
            memset(extension, 0, strlen(filename));
        
        *s++;
    }
    int extension_number = getExtensionNumber(extension);
    free(extension);
    extension = NULL;

    return extension_number;
}

#endif // MANAGER_H_INCLUDED