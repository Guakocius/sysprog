#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
struct stat file_stat;

int main() {
    lstat("listfiles-example-dir", &file_stat);

    printf("%d",S_ISDIR(file_stat.st_mode));

}