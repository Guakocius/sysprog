#include "fileinfo.h"

#include <linux/limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

struct stat file_stat;

static fileinfo *list_directory(const char *filename) {
    DIR *dir = opendir(filename);
    fileinfo *info = malloc(sizeof(fileinfo));
    if (dir == NULL) {
       fprintf(stderr, "%s couldn't be read!", filename);
       return info = NULL;
    }
    errno = 0;
    struct dirent *d;

    while ((d = readdir(dir)) != NULL) {
        printf("%s/%s\n", filename, d->d_name);
    }

    if (errno) {

    }
    if (closedir(dir) == - 1) {

    }

    return info;


}

fileinfo *fileinfo_create(const char *filename) {

    fileinfo *info = malloc(sizeof(fileinfo));
    info->filename = filename;
    //enum filetype type;

    if (!filename || sizeof *filename > NAME_MAX + 1) {
        if (sizeof *filename > NAME_MAX + 1) {
            errno = ENAMETOOLONG;
        }
        free(info);
        return NULL;
    }
    if (lstat(filename, &file_stat) == -1) {
        free(info);
        return NULL;
    } else {
        if (S_ISREG(file_stat.st_mode)) {
            info->type = filetype_regular;
            info->size = file_stat.st_size;
            //info = malloc(info->size);
        } else if (S_ISDIR(file_stat.st_mode)) {
            info->type = filetype_directory;


        } else {
            info->type = filetype_other;

        }
    }
}