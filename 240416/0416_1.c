#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	int x, y;
	scanf("%d %d", &x, &y);
	if(!(x >= 1 && x <= 10) || !(y>=1 && y<=10)) {
		printf("RESTART\n");
		scanf("%d %d", &x, &y);
	}
	pid_t pid;
	pid = fork();
	int status, a = 1, b = 0;

	if(pid > 0) {
		for(int i = 1; i<=y; i++)
			a *= x;
		printf("parent : %d\n", a);
		wait(&status);
		status = status>>8;
		printf("%d\n", a+status);
	}
	else if(pid == 0) {
		for(int i = x; i<=y; i++)
			b += i;
		printf("child : %d\n", b);
		exit(b);
	}
	else printf("error\n");
}
