#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int nread = 0;
	char buffer[1024];
	if((nread = readlink(argv[1], buffer, 1024)) == -1)
		printf("No soft-link\n");
	else
		printf("Yes soft-link\n");
}
