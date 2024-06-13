#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXARG 7

int main() {
    char buf[256];
    char *args[MAXARG];
    char *s;
    char *save;
    int argn;
    static const char delim[] = "\t\n";
    int pid[MAXARG], status;
    int i, ch;
    int fd;
    while (1) {
        printf("[shell] ");
        gets(buf);
        // printf("buf %s\n", buf);
        argn = 0;
        ch = 1;
        for (i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '&') {
                ch = 2;
                break;
            }
            else if (buf[i] == '>') {
                ch = 3;
                break;
            }
            else if (buf[i] == '<') {
                ch = 4;
                break;
            }
            else if (buf[i] == ';') {
                ch = 5;
                break;
            }
            else if (buf[i] == '|') {
                ch = 6;
                break;
            }
        }
        if (ch == 1) {
            argn = 0;
            s = strtok_r(buf, delim, &save);
            while(s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;
            if (argn == 0) 
                continue;
            if(!strcmp(args[0], "quit"))
                break;
            if ((pid[0] = fork()) == -1)
                perror("fork failed");
            else if (pid[0] == 0) {
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행 \n", args[0]);
                exit(1);
            }
            else {
                waitpid(pid[0], &status, 0);
            }
        }
        if (ch == 2) {
            char *cmd;
            cmd = strtok_r(buf, "&", &save);
            argn = 0;
            s = strtok_r(cmd, delim, &save);
            while(s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;
            if ((pid[0] = fork()) == 0) {
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행불가\n", args[0]);
                exit(5);
            }
            else {
                printf("%s %d\n", cmd, pid[0]);
            }
        }
        if (ch == 3) {
            char *cmd;
            char *file;
            cmd = strtok_r(buf, ">", &save);
            file = strtok_r(NULL, ">", &save);
            argn = 0;
            s = strtok_r(cmd, delim, &save);
            while(s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;
            if ((pid[0] = fork()) == 0) {
                fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0600);
                dup2(fd, 1);
                close(fd);
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행불가 \n", args[0]);
                exit(3);
            }
            else {
                waitpid(pid[0], &status, 0);
            }
        }
        if (ch == 4) {
            char *cmd;
            char *file;
            cmd = strtok_r(buf, '<', &save);
            file = strtok_r(NULL, '<', &save);
            argn = 0;
            s = strtok_r(cmd, delim, &save);
            while(s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;
            if ((pid[0] = fork()) == 0) {
                fd = open(file, O_RDONLY);
                dup2(fd, 0);
                close(fd);
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행불가 \n", args[0]);
                exit(4);
            }
            else {
                printf("%s %d\n", cmd, pid[0]);
            }
        }
        
    }
    exit(0);

}