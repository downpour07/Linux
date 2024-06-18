#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define SIZE 512 

int main() {
	int fd[2];
	int buf[SIZE];
	pid_t pid;

	printf("input two numbers: ");
	scanf("%d %d", &buf[0], &buf[1]);
	int bufsize = strlen(buf);

	if(pipe(fd) == -1) {
		printf("fail to call pipe()\n");
		exit(1);
	}

	if((pid = fork()) == -1) {
		printf("fail to call fork()\n");
		exit(1);
	}
	else if(pid > 0) {
		close(fd[0]);
		write(fd[1], buf, bufsize);
		sleep(3);
	}
	else {
		close(fd[1]);

		read(fd[0], buf, bufsize);
		printf("sum = %d\n", buf[0]+buf[1]);
	}
}
