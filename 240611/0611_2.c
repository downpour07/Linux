#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define SIZE 512 

int main() {
	int p1[2], p2[2];
	int buf[SIZE];
	pid_t pid1 = 0, pid2 = 0;

	printf("input two numbers: ");
	scanf("%d %d", &buf[0], &buf[1]);
	int bufsize = strlen(buf);

	if(pipe(p1) == -1) {
		printf("fail to call pipe() 1\n");
		exit(1);
	}
	if(pipe(p2) == -1) {
		printf("fail to call pipe() 2\n");
		exit(1);
	}

	if((pid1 = fork()) == -1) {
		printf("fail to call fork() 1\n");
		exit(1);
	}
	if(pid1 > 0) {
		if((pid2 = fork()) == -1) {
			perror("fail to call fork() 2\n");
		}
	}

	if(pid1 > 0 && pid2 > 0) {
		write(p1[1], buf, bufsize);
		write(p2[1], buf, bufsize);

		sleep(5);

		read(p1[0], buf, bufsize);
		printf("%d ", buf[0]);
		read(p2[0], buf, bufsize);
		printf("%d\n", buf[1]);
	}
	else if(pid1 == 0 && pid2 == 0) {
		close(p2[0]);
		close(p2[1]);
		
		read(p1[0], buf, bufsize);
		buf[0] = buf[0] + buf[1];
		printf("%d ", buf[0]);
		
		write(p1[1], buf, bufsize);
	}
	else {
		close(p1[0]);
		close(p1[1]);

		read(p2[0], buf, bufsize);
		buf[1] = buf[0] * buf[1];
		printf("%d\n", buf[1]);

		write(p2[1], buf, bufsize);
	}
}
