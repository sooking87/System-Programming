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
        for (int i = 0; buf[i] != '\0'; i++) {
            
            if (buf[i] == '|') {
                ch = 6;
                break;
            }
        }
        
        if (ch == 6) {
            char *cmd1, *cmd2;
            char *args1[MAXARG];
            int argn1 = 0;
            argn = 0;

            cmd1 = strtok_r(buf, "|", &save);
            cmd2 = strtok_r(NULL, "|", &save);

            /* cmd1 에서 delim을 기준으로 단어를 잘라냄 */
            s = strtok_r(cmd1, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */

            /* cmd2 에서 delim을 기준으로 단어를 잘라냄 */
            s = strtok_r(cmd2, delim, &save);
            while (s) {
                args1[argn1++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args1[argn1] = NULL;

            /* cmd1 명령을 파이프를 통해 실행하고, 출력을 읽어 cmd2 명령의 입력으로 사용 */
            FILE *pipe_fp1, *pipe_fp2;
            char command1[MAXLINE] = "", command2[MAXLINE] = "", buffer[MAXLINE];

            for (int i = 0; args[i] != NULL; i++) {
                strcat(command1, args[i]);
                strcat(command1, " ");
            }

            for (int i = 0; args1[i] != NULL; i++) {
                strcat(command2, args1[i]);
                strcat(command2, " ");
            }

            /* cmd1 명령 실행 및 출력 파이프 열기 */
            if ((pipe_fp1 = popen(command1, "r")) == NULL) {
                perror("popen cmd1");
                exit(EXIT_FAILURE);
            }

            /* cmd2 명령 실행 및 입력 파이프 열기 */
            if ((pipe_fp2 = popen(command2, "w")) == NULL) {
                perror("popen cmd2");
                pclose(pipe_fp1);
                exit(EXIT_FAILURE);
            }

            /* cmd1의 출력을 읽어서 cmd2의 입력으로 전달 */
            while (fgets(buffer, sizeof(buffer), pipe_fp1) != NULL) {
                fputs(buffer, pipe_fp2);
            }

            pclose(pipe_fp1);
            pclose(pipe_fp2);
        }

    }
}