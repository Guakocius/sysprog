
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fileinfo.h"

static fileinfo *list_directory(char *filename) {
    DIR *dir = opendir(filename);
    struct stat f_stat;
    lstat(filename, &f_stat);

    chdir(filename);
    fileinfo *info = malloc(sizeof(fileinfo));
    fileinfo *head = NULL, *tail = NULL;

    if (!chdir(filename)) {
        return NULL;
    }

    if (!info) {
        fprintf(stderr, "%s couldn't be read! (%d)\n", filename, errno);
        return info = NULL;
    }
    memset(info, 0, sizeof(fileinfo));

    strcpy(info->filename, filename);

    const struct dirent *d;

    if (!dir) {
        fprintf(stderr, "%s:\t%d", strerror(errno), errno);
    }
    errno = 0;
    while ((d = readdir(dir)) != NULL) {

        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
            // info = info->next;
            continue;
        }
        fileinfo *info_next = fileinfo_create(d->d_name);

        if (!info_next)
            continue;

        if (!head) {
            head = tail = info_next;
        } else {
            tail->next = info_next;
            tail = info_next;
        }
    }
    if (errno != 0) {
        fprintf(stderr, "%d : Error : %s\n", errno, strerror(errno));
        closedir(dir);
        return info = NULL;
    }
    chdir("..");
    closedir(dir);
    return head;
}

static void print_regular(const char *filename, size_t size) {

    fprintf(stdout, "%s (%s, %zu %s)\n", filename, "regular", size, "Byte");
}
static void print_other(const char *filename) {
    printf("%s (other)\n", filename);
}

static void print_directory(char *path_relative, char *filename,
                            fileinfo *sub_dirs) {


    path_relative = calloc(sizeof(fileinfo), sizeof(filename));

    if (!path_relative) {
        fprintf(stderr, "%s\t%d\n", "Error: no allocated memory!", errno);
    }

    strcat(path_relative, "\0");
    strcpy(path_relative, filename);
    strcat(path_relative, "/");

    if (sub_dirs->next) {

        for (fileinfo *i = sub_dirs; i; i = i->next) {
            if (i->type == filetype_directory) {
                strcpy(i->filename, filename);
                strcat(path_relative, i->filename);


                print_directory(path_relative, i->filename, i->next);

            } else if (i->type == filetype_regular) {
                print_regular(i->filename, i->size);
            } else {
                print_other(i->filename);
            }
        }
        printf("%s:\n", path_relative);
    } else if (sub_dirs->subdir) {
        for (fileinfo *i = sub_dirs->subdir; i; i = i->subdir) {
            print_directory(path_relative, i->filename, i->subdir);
        }
    }
    free(path_relative);
}

void fileinfo_print(fileinfo *info) {
    errno = 0;

    // struct stat f_stat;

    if (info->type == filetype_regular) {
        size_t size = info->size;
        print_regular(info->filename, size);
    } else if (info->type == filetype_directory) {

        printf("%s:\n", info->filename);
        if (info->subdir) {

            // lstat(info->subdir->filename, &f_stat);
            print_directory("", info->filename, info->subdir);
        }
    } else if (info->type == filetype_other) {
        print_other(info->filename);
    }
}

void fileinfo_destroy(fileinfo *info) {

    if (info->type == filetype_regular) {
        for (fileinfo *i = info; i; i = info->next) {

            free(info->next);
        }
    } else if (info->type == filetype_directory) {
        while (info->subdir) {
            fileinfo_destroy(info->subdir);
        }
    }
    free(info);
}

fileinfo *fileinfo_create(const char *filename) {

    fileinfo *info = malloc(sizeof(fileinfo));
    struct stat f_stat;

    if (!info) {
        fprintf(stderr, "No allocation done, %d %s", errno, strerror(errno));
        return NULL;
    }

    memset(info, 0, sizeof(fileinfo));

    strcpy(info->filename, filename);
    lstat(filename, &f_stat);

    if (!filename) {
        free(info);
        return NULL;
    } else if (strlen(filename) > NAME_MAX) {
        errno = ENAMETOOLONG;
        free(info);
        return NULL;
    } else {
        if (S_ISREG(f_stat.st_mode)) {

            info->type = filetype_regular;
            info->size = f_stat.st_size;
        } else if (S_ISDIR(f_stat.st_mode)) {
            info->type = filetype_directory;
            info->subdir = list_directory(info->filename);
        } else {
            printf("Other!\n");
            info->type = filetype_other;
        }
    }
    return info;
}