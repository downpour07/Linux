#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
	int num = 0;
	scanf("%d", &num);
	pid_t pid;

	pid = fork();

	if(pid > 0) {
		int sum = 0;
		for(int i = 1; i <= num; i++)
			sum += i;
		printf("sum = %d\n", sum);
	}
	else if(pid == 0) {
		int mul = 1;
		for(int i = 1; i<=num; i++)
			mul *= i;
		printf("mul = %d\n", mul);
	}
	else
		printf("error\n");
}
