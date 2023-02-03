#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500
#define PORTNUM 2300

int main()
{
  char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
  char* server_name;
  int len, mysocket;
  struct sockaddr_in dest;

  mysocket = socket(AF_INET, SOCK_STREAM, 0);

  memset(&dest, 0, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr("127.0.0.1");
  dest.sin_port = htons(PORTNUM);

  connect(mysocket, (struct sockaddr*) &dest, sizeof(struct sockaddr_in));

  len = recv(mysocket, buffer, MAXRCVLEN, 0);
  buffer[len] = '\0';
  printf("Received %s\n", buffer);

  send(mysocket, " ", strlen(" "), 0);

  len = recv(mysocket, buffer, MAXRCVLEN, 0);
  buffer[len] = '\0';
  server_name = buffer;

  send(mysocket, "why helo there", strlen("why helo there"), 0);

  close(mysocket);
  return EXIT_SUCCESS;
}
