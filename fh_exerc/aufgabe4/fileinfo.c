#include "fileinfo.h"

#include <linux/limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct fileinfo *fileinfo_create(const char *filename) {
    if (!filename || sizeof *filename > sizeof NAME_MAX) {
        if (*filename > sizeof NAME_MAX) {
            errno = ENAMETOOLONG;
        }
        return NULL;
    }
    
}