//
// Created by mos on 24.12.17.
//

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct stat FileAttrib;
    if (argc == 3) {
        stat(argv[1], &FileAttrib);
        if ((FileAttrib.st_mode & S_IFMT) == S_IFDIR) printf("hard link not allowed for directory\n");
        else link(argv[1], argv[2]);
    }
    if (argc == 4 && strcmp(argv[1], "-s") == 0) {
        symlink(argv[2], argv[3]);
    }
}