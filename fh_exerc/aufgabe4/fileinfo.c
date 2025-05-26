
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "fileinfo.h"

struct stat file_stat;

static fileinfo *list_directory(char *filename) {
    DIR *dir = opendir(filename);
    fileinfo *info = malloc(sizeof(fileinfo));
    fileinfo *head = NULL, *tail = NULL;
    memset(info, 0, sizeof(fileinfo));

    strcpy(info->filename, filename);

    if (!info) {
       fprintf(stderr, "%s couldn't be read! (%d)\n", filename, errno);
       return info = NULL;

    }
    const struct dirent *d;

    if (info == NULL) {
        return NULL;
    }

    while (dir) {
        /*if (S_ISDIR(file_stat.st_mode)) {
            chdir(info->filename);
        }*/
        errno = 0;
        if ((d = readdir(dir)) != NULL) {

            if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
                //info = info->next;
                continue;
            }
            chdir(info->filename);
            info->subdir = fileinfo_create(d->d_name);

            if (!info->subdir) continue;

            if (!head) {
                head = info;
                head->next = info->subdir;
                printf("Head:\t%s\n\n",head->filename);
            } else {
                tail = head->next;
                //info->subdir = tail;
                printf("Tail:\t%s\n\n",tail->filename);
            }
        } else {
            if (errno != 0) {
                fprintf(stderr, "%d : Error : %s\n", errno, strerror(errno));
                closedir(dir);
                return info->subdir = NULL;
            }
            chdir("..");
            return info->next;

        }
        return head;
    }
    chdir("..");
    closedir(dir);
    return head;
}

static void print_regular(char *filename, size_t size) {

    fprintf(stdout, "%s (%s %lu)\n", filename, "regular", size);

}
static void print_other(char *filename) {
    printf("%s (other)\n", filename);
}

static void print_directory(char *path_relative, char *filename, fileinfo *sub_dirs) {

    for (fileinfo *i = sub_dirs; i; i = i->next) {
        if (S_ISDIR(file_stat.st_mode)) {
            printf("%s (directory)\n", (char*)i);
            if (i->next == sub_dirs) {
                print_directory(path_relative, filename, i->next);
            }
        } if (S_ISREG(file_stat.st_mode)) {
            print_regular(filename, sub_dirs->size);
        } else {
            print_other(filename);
        }
    }
}

void fileinfo_print(fileinfo *info) {
    //printf("fileinfo_print_subdirs:\t%s\n",info->next->subdir->filename);
    //char *filename = info->filename;
    errno = 0;
    printf("Type:\t%d\n",info->type);
    printf("S_ISREG:\t%d\n", S_ISREG(file_stat.st_mode));
    //printf("cwd:\t%d\n",chdir(".."));
    //printf("Subdirs:\t%s\n",info->subdir->filename);

    if (info->type == filetype_regular) {
        printf("REG:\t%s\n",info->filename);
        size_t size = file_stat.st_size;
        print_regular(info->filename, size);

    } else if (info->type == filetype_directory) {

        printf("%s (directory)\n",info->filename);
        printf("Subdirs:\t%s\n",info->subdir->filename);
        if (info->subdir) {
            printf("%s\n%s\n",info->subdir->filename,getcwd(info->filename, sizeof(fileinfo)));
            printf("%s:\n", info->filename);
            print_directory(getcwd(info->filename, sizeof(fileinfo)), info->filename, info->subdir);
        } else {
            printf("No Subdirs:\t%s\n",info->filename);
        }



    } else if (info->type == filetype_other) {
        print_other(info->filename);
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

    if (!info) {
        fprintf(stderr, "No allocation done, %d %s", errno, strerror(errno));
        return NULL;
    }

    memset(info, 0, sizeof(fileinfo));

    strcpy(info->filename, filename);
    lstat(filename, &file_stat);

    if (!filename) {
        free(info);
        return NULL;
    } if (strlen(filename) > NAME_MAX) {
        errno = ENAMETOOLONG;
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
        } else if (S_ISDIR(file_stat.st_mode)) {
            info->type = filetype_directory;
            info->next = list_directory(info->filename);


        } else {
            info->type = filetype_other;

        }
    }
    return info;
}