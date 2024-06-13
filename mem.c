#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>

int main() {
    char str[32] = "Do you like Linux?";
    char *ptr, *p;

    ptr = (char *)malloc(32);
    memcpy(ptr, str, strlen(str));
    puts(ptr);
    memset(ptr+12, 'l', 4);
    puts(ptr);

    p = (char *)memchr(ptr, 'l', 18);
    puts(p);
    memmove(str+12, str+7, 10);
    puts(str);
}
