//
// Created by mos on 24.12.17.
//

#include        <stdio.h>
#include        <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    int iChars = 0, iWords = 0, iLines = 0;
    int ch;
    int previousCh;
    /* if there is a command line arg, then try to open it as the file
            otherwise, use stdin */
    fp = stdin;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[1]);
            exit(1);
        }
    }
    /* read until the end of file, counting chars, words, lines */
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            iLines++;
        }
        if (ch == '\t' || ch == ' ' || ch == '\n') {
            if(!(previousCh == '\t' || previousCh == ' ' || previousCh == '\n')) iWords++;
        }
        iChars++;
        previousCh = ch;
    }
    iWords++;
    if (fp != stdin) {
        fclose(fp);
    }
    printf("%d\t%d\t%d\n", iLines, iWords, iChars);
}