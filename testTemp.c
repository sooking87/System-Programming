#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // open, close 함수

int main() {
    // 23 10번
    char buf1[] = "good afternoon111";
    char buf2[] = "good afternoon2222";
    FILE *fd1, *fd2;
    printf("%d\n", sizeof(buf1));
    fd1 = open("test", O_RDWR);
    write(fd1, buf1, sizeof(buf1));
    fd2 = open("test", O_RDWR);
    write(fd2, buf2, sizeof(buf2));
    

    // // 23 5번
    // FILE *fd;
    // if ((fd = creat("./myfile23", 0600)) == -1) {
    //     perror("./myfile23");
    // }
    // write(fd, "Hello! Linux", 12);
    // dup2(1, fd);
    // write(fd, "Bye! Linux", 10);
    // exit(0);

    // // 18 1번
    // FILE *fd, *fd2;
    // if ((fd = creat("./myfile18", 0600)) == -1) {
    //     perror("./myfile18");
    // }
    // write(fd, "Hello! Linux", 12);
    // fd2 = dup(fd);
    // write(fd2, "Bye! Linux", 10);
    // exit(0);
}