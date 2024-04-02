#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	DIR *dirp;
	struct dirent *dentry;

	if((dirp = opendir(".")) == NULL) {
		fprintf(stderr, "Error\n");
		exit(1);
	}

	printf("files .. \n");
	while(dentry = readdir(dirp)) {
		if(dentry->d_ino != 0)
			printf("%s\n", dentry->d_name);

	}

	rewinddir(dirp);
	printf("clear files .. \n");
	while(dentry = readdir(dirp)) {
		if(dentry->d_ino == 0) 
			printf("%s\n", dentry->d_name);
	}
	closedir(dirp);
}
