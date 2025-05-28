#ifndef FILEINFO_H
#define FILEINFO_H

#include <stdlib.h>
#include <linux/limits.h>



enum filetype {
    filetype_regular,
    filetype_directory,
    filetype_other
};

struct fileinfo {
    struct fileinfo *next;
    char filename[NAME_MAX + 1];
    enum filetype type;

    union {
        size_t size;
        struct fileinfo *subdir;

    };
};

void fileinfo_print(struct fileinfo *f);

void fileinfo_destroy(struct fileinfo *f);
struct fileinfo *fileinfo_create(const char* filename);


typedef struct fileinfo fileinfo;
#endif // FILEINFO_H