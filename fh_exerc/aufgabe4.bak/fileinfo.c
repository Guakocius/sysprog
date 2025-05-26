
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "fileinfo.h"

struct stat file_stat;
enum filetype type;


static fileinfo *list_directory(const char *filename) {
    DIR *dir = opendir(filename);
    fileinfo *info = malloc(sizeof(fileinfo));
    info->filename = filename;
    chdir(info->filename);

    if (dir == NULL) {
       fprintf(stderr, "%s couldn't be read!", filename);
       return info = NULL;
    }
    errno = 0;
    const struct dirent *d;

    while ((d = readdir(dir)) != NULL) {

        //info->next = readdir(dir);
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
            info = info->next;
            continue;
        }
        printf("%s/%s\n", filename, d->d_name);
        info->next = fileinfo_create(filename);
    }

    if (errno) {
        fprintf(stderr, "%d : Error", errno);
        return info = NULL;

    }
    chdir("..");
    closedir(dir);

    return info;
}

static void print_regular(const char *filename, size_t size) {

    if (errno) {
        fprintf(stderr, "%s (errno %d)", strerror(errno), errno);
    }
    fprintf(stdout, "%s (%s %lu)\n", filename, "regular", size);

}
static void print_other(const char *filename) {
    printf("%s (other)\n", filename);
}

static void print_directory(const char *path_absolute, const char *filename, fileinfo *sub_dirs) {
    for (fileinfo *i = sub_dirs; i; i = sub_dirs->next) {
        if (S_ISDIR(file_stat.st_mode)) {
            printf("%s (directory)\n", (char*)i);
            if (i->next == sub_dirs) {
                print_directory(path_absolute, filename, i->next);
            }
        } if (S_ISREG(file_stat.st_mode)) {
            print_regular(filename, sub_dirs->size);
        } else {
            print_other(filename);
        }
    }
}

void fileinfo_print(fileinfo *info) {
    const char *filename = info->filename;

    if (info->type == filetype_regular) {
        size_t size = file_stat.st_size;
        print_regular(filename, size);

    } else if (info->type == filetype_directory) {
        const char *path_abs;
        path_abs = getcwd((char*)filename, PATH_MAX);

        fileinfo *sub_dirs = list_directory(filename);
        printf("%s:\n", (char*)info);
        print_directory(path_abs, filename, sub_dirs);

    } else if (info->type == filetype_other) {
        print_other(filename);
    }
}

void fileinfo_destroy(fileinfo *info) {

    if (S_ISREG(file_stat.st_mode)) {
        for (fileinfo *i = info; i != info->subdir; i = info->next) {
            free(info->subdir);
        }
    }
    free(info);
}

fileinfo *fileinfo_create(const char *filename) {

    fileinfo *info = malloc(sizeof(fileinfo));
    info->filename = filename;

    if (!filename || sizeof *filename > NAME_MAX + 1) {
        if (sizeof *filename > NAME_MAX + 1) {
            errno = ENAMETOOLONG;
        }
        free(info);
        return NULL;
    }
    lstat(filename, &file_stat);

    if (lstat(filename, &file_stat) == -1) {
        free(info);
        return NULL;
    } else {
        info->filename = filename;
        if (S_ISREG(file_stat.st_mode)) {
            info->type = filetype_regular;
            info->size = file_stat.st_size;
            //info = malloc(info->size);
        } else if (S_ISDIR(file_stat.st_mode)) {
            info->type = filetype_directory;
            info->next = list_directory(info->filename);


        } else {
            info->type = filetype_other;

        }
    }
    return info;
}