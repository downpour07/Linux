#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
	int fd;
	ssize_t nread;
	char buffer[1024];
	int count = 0, numchar = 0;

	if((fd = open("0319_1.txt", O_RDWR)) == -1) {
		printf("error\n");
		exit(1);
	}

	while((nread = read(fd, buffer, 1024)) > 0) {
		for(count = 0; count < nread; count++) {
			//if((buffer[count] >= 'a' && buffer[count] <= 'z') ||
			//	(buffer[count] >= 'A' && buffer[count] <= 'Z'))
			//	numchar++;

			if(buffer[count] >= 'a' && buffer[count] <= 'z')
				buffer[count] = buffer[count] -'a' + 'A';
		}
		lseek(fd, (off_t)-nread, SEEK_CUR);
		if(write(fd, buffer, nread) < nread) close(fd);
	}

	//printf("number : %d\n", count);
	close(fd);
}
