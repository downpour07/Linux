#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char *filename = "b.txt";

	if(access(filename, F_OK) == -1) {
		printf("file none\n");
		exit(1);
	}
	printf("file OK");
}
