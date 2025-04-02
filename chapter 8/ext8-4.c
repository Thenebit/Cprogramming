// Exercise 8-4. The standard library function
// int fseek(FILE *fp, long offset, int origin)
// is identical to lseek except that fp is a file pointer instead of a file
// descriptor and return value
// is an int status, not a position. Write fseek. Make sure that your fseek
// coordinates properly
// with the buffering done for the other functions of the library

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS (0666) // RW for owner, group, others

struct _iobuf
{
        int cnt;    // characters left
        char *ptr;  // next character position
        char *base; // location of buffer
        int flag;   // mode of file access
        int fd;	    // file descriptor
};

// File flags
enum _flags
{
        _READ = 01,  // file open for reading
        _WRITE = 02, // file open for writing
        _UNBUF = 04, // file is unbuffered
        _EOF = 010,  // EOF has occurred on this file
        _ERR = 020   // error occurred on this file
};

// Standard I/O streams
struct _iobuf _iob[20] = { // stdin, stdout, stderr
        {0, (char *)0, (char *)0, _READ, 0},
        {0, (char *)0, (char *)0, _WRITE, 1},
        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}
};

#define my_stdin (&_iob[0])
#define my_stdout (&_iob[1])
#define my_stderr (&_iob[2])

// Function prototypes
int _fillbuf(struct _iobuf *);

#define feof(p) (((p)->flag & _EOF) != 0)   // test for end of file
#define ferror(p) (((p)->flag & _ERR) != 0) // test for error
#define fileno(p) ((p)->fd)		    // get file descriptor

#define my_getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define my_putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define my_getchar() my_getc(my_stdin)	      // get a character from stdin
#define my_putchar(x) my_putc((x), my_stdout) // put a character to stdout

//my_fopen - Open a file, return a file pointer.
struct _iobuf *my_fopen(char *name, char *mode)
{
        int fd;
        struct _iobuf *fp;


        if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
                return NULL;
        }

        // open file
        if (*mode == 'w') {
                fd = creat(name, PERMS);
        } else if (*mode == 'a') {

                if ((fd = open(name, O_WRONLY, 0)) == -1) {
                        fd = creat(name, PERMS);
                }
 
                lseek(fd, 0L, 2);

        } else {
                fd = open(name, O_RDONLY, 0);
        }

        // open failed
        if (fd == -1) {
                return NULL; // couldn't access name
        }

        fp = (struct _iobuf *)malloc(sizeof(struct _iobuf));

        if (fp == NULL) {
                return NULL;
        }

        fp->fd = fd;	 // save file descriptor
        fp->cnt = 0;	 // no characters in buffer
        fp->base = NULL;

        fp->flag = (*mode == 'r') ? _READ : _WRITE;

        return fp;
}

//_fillbuf - Fill input buffer.
int _fillbuf(struct _iobuf *fp)
{
        int bufsize;


        if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
                return EOF;
        }

        // allocate buffer
        bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
        if (fp->base == NULL) {
                if ((fp->base = (char *)malloc(bufsize)) == NULL) {
                        return EOF; 
                }
        }
        fp->ptr = fp->base;			  // set buffer pointer
        fp->cnt = read(fp->fd, fp->ptr, bufsize); // fill buffer
        fp->ptr = fp->base;

        // check read error
        if (--fp->cnt < 0) {
                // check EOF
                if (fp->cnt == -1) {
                        fp->flag |= _EOF;
                } else {
                        fp->flag |= _ERR;
                }
                fp->cnt = 0;
                return EOF;
        }

        return (unsigned char)*fp->ptr++;
}

// _flushbuf - Flush output buffer.
int _flushbuf(int c, struct _iobuf *fp)
{
        int bufsize;


        if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
                return EOF;
        }

        // allocate buffer
        bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
        if (fp->base == NULL) {
                if ((fp->base = (char *)malloc(bufsize)) == NULL) {
                        return EOF; 
                }
        } else {

                if (write(fp->fd, fp->base, bufsize) != bufsize) {
                        fp->flag |= _ERR;
                        return EOF;
                }
        }

        fp->ptr = fp->base;
        fp->cnt = bufsize - 1;
        *fp->ptr++ = c;

        return c;
}

// my_fclose - Close a file.
int my_fclose(struct _iobuf *fp)
{
        if (fp == NULL)
                return EOF;
        if (fp->base != NULL)
                free(fp->base);
        close(fp->fd);

        fp->cnt = 0;
        fp->ptr = NULL;
        fp->base = NULL;
        fp->flag = 0;
        fp->fd = -1;

        return 0;
}

//fseek - Move file pointer to a specified position.
int my_fseek(struct _iobuf *fp, long offset, int origin)
{
        if (fp == NULL)
                return -1;	//return -1 for failure
        if (fp->flag & _WRITE){
		if(_flushbuf(0, fp) == EOF)
			return -1;	//error flushing buffer
	}

	//use lseek to move file desciptor
	off_t new_position = lseek(fp->fd, offset, origin);
	if(new_position == -1)
		return -1;	//lseek failed

	//reset buffer state
        fp->cnt = 0;	//no character in buffer
        fp->ptr = NULL;		//reset pointer
        fp->base = NULL;	//reset base
        //fp->flag = 0;
        //fp->fd = -1;

        return 0;	//success
}

int main(void)
{
        struct _iobuf *fp;
        int c;

        // open file
        if ((fp = my_fopen("ext8-4.c", "r")) == NULL) {
		fprintf(stderr, "Error: could not find file ext8-4.c\n");
                return 1;
        }

        // read file
        while ((c = my_getc(fp)) != EOF) {
                my_putchar(c);
        }

        // close file
        if (my_fclose(fp) == EOF){
		fprintf(stderr, "Error: could not close file\n");
                return 1;
        }

        return 0;
}
