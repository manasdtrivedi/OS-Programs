#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
extern int errno;
int main()
{
	int fd, sz;
	char c[1];
	
	mode_t mode = S_IRWXU;	
	char *file = "abc.txt";
	fd = creat(file, mode);
	printf("fd = %d\n", fd);
	if(fd == -1)
	{
		printf("Error Number %d\n", errno);
		perror("Problem with creat()");
		exit(0);
	}
	else
	{
		printf("Created the file with fd = %d\n", fd);

		//OPEN BEGINS HERE

		fd = open("abc.txt", O_RDWR);
		
		if(fd == -1)
		{
			printf("Error Number %d\n", errno);
			perror("Problem with open()");
			exit(0);
		}
		printf("Opened the file with fd = %d\n", fd);

		//READ BEGINS HERE

		sz = read(fd, c, 1);
		printf("%d bytes were read.\n", sz);
		printf("Those bytes are: %s\n", c);

		//WRITE BEGINS HERE

		sz = write(fd, "b", 1);

		//CLOSE BEGINS HERE

		fd = close(fd);
		
		printf("fd = %d\n", fd);
		if(fd == -1)
		{
			perror("Problem with close()");
			exit(0);
		}
		printf("Closed the file with fd = %d\n", fd);
		
	}
	return 0;
}
