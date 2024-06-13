#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#define CMD_SIZE 1024

#define MAXARG 7
#define MAXLINE 512

void alarmHandler();
int spid;

int main() {
    char buf[256];
    char *args[MAXARG];
    char *s;
    char *save1, *save2;
    int argn;
    static const char delim[] = " \t\n";
    int pid[MAXARG], status;
    int i;
    
    while (1) {
        printf("[SHELL] ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            exit(1); // 입력이 없으면 종료
        }

        // 파이프 체크
        int has_pipe = 0;
        for (int i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '|') {
                has_pipe = 1;
                break;
            }
        }

        if (has_pipe) {
            char *cmd1, *cmd2;
            char cmd1_args[CMD_SIZE], cmd2_args[CMD_SIZE];

            // buf를 '|'로 나누어서 cmd1과 cmd2에 저장
            cmd1 = strtok(buf, "|");
            cmd2 = strtok(NULL, "|");

            // 불필요한 공백 제거
            strcpy(cmd1_args, cmd1);
            strcpy(cmd2_args, cmd2);

            // 첫 번째 명령어 실행
            FILE *pipe1 = popen(cmd1_args, "r");
            if (pipe1 == NULL) {
                perror("popen");
                exit(1);
            }

            // 두 번째 명령어 실행
            FILE *pipe2 = popen(cmd2_args, "w");
            if (pipe2 == NULL) {
                perror("popen");
                exit(1);
            }

            // 첫 번째 명령어에서 읽은 데이터를 두 번째 명령어에 쓰기
            char buffer[CMD_SIZE];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), pipe1)) > 0) {
                fwrite(buffer, 1, bytes_read, pipe2);
            }

            // 파이프 닫기
            pclose(pipe1);
            pclose(pipe2);
        } else {
            // 파이프가 없는 경우 단일 명령어 실행
            system(buf);
        }
    }

    return 0;
}
