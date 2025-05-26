#ifndef FILEINFO_H
#define FILEINFO_H

#include <stdlib.h>



enum filetype {
    filetype_regular,
    filetype_directory,
    filetype_other
};

struct fileinfo {
    struct fileinfo *next;
    const char *filename;
    enum filetype type;

    union {
        size_t size;
        struct fileinfo *subdir;

    };
};

/*static void print_regular(const char *filename, size_t size);
static void print_directory(char *path_abs, const char *filename, struct fileinfo *sub_dirs);
static void print_other(const char *filename);*/
void fileinfo_print(struct fileinfo *f);

void fileinfo_destroy(struct fileinfo *f);
struct fileinfo *fileinfo_create(const char* filename);
//static struct fileinfo *list_directory(const char *filename);

typedef struct fileinfo fileinfo;
#endif // FILEINFO_H