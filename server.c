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
#include "user.h"
#include "dictionary.h"

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
    char* temp = concat("Connected to ", name);
    temp = concat(temp, " - ");
    temp = concat(temp, ip);
    send(consocket, temp, strlen(temp), 0);
    recv(consocket, buffer, 500, 0);
    send(consocket, name, strlen(name), 0);
    free(temp);

    while (1)
    {
      char* msg;

      // Receiving
      int len = recv(consocket, buffer, 500, 0);
      buffer[len] = '\0';

      printf("%s> %s\n", connection_name, buffer);

      // Evaluating
      if (strcmp(buffer, "exit") == 0) break;
      else if (strcmp(buffer, "hi") == 0 || strcmp(buffer, "hello") == 0)
      {
        msg = "why hello there!";
      }
      else if (strstr(buffer, "login") != NULL)
      {
        char** args = malloc(0);
        int count = 0;
        char* token = strtok(buffer, " ");
        while (token)
        {
          args = realloc(args, sizeof(char[20]) * (count + 1));
          args[count] = token;
          token = strtok(NULL, " ");
          count++;
        }
        args[1] = check_username(args[1]);
        msg = concat("This good? [y/n]: ", args[1]);
      }
      else if (strstr(buffer, "signup") != NULL)
      {
      }
      else msg = " ";

      // Sending
      send(consocket, msg, strlen(msg), 0);
    }

    // free(msg);
    close(consocket);
    consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  }

  close(mysocket);
  return EXIT_SUCCESS;
}
