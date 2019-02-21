#ifndef STRUCTDISK_H_INCLUDED
#define STRUCTDISK_H_INCLUDED

#include "mlist.h"
#include "string.h"

typedef struct Disk Disk;
typedef struct Part Part;

MList * mounted = NULL;

struct Disk
{
    char * path;
    char letter;
    MList * Partitions;
};

struct Part
{
    char * name;
    int serie;
};

Disk * newDisk ()
{
    Disk * disk = (Disk *)malloc(sizeof(Disk));
    disk->letter = '\0';
    disk->path = NULL;
    disk->Partitions = NULL;

    return disk;
}

Part * newPart()
{
    Part * partition = (Part *)malloc(sizeof(Part));
    partition->name = NULL;
    partition->serie = 0;

    return partition;
}

/* COMPARA LETRA DE DISCO */
int compareDiskLetter (void * disk1, void * letter)
{
    if (((Disk *)disk1)->letter > ((char *)letter)[0])
        return 1;
    if (((Disk *)disk1)->letter < ((char *)letter)[0])
        return -1;
    return 0;
}

/* COMPARA NUMERO DE PARTICION */
int comparePartitionSerial (void * part, void * serial)
{
    if (((Part *)part)->serie > *((int *)serial))
        return 1;
    if (((Part *)part)->serie < *((int *)serial))
        return -1;
    return 0;
}

/* COMPARAR PATH DE DISCO */
int compareDiskPath (void * disk, void * path)
{
    int cmp = strcmp(((Disk *)disk)->path, (char *)path);

    return (cmp > 0) ? 1: (cmp < 0) ? -1 : 0;
}

/* COMPARAR NOMBRE DE PARTICION */
int comparePartitionName (void * part, void * name)
{
    int cmp = strcmp(((Part *)part)->name, (char *)name);

    return (cmp > 0) ? 1 : (cmp < 0) ? -1 : 0;
}

#endif // STRUCTDISK_H_INCLUDED