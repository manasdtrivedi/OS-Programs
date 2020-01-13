#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>

extern int errno;

void handler_sigint(int sig)
{
        printf(" Caught signal %d\n",sig);

}

int main()
{
        int fd, size, lk;
        //char *c = (char *)calloc(100, sizeof(char));
        char c[100];

        // Create file 'file.txt'
        mode_t mode = S_IRWXU;
        char *file = "file.txt";
        fd = creat(file, mode);
        if(fd == -1)
        {
                printf("Error no. %d\n", errno);
                perror("Problem with creat()");
                exit(0);
        }
        else
        {
                printf("creat():\nCreated file 'file.txt'. Its fd is %d.\n\n", fd);
        }
        // Close file
        close(fd);
        printf("close():\nClosed file.\n\n");

        // Open file 'file.txt'
        fd = open(file, O_RDWR);
        if(fd == -1)
        {
                printf("Error Number %d\n", errno);
                perror("Problem with open()");
                exit(0);
        }
        else
        {
                printf("open():\nOpened file 'file.txt'. Its fd is %d.\n\n", fd);
        }

        // Writing to file
        size = write(fd, "OPERATING Systems", 17);
        printf("write():\n%d bytes were written.\n\n", size);

        // Reading from file
        lseek(fd, 0, SEEK_SET);
        size = read(fd, c, 17);
        c[size] = '\0';
        printf("read():\n%d bytes were read.\n", size);
        printf("Those bytes are: %s\n\n", c);

        // Writing to file again
        lseek(fd, 0, SEEK_SET);
        size = write(fd, "Operating", 9);
        printf("write():\n%d bytes were written.\n\n", size);

        // Reading from file again
        lseek(fd, 0, SEEK_SET);
        size = read(fd, c, 17);
        c[size] = '\0';
        printf("read():\n%d bytes were read.\n\n", size);
        printf("Those bytes are: %s\n", c);

        // Duplicate fd
        int duplicate_fd = dup(fd);
        printf("dup():\nfd = %d, duplicate_fd = %d.\n\n", fd, duplicate_fd);

        close(fd);
        printf("close():\nClosed file.\n\n");

        // Link
        char *fileAlias = "fileAlias.txt";
        lk = link(file, fileAlias);
        printf("link():\nlk = %d.\n", lk);
        perror("Link");
        printf("\n");

        // Unlink
        lk = unlink(fileAlias);
        printf("unlink():\nlk = %d.\n", lk);
        perror("Unlink");
        printf("\n");

        // Chmod
        chmod(file, S_IRUSR | S_IRGRP | S_IROTH);
        printf("chmod():\nUser, group and others now have R permission for '%s'.\n\n", file);

        // Access
        if(access(file, 0) == 0)
                printf("access():\nYou have existence permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have existence permission for '%s'.\n", file);
        if(access(file, 1) == 0)
                printf("access():\nYou have execute permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have execute permission for '%s'.\n", file);
        if(access(file, 2) == 0)
                printf("access():\nYou have write permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have write permission for '%s'.\n", file);
        if(access(file, 4) == 0)
                printf("access():\nYou have read permission for '%s'.\n\n", file);
        else
                printf("access():\nYou don't have read permission for '%s'.\n\n", file);

        // Chmod again
        chmod(file, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH);
        printf("chmod():\nUser has RWX, group has RX, others have R permission for '%s'\n\n", file);

        // Access again
        if(access(file, 0) == 0)
                printf("access():\nYou have existence permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have existence permission for '%s'.\n", file);
        if(access(file, 1) == 0)
                printf("access():\nYou have execute permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have execute permission for '%s'.\n", file);
        if(access(file, 2) == 0)
                printf("access():\nYou have write permission for '%s'.\n", file);
        else
                printf("access():\nYou don't have write permission for '%s'.\n", file);
        if(access(file, 4) == 0)
                printf("access():\nYou have read permission for '%s'.\n\n", file);
        else
                printf("access():\nYou don't have read permission for '%s'.\n\n", file);

        // GetPID
        printf("getpid():\n");
        printf("expt1: My ProcessID is %d.\n\n", getpid());

        int a = fork();
        pid_t childPID;
        if(a == 0)
        {
                printf("Inside child process. Its PID: %d, its parent's PID: %d\n", getpid(), getppid());
                //kill(getpid(),SIGKILL);
                exit(0);
        }
        else
        {
                childPID = wait(NULL);
                printf("Inside parent process. Its PID: %d, its child's PID: %d\n", getpid(), childPID);
        }
        printf("Child process terminated\n");

        printf("getuid():\nUser ID is %d\n",getuid());
        printf("geteuid():\nEffective user ID is %d\n",geteuid());
        printf("getgid():\nGroup ID is%d\n",getgid());
        printf("getegid():\nEffective group ID is %d\n",getegid());

       // signal(SIGINT, handler_sigint);

        printf("chdir():\n");
        chdir("..");

        //printf("execl():\n");
        //execl("/bin/ls", "ls", "-l", NULL);

        alarm(7);
        while(1)
        {
                sleep(1);
                printf("Slept for 1 sec\n");
                signal(SIGINT, handler_sigint);
        }

        return 0;
}