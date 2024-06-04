#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void handler(int signum);

int main() {
	struct sigaction act;
	sigset_t set;

	sigfillset(&(act.sa_mask));
	act.sa_handler = handler;
	
	sigaction(SIGCHLD, &act, NULL);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	pid_t  pid = fork();

	if(pid == 0) {
		int count = 10;

		while(count) {
			if(count == 5) {
				sigprocmask(SIG_UNBLOCK, &set, NULL);
			}
			printf("I am a child\n");
			sleep(1);
			count--;
		}
		sigprocmask(SIG_UNBLOCK, &set, NULL);
		exit(1);
	}
	
	else {
		pause();
	}
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	return 0;
}
	
void handler(int signum) {
	int pid, status;
	while((pid=waitpid(-1, &status, WNOHANG)) > 0) {
		int state;

		if(WIFEXITED(status)) state = 1;
		if(WIFSIGNALED(status)) {
			state = 0;
			printf("bye~\n");
		}

		printf("writing\n");
		int fd;
		fd = open("log.txt", O_RDWR | O_CREAT, 0644);
		off_t newpos = lseek(fd, (off_t)0, SEEK_END);
	
		time_t t = time(NULL);
		char *time_str = ctime(&t);
		time_str[strlen(time_str) - 1] = '\0';
	
		char log[256];
		snprintf(log, sizeof(log), "%d\t%s\t%s\n", pid, time_str, state ? "exit" : "Signal(bye~)");
	
		write(fd, log, strlen(log));
		close(fd);
	}
}
