//
// Created by vkirillov on 07.12.17.
//

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>

void list_of_file(char *subfolder_path) {
    char *path = getenv("PWD");
//    char *path = "/home/vkirillov/CLionProjects/MSU_C_task3/src";
    char p[1024] = {"\0"};
    strcpy(p, path);
    if (subfolder_path != "") {
//        strcat(p, "/");
        strcat(p, subfolder_path);
    }
    DIR *dir = opendir(p);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat buf;
        if (entry->d_name[0] == '.')
            continue;
//        lstat(entry->d_name, &buf);
        if (entry->d_type == DT_DIR) {
            putchar('\033');
            fputs("[0;34m", stdout);
            putchar('\033');
            fputs("[1m", stdout);
        }
        fputs(entry->d_name, stdout);
        putchar('\033');
        fputs("[0m", stdout);
        printf("  ");
    }
//    putchar('\n');
    printf("\n\n");
    closedir(dir);
}

void list_of_file_with_param(char param_g, char param_l, char param_R, char *subfolder_path) {
    char targetName[PATH_MAX + 1];
    char *path = getenv("PWD");
//    char *path = "/home/vkirillov/CLionProjects/MSU_C_task3/src";
    char theDir[1024];
    strcpy(theDir, path);
    if (subfolder_path != "") {
//        strcat(theDir, "/");
        strcat(theDir, subfolder_path);
    }
    DIR *dir = opendir(theDir);
    struct dirent *entry;
    if (param_l) {
        while ((entry = readdir(dir)) != NULL) {
            struct stat buf;
            if (entry->d_name[0] == '.')
                continue;
            lstat(entry->d_name, &buf);
            switch ((buf.st_mode & S_IFMT)) {
                case S_IFBLK:
                    fputs("block device", stdout);
                    break;
                case S_IFCHR:
                    fputs("character device", stdout);
                    break;
                case S_IFDIR:
                    fputs("directory", stdout);
                    break;
                case S_IFIFO:
                    fputs("FIFO/pipe", stdout);
                    break;
                case S_IFLNK:
                    fputs("symlink", stdout);
                    break;
                case S_IFREG:
                    fputs("regular file", stdout);
                    break;
                case S_IFSOCK:
                    fputs("socket", stdout);
                    break;
                default:
                    fputs("unknown?", stdout);
                    break;
            }
            printf(" \t");
            putchar((buf.st_mode & S_IFDIR) ? 'd' : '-');
            putchar((buf.st_mode & S_IRUSR) ? 'r' : '-');
            putchar((buf.st_mode & S_IWUSR) ? 'w' : '-');
            putchar((buf.st_mode & S_IXUSR) ? 'x' : '-');
            putchar((buf.st_mode & S_IRGRP) ? 'r' : '-');
            putchar((buf.st_mode & S_IWGRP) ? 'w' : '-');
            putchar((buf.st_mode & S_IXGRP) ? 'x' : '-');
            putchar((buf.st_mode & S_IROTH) ? 'r' : '-');
            putchar((buf.st_mode & S_IWOTH) ? 'w' : '-');
            putchar((buf.st_mode & S_IXOTH) ? 'x' : '-');
            putchar('\t');
            struct passwd *pw = getpwuid(buf.st_uid);
            fputs(pw->pw_name, stdout);
            putchar('\t');
            printf("%ld", buf.st_size);
            putchar('\t');
            if (S_ISDIR(buf.st_mode)) {
                putchar('\033');
                fputs("[0;34m", stdout);
                putchar('\033');
                fputs("[1m", stdout);
            }
            fputs(entry->d_name, stdout);
            putchar('\033');
            fputs("[0m", stdout);
            if( readlink( entry->d_name, targetName, PATH_MAX ) != -1 ){
                printf( " -> %s", targetName );
            }
            putchar('\n');
        }
        closedir(dir);
    }
    if (param_g){
        while ((entry = readdir(dir)) != NULL) {
            struct stat buf;
            if (entry->d_name[0] == '.')
                continue;
            lstat(entry->d_name, &buf);
            struct group  *gr = getgrgid(buf.st_gid);
            fputs(gr->gr_name, stdout);
            putchar('\t');
            if (entry->d_type == DT_DIR) {
                putchar('\033');
                fputs("[0;34m", stdout);
                putchar('\033');
                fputs("[1m", stdout);
            }
            fputs(entry->d_name, stdout);
            putchar('\033');
            fputs("[0m", stdout);
            if( readlink( entry->d_name, targetName, PATH_MAX ) != -1 ){
                printf( " -> %s", targetName );
            }
            putchar('\n');
        }
        closedir(dir);
    }
    if (param_R){
        if (subfolder_path == "") {
            printf(".:\n");
        }else{
            printf(".%s:\n", subfolder_path);
        }
        list_of_file(subfolder_path);
        while ((entry = readdir(dir)) != NULL) {
            struct stat buf;
            if (entry->d_name[0] == '.')
                continue;
//            if (lstat(entry->d_name, &buf))
//                printf("Read file %s fault, %s\n",entry->d_name, strerror(errno));
            if (entry->d_type == DT_DIR){
                char sub[1024] = {"\0"};
                strcat(sub, subfolder_path);
                strcat(sub,"/");
                strcat(sub, entry->d_name);
                list_of_file_with_param(param_g, param_l, param_R, sub);
            }
        }
//        putchar('\n');
        closedir(dir);
    }
}

int main(int argc, char **argv) {
    --argc;
    ++argv;
    char param_R = 0;
    char param_l = 0;
    char param_g = 0;
    if (argc) {
        if (!strcmp(argv[0], "-R")) {
            param_R = 1;
        }
        if (!strcmp(argv[0], "-l")) {
            param_l = 1;
        }
        if (!strcmp(argv[0], "-g")) {
            param_g = 1;
        }
        list_of_file_with_param(param_g, param_l, param_R, "");
        exit(0);
    }
    list_of_file("");
    exit(0);
}

