// Server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#define MAXREQ 20
#define MAXQUEUE 5
#define MAXOUT 20
#define MAXIN 20

#include"fileSrvUtil.c"

void server(int consockfd) {
	int bytes_read;
	char rcvbuf[MAXIN], cmd[MAXIN], arg[MAXIN], sndbuf[MAXOUT];

	memset(rcvbuf, 0, MAXIN);
	while ((bytes_read = read(consockfd, rcvbuf, MAXIN-1)) > 0) {
		printf("Recvd msg: %s\n", rcvbuf);

		sscanf(rcvbuf, "%s %s", cmd, arg);
		if (strncmp(rcvbuf, "echo", 4) == 0) {
			write(consockfd, arg, strlen(arg));
		}
		else if (strncmp(rcvbuf, "get", 3) == 0) {
			if (sendfile(sndbuf, MAXOUT, consockfd, arg) == 0)
				printf("Sent file: %s\n", arg);
		}
		else if (strncmp(rcvbuf, "put", 3) == 0) {
			if (recvfile(rcvbuf, MAXIN, consockfd, arg) == 0)
				printf("Recieved file: %s\n", arg);
		}

		memset(rcvbuf, 0, MAXIN);
	}
}

int main() {

int lstnsockfd, consockfd, clilen, portno = 5033;
struct sockaddr_in serv_addr, cli_addr;

 memset((char *) &serv_addr,0, sizeof(serv_addr));
 serv_addr.sin_family      = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port        = htons(portno);

// Server protocol
/* Create Socket to receive requests*/
lstnsockfd = socket(AF_INET, SOCK_STREAM, 0);

/* Bind socket to port */
bind(lstnsockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
printf("Bounded to port\n");
while (1) {
   printf("Listening for incoming connections\n");

/* Listen for incoming connections */
   listen(lstnsockfd, MAXQUEUE); 

   //clilen = sizeof(cl_addr);

/* Accept incoming connection, obtaining a new socket for it */
   consockfd = accept(lstnsockfd, (struct sockaddr *) &cli_addr,       
                      &clilen);
   printf("Accepted connection\n");
  
  int pid=fork();
  if(!pid)
   {
    server(consockfd);

    close(consockfd);
   }
  
  }
close(lstnsockfd);
}
