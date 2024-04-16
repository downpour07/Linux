#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	pid_t pid;
	int status;

	pid = fork();
	if(pid>0) {
		printf("parnet: waiting\n");
		wait(&status);
		printf("parent: status is %d\n", status);
	}
	else if(pid == 0) {
		sleep(1);
		printf("child: bye\n");
		exit(1);
	}
	else printf("fail to fork\n");
	printf("bye\n");
}
