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
    char *filename;
    enum filetype type;

    union {
        int size;
        struct fileinfo *subdir;

    };
};

#endif // FILEINFO_H