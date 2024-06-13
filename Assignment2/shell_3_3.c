#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 7
#define MAXLINE 512

int main() {
    char buf[256];
    char *args[MAXARG];
    char *s;
    char *save;
    int argn;
    static const char delim[] = " \t\n";
    int i;

    while (1) {
        printf("[SHELL] ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break; // 입력이 없으면 종료
        }

        // 파이프 체크
        int has_pipe = 0;
        for (i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '|') {
                has_pipe = 1;
                break;
            }
        }

        if (has_pipe) {
            char *cmd1, *cmd2;
            char *args1[MAXARG];
            int argn1 = 0;

            cmd1 = strtok_r(buf, "|", &save);
            cmd2 = strtok_r(NULL, "|", &save);

            // 첫 번째 명령어 분리
            argn = 0;
            s = strtok_r(cmd1, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;

            // 두 번째 명령어 분리
            s = strtok_r(cmd2, delim, &save);
            while (s) {
                args1[argn1++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args1[argn1] = NULL;

            // 첫 번째 명령어 실행
            FILE *fp1 = popen(args[0], "r");
            if (fp1 == NULL) {
                perror("popen");
                exit(1);
            }

            // 첫 번째 명령어의 출력을 읽어들임
            char result[MAXLINE];
            size_t bytes_read = fread(result, 1, sizeof(result) - 1, fp1);
            if (bytes_read == 0) {
                pclose(fp1);
                continue;
            }
            result[bytes_read] = '\0'; // 널 종료 문자 추가
            pclose(fp1);

            // 두 번째 명령어 실행
            FILE *fp2 = popen(args1[0], "w");
            if (fp2 == NULL) {
                perror("popen");
                exit(1);
            }

            // 첫 번째 명령어의 출력을 두 번째 명령어의 입력으로 제공
            fwrite(result, 1, bytes_read, fp2);
            pclose(fp2);

        } else {
            // 파이프 없는 경우 처리 (단일 명령어)
            argn = 0;
            s = strtok_r(buf, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;

            if (fork() == 0) {
                // 자식 프로세스: 단일 명령어 실행
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }

    return 0;
}
