#ifndef STRUCT_DISK_H_INCLUDED
#define STRUCT_DISK_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <time.h>

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



#endif // STRUCT_DISK_H_INCLUDED