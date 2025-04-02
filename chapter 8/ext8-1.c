/*Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write,
 open, and close  instead of their standard library equivalents. Perform experiments to
 determine the relative  speeds of the two versions.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE (1024)

//filecopy: copy file ifd to file ofd - file desciptor(fd)
int filecopy(int ifd, int ofd)
{
	char buf[BUFSIZE];
	int number_of_bytes;

	// read from input file descriptor
	while((number_of_bytes = read(ifd, buf, BUFSIZE)) > 0){

		if (write(ofd, buf, number_of_bytes) != number_of_bytes){

			fprintf(stderr, "write error\n");
			exit(3);

		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int fd;   //file descriptor
	char *prog = argv[0];

	if(argc == 1){
		filecopy(0, 1);

	}else{
		while(--argc > 0){
	                 if((fd = open(*++argv, O_RDONLY, 0)) == -1){

				fprintf(stderr, "%s: can't open %s\n", prog, *argv);

				exit(1);
			}else{

				filecopy(fd, 1);
				close(fd);
			}
		}
	}

	// check for errors
	if(ferror(stdout)){

		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}

	return 0;
}
