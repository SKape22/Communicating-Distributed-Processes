#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<unistd.h>

#define MIN(x,y) (x<y? x:y)

char *trim(char *s) {
    char *ptr;
    if (!s)
        return NULL;   // handle NULL string
    if (!*s)
        return s;      // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    return s;
}

ulong getFileSize(FILE *fptr)
{
    fseek(fptr,0L,SEEK_END); // find the end EOF
    long file_size=ftell(fptr);
    rewind(fptr);
    return file_size;
}

int sendfile(void *sndbuf, int bufsize, int consockfd, char *file)
{
	FILE *fptr;
	long file_size;
	size_t bytes_read;

	// open file for reading
	if ((fptr = fopen(file, "rb")) == NULL) {
		perror("Error reading file");
		return 1;
	}

	// send file size
	fseek(fptr, 0L, SEEK_END);
	file_size = ftell(fptr);
	rewind(fptr);
	write(consockfd, &file_size, sizeof(file_size));

	// send file
	while ((bytes_read = fread(sndbuf, 1, bufsize, fptr))) {
		write(consockfd, sndbuf, bytes_read);
	}

	fclose(fptr);
	return 0;
}

int recvfile(void *rcvbuf, int bufsize, int consockfd, char *file)
{
	FILE *fptr;
	long file_size, bytes_rem;
	size_t bytes_read;

	// open file for writing
	if ((fptr = fopen(file, "wb")) == NULL) {
		perror("Error writing file");
		return 1;
	}

	// recv file size
	read(consockfd, &file_size, sizeof(file_size));

	// recv file
	bytes_rem = file_size;
	while (bytes_rem) {
		bytes_read = read(consockfd, rcvbuf, MIN(bytes_rem, bufsize));
		fwrite(rcvbuf, 1, bytes_read, fptr);
		bytes_rem -= bytes_read;
	}

	fclose(fptr);
	return 0;
}