//
// Created by slava on 05.12.17.
//

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *path = getenv("PWD");
    char *p = path;

    if (!p || p[0] != '/')
        exit(1);
    while ((p = strstr(p, "/."))) {
        if (!p[2] || p[2] == '/' || (p[2] == '.' && (!p[3] || p[3] == '/')))
            exit(1);
        p++;
    }
    puts(path);
    exit(0);
}