// Exercise 8-5. Modify the fsize program to print the other information 
// contained in the inode entry

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// fsize - print file size
int fsize(char *name)
{

	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);

		return -1;
	}

	printf("File: %s\n", name);
	printf("Size: %ld bytes\n", stbuf.st_size);
	printf("Blocks: %ld\n", stbuf.st_blocks);
	printf("IO Block: %ld bytes\n", stbuf.st_blksize);
	printf("Device: %ld\n", stbuf.st_dev);
	printf("Inode: %ld\n", stbuf.st_ino);
	printf("Links: %ld\n", stbuf.st_nlink);

	printf("Last modified: %s", ctime(&stbuf.st_mtime));

        return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 1) // check for default if no arguments
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);

	return 0;
}
