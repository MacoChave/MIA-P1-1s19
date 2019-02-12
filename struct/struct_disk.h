#ifndef STRUCT_DISK_H_INCLUDED
#define STRUCT_DISK_H_INCLUDED

#include "mlist.h"
#include "string.h"

typedef struct Disk Disk;
typedef struct Partition Partition;

struct Disk
{
    char * path;
    char letter;
    MList * Partitions;
};

struct Partition
{
    char * name;
    int serie;
};

Disk * newDisk ()
{
    Disk * disk = (Disk *)malloc(sizeof(Disk));
    disk->letter = '\0';
    disk->path = NULL;
    disk->Partitions = newMList();

    return disk;
}

Partition * newPartition()
{
    Partition * partition = (Partition *)malloc(sizeof(Partition));
    partition->name = NULL;
    partition->serie = 0;

    return partition;
}

/* COMPARA LETRO DE DISCO */
int compareDiskLetter (void * disk1, void * disk2)
{
    if (((Disk *)disk1)->letter > ((Disk *)disk2)->letter)
        return 1;
    if (((Disk *)disk1)->letter < ((Disk *)disk2)->letter)
        return 1;
    return 0;
}

/* COMPARA NUMERO DE PARTICION */
int comparePartitionSerial (void * partition1, void * partition2)
{
    if (((Partition *)partition1)->serie > ((Partition *)partition2)->serie)
        return 1;
    if (((Partition *)partition1)->serie < ((Partition *)partition2)->serie)
        return -1;
    return 0;
}

/* COMPARAR PATH DE DISCO */
int compareDiskPath (void * path, void * disk)
{
    int cmp = strcmp((char *)path, ((Disk *)disk)->path);

    return (cmp > 0) ? 1: (cmp < 0) ? -1 : 0;
}

/* COMPARAR NOMBRE DE PARTICION */
int comparePartitionName (void * name, void * partition)
{
    int cmp = strcmp((char *)name, ((Partition *)partition)->name);

    return (cmp > 0) ? 1 : (cmp < 0) ? -1 : 0;
}

#endif // STRUCT_DISK_H_INCLUDED