#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <stdio.h>
#include "../struct/info_disk.h"
#include "../globalvar/global.h"

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

char * getNamePath (char * filename)
{
    char * s = filename;

    char * name = (char *)malloc(strlen(filename));
    memset(name, 0, strlen(filename));
    while(*s)
    {
        if (*s != '/' && *s != '.')
            sprintf(name, "%s%c", name, *s);
        else if (*s == '/')
            memset(name, 0, strlen(filename));
        else if (*s == '.') break;
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
    if (strcmp(extension, "jpg") == 0)
        return _JPG_;
    if (strcmp(extension, "jpeg") == 0)
        return _JPG_;
    if (strcmp(extension, "pdf") == 0)
        return _PDF_;
    return -1;
}

int getExtensionPath (char * filename)
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

    int result = (system(cmd) == 0) ? 1 : 0;

    return result;
}

int createFile (char * filename, char * data)
{
    FILE * file;
    
    if ((file = fopen(filename, "w")) == 0)
        return 0;

    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}

int updateFile (char * filename, char * data)
{
    FILE * file;
    
    if ((file = fopen(filename, "a+")) == 0)
        return 0;

    fprintf(file, "%s", data);
    fclose(file);
    return 1;
}

void createReport (char * directory, char * name, char * ext)
{
    char cmd[125];
    memset(cmd, 0, 125);
    strcpy(cmd, "dot -T");
    strcat(cmd, ext);
    strcat(cmd, " ");
    strcat(cmd, directory);
    strcat(cmd, "/");
    strcat(cmd, name);
    strcat(cmd, ".dot -o ");
    strcat(cmd, directory);
    strcat(cmd, "/");
    strcat(cmd, name);
    strcat(cmd, ".");
    strcat(cmd, ext);
    printf("* CMD: %s\n", cmd);
    system(cmd);

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

int clearDisk (char * filename, int start, int size)
{
    FILE * file;

    if ((file = fopen(filename, "rb+")) == NULL)
        return 0;
    
    char buffer[_KILOBYTE_];
    memset(buffer, '\0', _KILOBYTE_);

    fseek(file, start, SEEK_SET);
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

int existDisk (char * filename)
{
    FILE * file;
    int result = 0;

    if ((file = fopen(filename, "r")) != NULL)
    {
        result = 1;
        fclose(file);
    }

    return result;
}

MBR getMBR (char * filename)
{
    MBR mbr = newMBR(0);
    FILE * file;
    if ((file = fopen(filename, "rb")) == NULL)
        return mbr;
    
    fread(&mbr, sizeof(MBR), 1, file);
    fclose(file);
    return mbr;
}

int updateMBR (char * filename, MBR * data)
{
    FILE * file;
    if ((file = fopen(filename, "rb+")) == NULL)
        return 0;
    
    fwrite(data, sizeof(MBR), 1, file);
    fclose(file);
    return 1;
}

EBR getEBR (char * filename, int start)
{
    EBR ebr = newEBR(0, 0);
    FILE * file;
    if ((file = fopen(filename, "rb")) == NULL)
        return ebr;
    
    fseek(file, start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, file);
    fclose(file);
    return ebr;
}

int updateEBR (char * filename, EBR * data, int pos)
{
    FILE * file;
    if ((file = fopen(filename, "rb+")) == NULL)
        return 0;
    
    fseek(file, pos, SEEK_SET);
    fwrite(data, sizeof(EBR), 1, file);
    fclose(file);
    return 1;
}

#endif // MANAGER_H_INCLUDED