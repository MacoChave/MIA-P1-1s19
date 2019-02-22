#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/* TAMAÑO DE BYTES */
#define _KILOBYTE_ 1024
#define _MEGABYTE_ _KILOBYTE_ * 1024

/* EXTENSIONES */
#define _DISK_ 0
#define _PNG_ 1
#define _JPG_ 2
#define _PDF_ 3

/* SIZE STRING */
#define _SIZE_STRING_ sizeof(char) * 125
#define _LONG_STRING_ _SIZE_STRING * 2

/* TIPO DE DATO */
#define _INT_ 0
#define _CHAR_ 1
#define _STRING_ 2

/* TIPO DE COMANDO */
#define _EXEC_ 0
#define _MKDISK_ 1
#define _RMDISK_ 2
#define _FDISK_ 3
#define _MOUNT_ 4
#define _UNMOUNT_ 5
#define _REP_ 6

/* TIPO DE PARAMETRO */
#define _SIZE_ 0
#define _PATH_ 1
#define _UNIT_ 2
#define _NAME_ 3
#define _TYPE_ 4
#define _FIT_ 5
#define _DELETE_ 6
#define _ADD_ 7
#define _ID_ 8

#endif // GLOBAL_H_INCLUDED