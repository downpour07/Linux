#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
       DIR *dirp;
       DIR *dirCheck;
       int fileCount = 0;
       int dirCount = 0;
	struct dirent *dentry;
 	if((dirp = opendir(".")) == NULL) 
		exit(1);
	while(dentry = readdir(dirp)) {
		if(dentry->d_ino != 0) {
			if((dirCheck = opendir(dentry->d_name)) == NULL)
				fileCount++;
			else dirCount++;
		}
	}

	printf("file : %d\ndir : %d\n", fileCount, dirCount);
	closedir(dirp);
}	
