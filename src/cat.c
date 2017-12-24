//
// Created by mos on 24.12.17.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *mf;
    char sym;
    int count = 0;
    --argc;
    ++argv;
    if (*argv[0] == '-'){
        --argc;
        ++argv;
        while (argc) {
            mf = fopen(argv[0], "r");
            if (mf == NULL) {printf ("ошибка\n"); return -1;}
            while (1) {
                sym = fgetc (mf);
                if (sym == EOF) {
                    if ( feof (mf) != 0) {
                        break;
                    }
                }
                if (count == 0) {
                    printf("%5d ", ++count);
                } else if (sym == '\n') {
                    printf ("%c",sym);
                    printf("%5d ", ++count);
                    continue;
                }
                printf ("%c",sym);
            }
            fclose (mf);
            --argc;
            ++argv;
            putchar('\n');
            printf("%5d ", ++count);
        }
    }else{
        while (argc){
            mf = fopen (argv[0],"r");
            if (mf == NULL) {printf ("ошибка\n"); return -1;}
            while (1) {
                sym = fgetc (mf);
                if (sym == EOF) {
                    if ( feof (mf) != 0) {
                        break;
                    }
                }
                printf ("%c",sym);
            }
            fclose (mf);
            --argc;
            ++argv;
            putchar('\n');
        }
    }
    return 0;
}