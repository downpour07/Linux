#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid[3];
    int status;

    for (int i = 0; i < 3; i++) {
        pid[i] = -1;
    }

    for (int i = 0; i < 3; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            printf("Failed to fork\n");
            exit(1);
        }

        if (pid[i] == 0) {
            if (i == 0) {
                sleep(1);
                exit(1);
            } else if (i == 1) {
                sleep(2);
                exit(2);
            } else if (i == 2) {
                sleep(3);
                exit(3);
            }
        }
    }
    if (pid[0] > 0 && pid[1] > 0 && pid[2] > 0) {
        for (int i = 0; i < 3; i++) {
            waitpid(pid[i], &status, 0);
            printf("parent: child%d - exit(%d)\n", i+1, status);
        }
    }

    return 0;
}
