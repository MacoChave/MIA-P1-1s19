#ifndef CMDREP_H_INCLUDED
#define CMDREP_H_INCLUDED

#include "../struct/disk.h"
#include "../struct/parameter.h"
#include "../file_manager/manager.h"

#define DIGRAPH_HEADER "digraph disco\n{\n\tnode [shape = plaintext]\n\tstruct [label = \n\t\t<\n<table border='1'>\n"
#define DIGRAPH_FOOTER "\t\t\t</table>\n\t\t>\n\t]\n}"

void compileDot (char * directory, char * name, int ext)
{
    if (ext == _JPG_)
        createReport(directory, name, "jpg");
    else if (ext == _PNG_)
        createReport(directory, name, "png");
    else if (ext == _PDF_)
        createReport(directory, name, "pdf");
}

int countExtendedFragmented (char * filename, int start)
{
    int count = 0;
    EBR ebr;

    do
    {
        ebr = getEBR(filename, start);
        count += 2;
        start = ebr.part_next;
    } while (ebr.part_next > 0);
    
    return count;
}

void mbrReport (MBR mbr, char * path, char * filename)
{
    int ebr_start = 0;

    char data[150];
    memset(data, 0, 150);

    strcpy(data, "<tr>\n\t<td colspan='2'>MBR</td>\n </tr>\n");
    updateFile(path, data);
    memset(data, 0, 150);

    strcpy(data, "<tr>\n\t<td>Size</td>\n");
    updateFile(path, data);
    memset(data, 0, 150);
    sprintf(data, "\t<td>%d</td>\n </tr>\n", mbr.size);
    updateFile(path, data);
    memset(data, 0, 150);

    strcpy(data, "<tr>\n\t<td>Created</td>\n");
    updateFile(path, data);
    memset(data, 0, 150);
    sprintf(data, "\t<td>%s</td>\n </tr>\n", mbr.mbr_fecha_creacion);
    updateFile(path, data);
    memset(data, 0, 150);

    strcpy(data, "<tr>\n\t<td>Signature</td>\n");
    updateFile(path, data);
    memset(data, 0, 150);
    sprintf(data, "\t<td>%d</td>\n </tr>\n", mbr.mbr_disk_signature);
    updateFile(path, data);
    memset(data, 0, 150);

    for(int i = 0; i < 4; i++)
    {
        if (mbr.partitions[i].part_type == 'e')
            ebr_start = mbr.partitions[i].part_start;

        sprintf(data, "<tr>\n\t<td colspan='2'>Particion: %s</td>\n </tr>\n", mbr.partitions[i].part_name);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Status</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", mbr.partitions[i].part_start);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Type</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%c</td>\n </tr>\n", mbr.partitions[i].part_type);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Fit</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%c</td>\n </tr>\n", mbr.partitions[i].part_fit);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Start</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", mbr.partitions[i].part_start);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Size</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", mbr.partitions[i].part_size);
        updateFile(path, data);
        memset(data, 0, 150);
    }

    if (ebr_start > 0)
    {
        EBR ebr = getEBR(filename, ebr_start);
        strcpy(data, "<tr>\n\t<td colspan='2'>EBR</td>\n </tr>\n");
        memset(data, 0, 150);
        updateFile(path, data);

        strcpy(data, "<tr>\n\t<td>Status</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", ebr.part_status);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Fit</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        strcpy(data, "\t<td>0</td>\n</tr>\n");
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Size</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", ebr.part_size);
        updateFile(path, data);
        memset(data, 0, 150);

        strcpy(data, "<tr>\n\t<td>Next</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>%d</td>\n </tr>\n", ebr.part_next);
        updateFile(path, data);
        memset(data, 0, 150);
    }
}

