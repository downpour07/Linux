#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char buffer[1024];
	int nread, count, numchar = 0;

	fp = fopen(argv[1], "r");

	
	while((nread = fread(buffer,1024,1,fp)) > 0) {
		for(count = 0; count < nread; count++) {
			if((buffer[count] >= 'a' && buffer[count] <= 'z')
			||(buffer[count]>='A' && buffer[count]<='Z'))
				numchar++;
		}
	}
	fclose(fp);
	printf("number of : %d\n", numchar);
}
