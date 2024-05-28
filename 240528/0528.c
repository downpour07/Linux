#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main() {
	pid_t pid;

	pid = fork();

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, NULL);

	if(pid == 0) {
		int count = 5;

		while(count) {
			sleep(1);
			printf("I am a child\n");
			count--;
		}

		sigprocmask(SIG_UNBLOCK, &set, NULL);

		sleep(10);
		exit(1);
	}

	else if(pid > 0) {
		int status, state = 1;
		waitpid(pid, &status, 0);
		if(status != 256) {
			printf("bye~\n");
			state = 0;
		}

		printf("writing\n");

		int fd;
		fd = open("log.txt", O_RDWR | O_CREAT, 0644);
		off_t newpos = lseek(fd, (off_t)0, SEEK_END);

		time_t t = time(NULL);
		char *time_str = ctime(&t);
		time_str[strlen(time_str) - 1] = '\0';

		char log[256];
		snprintf(log, sizeof(log), "%d\t%d\t%s\t%s\n", pid, 1, time_str, state ? "exit" : "Signal(bye~)");

		write(fd, log, strlen(log));
		close(fd);
	}

	else printf("process error\n");
}
