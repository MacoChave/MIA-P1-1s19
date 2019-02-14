#ifndef STRUCT_DISK_H_INCLUDED
#define STRUCT_DISK_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _KILOBYTE_ 1024
#define _MEGABYTE_ _KILOBYTE_ * 1024

typedef struct Partition Partition;
typedef struct MBR MBR;
typedef struct EBR EBR;

struct Partition
{
    int part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct MBR
{
    int size;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    Partition partitions[4];
};

struct EBR
{
    int part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

char * getCurrentDate ()
{
    time_t datetime = time(0);
    struct tm * tlocal = localtime(&datetime);
    static char date[18];
    strftime(date, 18, "%d/%m/%y %H:%M:%S", tlocal);

    return date;
}

int getRandom ()
{
    time_t t;
    srand((unsigned) time(&t));
    return rand() % 100;
}

Partition newPartition (int start)
{
    Partition part;
    part.part_status = 0;
    part.part_type = '\0';
    part.part_fit = '\0';
    part.part_start = start;
    part.part_size = 0;
    memset(part.part_name, 0, 16);
    strcpy(part.part_name, "free");

    return part;
}

MBR newMBR (int size)
{
    MBR mbr;
    mbr.size = size;
    memset(mbr.mbr_fecha_creacion, 0, 18);
    strcpy(mbr.mbr_fecha_creacion, getCurrentDate());
    mbr.mbr_disk_signature = getRandom();

    for(int i = 0; i < 4; i++)
        mbr.partitions[i] = newPartition(size);
    
    return mbr;
}

EBR newEBR(int start, int size)
{
    EBR ebr;
    ebr.part_status = 0;
    ebr.part_fit = '\0';
    ebr.part_start = start;
    ebr.part_size = size;
    ebr.part_next = -1;
    memset(ebr.part_name, 0, 16);

    return ebr;
}

#endif // STRUCT_DISK_H_INCLUDED