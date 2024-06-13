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
            break; // 입력이 없으면 종료
        }
        buf[strcspn(buf, "\n")] = '\0';

        // gets(buf);
        printf("buf %s \n", buf);
        ch=1;
        for (i = 0; buf[i] != '\0'; i++) {
            printf("buf[%d] %c \n", i, buf[i]);
            if (buf[i] == '|') {
                ch = 6;
                break;
            }
        }
        printf("ch %d \n", ch);
        if (ch == 6) {
            char *cmd1, *cmd2;
            char *args1[MAXARG];
            int argn1 = 0;

            argn = 0;
            char buf_copy[sizeof(buf)];
            strcpy(buf_copy, buf);

            cmd1 = strtok_r(buf_copy, "|", &save);
            cmd2 = strtok_r(NULL, "|", &save);

            if (cmd1 && cmd2) {
                printf("cmd1: %s, cmd2: %s \n", cmd1, cmd2);
            }
            // cmd1 = strtok_r(buf, '|', &save);
            // cmd2 = strtok_r(NULL, '|', &save);
            // printf("cmd1: %s, cmd2: %s \n", cmd1, cmd2);

            s = strtok_r(cmd1, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
                printf("%s ", s);
            }
            args[argn] = NULL; // 인수가 더 없음을 의미하는 문자 추가
 
            s = strtok_r(cmd2, delim, &save);
            while (s) {
                args1[argn1++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args1[argn1] = NULL;
            if ((pid[0] = fork()) == 0) {
                int fd[2];
                pipe(fd);
                if ((pid[1] = fork()) == 0) {
                    close(fd[0]);
                    dup2(fd[1], 1);
                    close(fd[1]);
                    execvp(args[0], args);
                    perror("pipe");
                    exit(6);
                }
                else {
                    close(fd[1]);
                    dup2(fd[1], 1);
                    close(fd[0]);
                    execvp(args1[0], args1);
                    perror("pipe");
                    exit(0);
                }
            }
            else {
                waitpid(pid[0], &status, 0);
            } 
        }
    }
}