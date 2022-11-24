// Client.c
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXIN 20
#define MAXOUT 20

#include"fileSrvUtil.c"

int getreq(char *inbuf, int len) {
  /* Get request char stream */
  printf("REQ: ");              /* prompt */
  memset(inbuf,0,len);          /* clear for good measure */
  fgets(inbuf,len,stdin); /* read up to a EOL */
  inbuf[strcspn(inbuf, "\r\n")] = 0;//trim(inbuf);
  return strlen(inbuf);
}

void client(int sockfd) {
  int bytes_read;
	char sndbuf[MAXOUT], cmd[MAXOUT], arg[MAXOUT], rcvbuf[MAXIN];

	while (getreq(sndbuf, MAXOUT) > 0) {
		write(sockfd, sndbuf, strlen(sndbuf));

		if (strncmp(sndbuf, "echo", 4) == 0) {
			memset(rcvbuf, 0, MAXIN);
			bytes_read = read(sockfd, rcvbuf, MAXIN);
			write(STDOUT_FILENO, rcvbuf, bytes_read);
			printf("\n");
		}
		else if (strncmp(sndbuf, "get", 3) == 0) {
			sscanf(sndbuf, "%s %s", cmd, arg);
			if (recvfile(rcvbuf, MAXIN, sockfd, arg) == 0)
				printf("Recieved file: %s\n", arg);
		}
		else if (strncmp(sndbuf, "put", 3) == 0) {
			sscanf(sndbuf, "%s %s", cmd, arg);
			if (sendfile(sndbuf, MAXOUT, sockfd, arg) == 0)
				printf("Sent file: %s\n", arg);
		}
	}
}

// Server address
//struct hostent *buildServerAddr(struct sockaddr_in *serv_addr,
void buildServerAddr(struct sockaddr_in *serv_addr,
	char *serverIP, int portno) {
  /* Construct an address for remote server */
  memset((char *) serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr->sin_family = AF_INET;
  inet_aton(serverIP, &(serv_addr->sin_addr));
  serv_addr->sin_port = htons(portno);
 }


int main() {
	//Client protocol
	char *serverIP = "127.0.0.1";
	int sockfd, portno = 5033;
	struct sockaddr_in serv_addr;
	
	buildServerAddr(&serv_addr, serverIP, portno);

	/* Create a TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd<0) perror("Socket connection break\n");

	/* Connect to server on port */
	int conn_stat=connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	
  if(conn_stat<0) perror("error occured in connection\n");
  printf("Connected to %s:%d\n",serverIP, portno);

	/* Carry out Client-Server protocol */
	client(sockfd);

	/* Clean up on termination */
	close(sockfd);
}
