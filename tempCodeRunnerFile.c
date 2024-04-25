FILE *fd;
    if ((fd = creat("./myfile", 0600)) == -1) {
        perror("./myfile");
    }
    write(fd, "Hello! Linux", 12);
    dup2(1, fd);
    write(fd, "Bye! Linux", 10);
    exit(0);