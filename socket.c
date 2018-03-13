
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  int sockfd, newsockfd, portno=80, clilen;
  char buffer[1000],body[1000], tempstr[100];
  struct sockaddr_in serv_addr, cli_addr;
  int n,count=0;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd:%d\n",sockfd);
  if (sockfd<0) {
    perror("ERROR opening socket");
    exit(1);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  printf("Bind now...\n");
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) {
    perror("ERROR on binding");
    exit(1);
  }
  printf("Listen now...\n");
  /*  listen(sockfd,5); */
  listen(sockfd,1);
  clilen = sizeof(cli_addr);
  while (1) {
	    printf("accepting...\n");
	    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	    if (newsockfd<0) {
	      perror("Error on accept");
	      exit(1);
	    }
	    printf("newsockfd:%d\n",newsockfd);

	    bzero(buffer,sizeof(buffer));
	    n = read(newsockfd,buffer,sizeof(buffer)-1);
	    if (n<0) {
	      perror("ERROR reading fro socket");
	      exit(1);
	    }
	    printf("Here is the message (length:%d):\n%s\n",strlen(buffer),buffer);
	    if (strlen(buffer)==0) continue;

	    count++;
	    sprintf(body,"<html><body><h1>Chris count:%d</h1></body></html>\r\n",count);

	    sprintf(buffer,"HTTP/1.1 200 OK\r\n");
	    strcat(buffer,"Date: Mon,  27 Jul 2018 12:28:50 GMT\r\n");
	    sprintf(tempstr,"Content-length: %d\r\n",strlen(body));
	    strcat(buffer,tempstr);
	    strcat(buffer,"Content-Type: text/html\r\n");
	    strcat(buffer,"Connection: Closed\r\n");
	    strcat(buffer,"\r\n");
	    strcat(buffer,body);
	    printf("sending:\n%s\n",buffer);
	    n=write(newsockfd,buffer,strlen(buffer));
	    printf("n=%d\n",n);
  }
  
  printf("happy\n");

}