void diskReport (MBR mbr, char * path, char * filename)
{
    int hasExtended = 0;
    int percent_extended = 0;
    int pivot = sizeof(MBR);
    char data[150];
    memset(data, 0, 150);

    strcpy(data, "<tr>\n\t<td rowspan='2'>MBR</td>\n");
    updateFile(path, data);
    memset(data, 0, 150);

    for(int i = 0; i < 4; i++)
    {
        int free_space = mbr.partitions[i].part_start - pivot;
        int percent = free_space * 100 / mbr.size;

        if (percent > 0)
        {
            sprintf(data, "\t<td rowspan='2'>FREE %d %%</td>\n", percent);
            updateFile(path, data);
            memset(data, 0, 150);
            pivot = mbr.partitions[i].part_start;
        }
        
        if (mbr.partitions[i].part_size > 0)
        {
            percent = mbr.partitions[i].part_size * 100 / mbr.size;
            if (mbr.partitions[i].part_type == 'e')
            {
                hasExtended = 1;
                percent_extended = percent;
                sprintf(data, "\t<td colspan='2'>%s %d %%</td>\n", mbr.partitions[i].part_name, percent);
                updateFile(path, data);
                memset(data, 0, 150);
            }
            else
            {
                sprintf(data, "\t<td rowspan='2'>%s %d %%</td>\n", mbr.partitions[i].part_name, percent);
                updateFile(path, data);
                memset(data, 0, 150);
            }

            pivot = mbr.partitions[i].part_start + mbr.partitions[i].part_size;
        }
        else
            break;
    }
    updateFile(path, "</tr>\n");

    if (hasExtended)
    {
        strcpy(data, "<tr>\n\t<td>EBR</td>\n");
        updateFile(path, data);
        memset(data, 0, 150);
        sprintf(data, "\t<td>FREE %d %%</td>\n </tr>\n", percent_extended);
        updateFile(path, data);
        memset(data, 0, 150);
    }
}

void exec_rep (MList ** parameters)
{
    if (mounted == NULL)
    {
        printf("* ERROR: No hay particiones montadas\n");
        return;
    }
    char letter = '\0';
    int number = 0;
    char * path = NULL; // image path
    char * name = NULL; //mbr | disk
    MBR mbr;

    while((*parameters)->size > 0)
    {
        Parameter * param = (Parameter *)pop_front(parameters);
        if (param->type == _ID_)
        {
            if (param->data_type == _STRING_ && strlen(param->value) == 4)
            {
                letter = param->value[2];
                number = param->value[3] - '0';
            }
            else
                printf("* ERROR: Formato del id: vd[disk_letter][part_number]\n");
            
        }
        else if (param->type == _PATH_)
        {
            if (param->data_type == _STRING_)
            {
                path = (char *)malloc(strlen(param->value));
                memset(path, 0, strlen(param->value));
                strcpy(path, param->value);
            }
            else
                printf("* ERROR: path debe ser string\n");
            
        }
        else if (param->type == _NAME_)
        {
            if (param->data_type == _STRING_)
            {
                name = (char *)malloc(strlen(param->value));
                memset(name, 0, strlen(param->value));
                strcpy(name, param->value);
            }
            else
                printf("* ERROR: name debe ser string\n");
        }

        deleteParameter(&param);
        param = NULL;
    }
    
    if (path == NULL || name == NULL || letter == '\0' || number == 0)
    {
        if (path != NULL) free(path);
        if (name != NULL) free(name);
        printf("* ERROR: Requeridos path, name e id\n");
        return;
    }
    
    Disk * disk = (Disk *)get_item_unordered(mounted, &letter, compareDiskLetter);
    if (disk == NULL)
    {
        free(path);
        free(name);
        printf("* ERROR: Partición no montada\n");
        return;
    }
    mbr = getMBR(disk->path);

    createDirectory(path);
    char * directory = getDirectoryPath(path);
    char * name_file = getNamePath(path);
    int ext = getExtensionPath(path);
    memset(path, 0, strlen(path));
    sprintf(path, "%s/%s.dot", directory, name_file);

    createFile(path, DIGRAPH_HEADER);

    if (strcasecmp(name, "mbr") == 0)
        mbrReport(mbr, path, disk->path);
    else if (strcasecmp(name, "disk") == 0)
        diskReport(mbr, path, disk->path);
    else
        printf("* ERROR: Nombre no reconocido\n");
    
    updateFile(path, DIGRAPH_FOOTER);
    compileDot(directory, name_file, ext);

    free(path);
    free(name);
    free(directory);
    free(name_file);
}

#endif // CMDREP_H_INCLUDED