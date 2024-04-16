#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	pid_t pid[3];
	int status;

	for(int i = 0; i<3; i++) {
		pid[i] = -1;
	}

	pid[0] = fork();

	if(pid1>0) {
		pid2 = fork();
	}

	if(pid1>0 && pid2>0) {
		waitpid(pid2, &status, 0);
		printf("parent : child2 - exit(%d)\n", status);
		waitpid(pid1, &status, 0);
		printf("parent : child1 - exit(%d)\n", status);
	}
	else if(pid1 == 0 && pid2==-1) {
		sleep(1);
		exit(1);
	}
	else if(pid1>0 && pid2==0) {
		sleep(2);
		exit(2);
	}
	else printf("fail to fork\n");
}
