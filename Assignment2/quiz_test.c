#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#define MAXARG 7
#define MAXLINE 512
void alarmHandler();
int spid;

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
        printf("[SHELL] ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            exit(1); // 입력이 없으면 종료
        }
        // gets(buf);

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
        if (ch == 6) {
            char *cmd1, *cmd2;
            char *args1[MAXARG];
            int argn1 = 0;
            argn = 0;

            cmd1 = strtok_r(buf, "|", &save);
            cmd2 = strtok_r(NULL, "|", &save);

            s = strtok_r(cmd1, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;

            s = strtok_r(cmd2, delim, &save);
            while (s) {
                args1[argn1++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args1[argn1] = NULL;

            FILE *pipe_fp1;
            FILE *pipe_fp2;
            char command1[MAXLINE] = "";
            char command2[MAXLINE] = "";
            char buffer[MAXLINE];

            for (int i = 0; args[i] != NULL; i++) {
                strcat(command1, args[i]);
                strcat(command1, " ");
            }

            for (int i = 0; args1[i] != NULL; i++) {
                strcat(command2, args1[i]);
                strcat(command2, " ");
            }

            if ((pipe_fp1 = popen(command1, "r")) == NULL) {
                perror("popen cmd1");
                exit(6);
            }

            if ((pipe_fp2 = popen(command2, "w")) == NULL) {
                perror("popen cmd2");
                pclose(pipe_fp1);
                exit(0);
            }

            while (fgets(buffer, sizeof(buffer), pipe_fp1) != NULL) {
                fputs(buffer, pipe_fp2);
            }

            pclose(pipe_fp1);
            pclose(pipe_fp2);

        }

    }
}