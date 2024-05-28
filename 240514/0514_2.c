#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
	sigset_t set;
	int count = 5;
	sigfillset(&set);

	sigprocmask(SIG_BLOCK, &set, NULL);

	while(count) {
		printf("don't disturb me (%d)\n", count--);
		sleep(1);
	}
	sigdelset(&set, SIGINT);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_UNBLOCK, &set, NULL);
	printf("you did not disturb me!!\n");
}
