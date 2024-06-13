if (fork() == 0) {
        printf("Hello pid=%d\n", getpid(), getppid());
    }
    if (fork() == 0) {
        printf("Good morning pid=%d\n", getpid(), getppid());
    }