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

int createDirectory (char * filename)
{
    char * dir = getDirectoryPath(filename);
    size_t size = strlen(filename) + sizeof(char) * 20;
    char * cmd = (char *)malloc(size);
    memset(cmd, 0, size);
    strcpy(cmd, "sudo mkdir -m 777 -p \"");
    strcat(cmd, dir);
    strcat(cmd, "\"");

    int res = (system(cmd) == 0) ? 1 : 0;

    return res;
}

int createDisk (char * filename, int size)
{
    FILE * file;

    if ((file = fopen(filename, "wb")) == NULL)
        return 0;
    
    char buffer[_KILOBYTE_];
    memset(buffer, '\0', _KILOBYTE_);

    for(int i = 0; i < size / _KILOBYTE_; i++)
    {
        fwrite(buffer, sizeof(buffer), 1, file);
        fflush(file);
    }

    fclose(file);
    return 1;
}

int deleteDisk (char * filename)
{
    return (remove(filename) == 0) ? 1 : 0;
}

#endif // MANAGER_H_INCLUDED