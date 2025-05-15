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
struct fileinfo *fileinfo_create(const char* filename);
static struct fileinfo *list_directory(const char *filename);

typedef struct fileinfo fileinfo;
#endif // FILEINFO_H