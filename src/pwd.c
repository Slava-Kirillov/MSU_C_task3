//
// Created by slava on 05.12.17.
//

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *path = getenv("PWD");

    if (!path || path[0] != '/')
        exit(1);
    while ((path = strstr(path, "/."))) {
        if (!path[2] || path[2] == '/' || (path[2] == '.' && (!path[3] || path[3] == '/')))
            exit(1);
        path++;
    }
    puts(path);
    exit(0);
}