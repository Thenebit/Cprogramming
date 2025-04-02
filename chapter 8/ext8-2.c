/* Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit 
 operations.
*/

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

// standard I/O streams
struct _iobuf _iob[20] = {

        {0, (char *)0, (char *)0, _READ, 0},
        {0, (char *)0, (char *)0, _WRITE, 1},
        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}
};

#define my_stdin (&_iob[0])
#define my_stdout (&_iob[1])
#define my_stderr (&_iob[2])

// Function prototypes
int _fillbuf(struct _iobuf *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define my_getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define my_putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define my_getchar() my_getc(my_stdin)
#define my_putchar(x) my_putc((x), my_stdout)

//fopen - Open a file, return a file pointer
struct _iobuf *my_fopen(char *name, char *mode)
{

        int fd;
        struct _iobuf *fp;


        if(*mode != 'r' && *mode != 'w' && *mode != 'a'){
                return NULL;
        }

        // find free slot
        for(fp = _iob; fp < _iob + 20; fp++){

                if((fp->flag & (_READ | _WRITE)) == 0){
                        break;
                }
        }


        if(fp >= _iob + 20){
                return NULL;
        }

        // open file
        if (*mode == 'w') {

                fd = creat(name, PERMS);
   
        } else if (*mode == 'a') {

                if ((fd = open(name, O_WRONLY, 0)) == -1) {

                        fd = creat(name, PERMS);
                }

                lseek(fd, 0L, SEEK_END);

        } else {
                fd = open(name, O_RDONLY, 0);
        }


        if (fd == -1) {
                return NULL;
        }


        fp->fd = fd;
        fp->cnt = 0;
        fp->base = NULL; 
        fp->flag = (*mode == 'r') ? _READ : _WRITE;

        return fp;
}

// _fillbuf - Allocate and fill input buffer.
int _fillbuf(struct _iobuf *fp)
{

        int bufsize;

 
        if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
                return EOF;
        }


        bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

        if (fp->base == NULL) {

                if ((fp->base = (char *)malloc(bufsize)) == NULL) {

                        return EOF;
                }
        }

        // read buffer
       //fp->ptr = fp->base;
        fp->cnt = read(fp->fd, fp->ptr, bufsize);
        fp->ptr = fp->base;

        if (--fp->cnt < 0) {
		fp->flag |= _ERR;

		return EOF;
	}else if(fp->cnt == 0){
		fp->flag |= _EOF;

		return EOF;
	}

        return (unsigned char)*fp->ptr++;
}

//fclose - Close file.
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

// _flushbuf - Flush output buffer
int _flushbuf(int c, struct _iobuf *fp)
{

        int bufsize;


        if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {

                return EOF;
        }

  
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

int main(int argc, char *argv[])
{
        struct _iobuf *fp;
        char *prog = argv[0];


        if (argc == 1) {

                fprintf(stderr, "Usage: %s file1 file2 ...\n", prog);
                fp = my_stdin;

        } else {
                while (--argc > 0) {

                        if ((fp = my_fopen(*++argv, "r")) == NULL) {

                                fprintf(stderr, "%s: can't open %s\n", prog, 
                                *argv);
                                exit(1);

                        } else {

                                int c;
                                while ((c = my_getc(fp)) != EOF) {
                                        my_putchar(c);
                                }

                                my_fclose(fp);
                        }
                }
        }


        if (ferror(my_stdout)) {

                fprintf(stderr, "%s: error writing stdout\n", prog);
                exit(2);
        }

        return 0;
}
