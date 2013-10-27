#ifndef _DIR_H
#define _DIR_H

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

char *print_folder(char *path);
void read_folder(char *path, char **contenu);
void upfile();

#endif /* _DIR_H */
