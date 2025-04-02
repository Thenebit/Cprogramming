//Exercise 8-3. Design and write _flushbuf, fflush, and fclose.

#include <stdlib.h>
#include <unistd.h>

#ifdef NULL
#undef NULL
#endif

#define NULL (0)
#define EOF (-1)
#define BUFSIZ (1024)
#define OPEN_MAX (20)

struct _iobuf{
	int cnt; //characters left
	char *ptr; //next character in position
	char *base; //location of buffer
	int flag; //mode of file access
	int fd; //file descriptor
};
extern struct _iobuf _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags{
	_READ = 01, //file open for reading
	_WRITE = 02, //file open for writing
	_UNBUF = 03, //file is unbuffered
	_EOF = 010, //EOF has occurred on this file
	_ERR = 020 //error occurred on this file
};

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS (0666) //RW for owner, group, others

struct _iobuf _iob[OPEN_MAX] = { //stdin, stdout, stderr
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

//_fillbuf: allocate and fill input buffer
int _fillbuf(struct _iobuf *fp)
{
	int bufsize;

	if((fp -> flag&(_READ | _EOF| _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if(fp->base == NULL){ //no buffer yet
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; //can't get buffer
	}

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if(--fp->cnt < 0){
		if(fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;

		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}

//_flushbuf: allocate and flush output buffer
int _flushbuf(int c, struct _iobuf *fp)
{
	int n, bufsize;
	unsigned char uc = c;

	if((fp->flag & (_WRITE | _EOF| _ERR)) != _WRITE)
		return EOF;
	if(fp->base == NULL && ((fp->flag & _UNBUF) == 0)){ 
		//no buffer yet
		if((fp->base = malloc(BUFSIZ)) == NULL)
			//could not allocate a buffer, so try unbuffered
            		fp->flag |= _UNBUF;
        	else{
            		fp->ptr = fp->base;
            		fp->cnt = BUFSIZ - 1;
        	}
	}
	if (fp->flag & _UNBUF){
        	//unbuffered write
        	fp->ptr = fp->base = NULL;
        	fp->cnt = 0;

        	if(c == EOF)
            		return EOF;

        	n = write(fp->fd, &uc, 1);
        	bufsize = 1;
    	}else{
        	//buffered write
        	bufsize = (int) (fp->ptr - fp->base);
        	n = write(fp->fd, fp->base, bufsize);
        	fp->ptr = fp->base;
        	fp->cnt = BUFSIZ - 1;
    	}

    	if(n == bufsize)
        	return c;
    	else{
        	fp->flag |= _ERR;
        	return EOF;
    	}
}

//fflush: flush buffer associated with file fp
int fflush(struct _iobuf *fp)
{
	int retval;

    	retval = 0;
    	if(fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF; //invalid pointer
	if(fp->flag & _WRITE)
		retval = _flushbuf(0, fp);

	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    	return retval;
}

//fclose: close file
int fclose(struct _iobuf *fp)
{
	int retval;

	retval = 0;
	if(fp == NULL || fp < _iob || fp >= _iob + OPEN_MAX)
        	return EOF; //invalid pointer
	if((fp->flag & _WRITE) == _WRITE)
        	retval = fflush(fp); //flush buffer
	if(fp->base != NULL)
        	free(fp->base); //free allocated memory
	if(close(fp->fd) != 0) //close file 
        	retval = EOF; 
    	fp->cnt = fp->flag = 0;
    	fp->fd = -1;
    	fp->ptr = fp->base = NULL;

    	return retval;
}

int main(void)
{
	int c;

	while((c = getchar()) != EOF)
		putchar(c);

	return 0;
}
