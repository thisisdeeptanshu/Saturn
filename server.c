#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include "string.h"

#define MAXRCVLEN 500
#define PORTNUM 2300
#define MAX 2300

int main()
{
  struct sockaddr_in dest; /* socket info about the machine connecting to us*/
  struct sockaddr_in serv; /* socket info about our server */
  int mysocket;            /* socket used to listen or incoming connections */
  socklen_t socksize = sizeof(struct sockaddr_in);
  char* ip = "127.0.0.1";
  char* name = "Saturn";
  char buffer[MAXRCVLEN + 1];

  memset(&serv, 0, sizeof(serv));           /* zero the struct before filling the fields */
  serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
  serv.sin_addr.s_addr = inet_addr(ip); /* set our address to any interface */
  serv.sin_port = htons(PORTNUM);           /* set the server port number */

  mysocket = socket(AF_INET, SOCK_STREAM, 0);

  /* bind serv information to mysocket */
  bind(mysocket, (struct sockaddr *) &serv, sizeof(struct sockaddr));

  /* start listening allowing a queue of up to 1 pending connection */
  listen(mysocket, 1);
  int consocket = accept(mysocket, (struct sockaddr *) &dest, &socksize);

  while (consocket)
  {
    char* connection_name = inet_ntoa(dest.sin_addr);

    printf("Incoming connection from %s\n", connection_name);
    char* msg = concat("Connected to ", name);
    msg = concat(msg, " - ");
    msg = concat(msg, ip);
    send(consocket, msg, strlen(msg), 0);
    recv(consocket, buffer, 500, 0);
    send(consocket, name, strlen(name), 0);

    while (1)
    {
      // Receiving
      int len = recv(consocket, buffer, 500, 0);
      buffer[len] = '\0';
      if (strcmp(buffer, "exit") == 0) break;

      // Sending
      printf("%s> %s\n", connection_name, buffer);
      send(consocket, "s", strlen("s"), 0);
    }

    close(consocket);
    consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  }

  close(mysocket);
  return EXIT_SUCCESS;
}
