//
// Created by slava on 04.12.17.
//

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

static char hex2bin(char c) {
    switch (c) {
        default:
            return c - '0';
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
    }
}

int main(int argc, char **argv) {
    char allow_line_feed = 1;
    char escapes = 0;
    --argc;
    ++argv;

    while (argc > 0 && *argv[0] == '-') {
        char const *temp = argv[0] + 1;
        switch (*temp) {
            case 'e':
                escapes = 1;
                break;
            case 'E':
                escapes = 0;
                break;
            case 'n':
                allow_line_feed = 0;
                break;
            default:
                goto just_echo;
        }
        argc--;
        argv++;
    }

    just_echo:

    if (escapes) {
        while (argc > 0) {
            char const *s = argv[0];
            char c;
            while ((c = *s++)) {
                if (c == '\\' && *s) {
                    switch (c = *s++) {
                        case 'a':
                            c = '\a';
                            break;
                        case 'b':
                            c = '\b';
                            break;
                        case 'c':
                            exit(0);
                        case 'e':
                            c = '\x1B';
                            break;
                        case 'f':
                            c = '\f';
                            break;
                        case 'n':
                            c = '\n';
                            break;
                        case 'r':
                            c = '\r';
                            break;
                        case 't':
                            c = '\t';
                            break;
                        case 'v':
                            c = '\v';
                            break;
                        case 'x': {
                            char ch = *s;
                            if (!isxdigit (ch)) {
                                goto not_an_escape;
                            }
                            s++;
                            c = hex2bin(ch);
                            ch = *s;
                            if (isxdigit (ch)) {
                                s++;
                                c = c * 16 + hex2bin(ch);
                            }
                        }
                            break;
                        case '0':
                            c = 0;
                            if (!('0' <= *s && *s <= '7')) {
                                break;
                            }
                            c = *s++;
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                            c -= '0';
                            if ('0' <= *s && *s <= '7') {
                                c = c * 8 + (*s++ - '0');
                            }
                            if ('0' <= *s && *s <= '7') {
                                c = c * 8 + (*s++ - '0');
                            }
                            break;
                        case '\\':
                            break;

                        not_an_escape:
                        default:
                            putchar('\\');
                            break;
                    }
                }
                putchar(c);
            }
            argc--;
            argv++;
            if (argc > 0)
                putchar(' ');
        }
    } else {
        while (argc > 0) {
            fputs(argv[0], stdout);
            argc--;
            argv++;
            if (argc > 0) {
                putchar(' ');
            }
        }
    }

    if (allow_line_feed) {
        putchar('\n');
    }
    exit(0);
}