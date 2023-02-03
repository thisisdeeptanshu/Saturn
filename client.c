#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "static.h"

#define MAXRCVLEN 500
#define PORTNUM 2300

int main()
{
  char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
  char* server_name;
  char* msg = malloc(sizeof(char) * MAXRCVLEN);
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
  printf("%s\n", buffer);

  send(mysocket, " ", strlen(" "), 0);

  len = recv(mysocket, buffer, MAXRCVLEN, 0);
  buffer[len] = '\0';
  server_name = malloc(sizeof(char) * len);
  memcpy(server_name, buffer, sizeof(char) * len);
  printf("%s", server_name);

  printf("Send 'exit' to close connection.\n");
  printf("Send 'help' for a list of commands.\n");

  while (1)
  {
    // Sending
    printf("Msg: ");
    fgets(msg, MAXRCVLEN, stdin);
    msg[strlen(msg) - 1] = '\0';
    send(mysocket, msg, strlen(msg), 0);
    if (strcmp(msg, "exit") == 0) break;
    else if (strcmp(msg, "help") == 0)
    {
      printf("login <username> <password>\n");
      printf("signup <username> <password>\n");
      printf("username can only contain lowercase-letters, numbers and underscores, max length = %d\n", MAX_USERNAME_LENGTH);
      printf("exit\n\n");
      printf("ONLY TYPE IN LOWERCASE\n");
    }

    // Receiving
    int len = recv(mysocket, buffer, 500, 0);
    buffer[len] = '\0';
    if (strcmp(" ", buffer) != 0)
      printf("%s> %s\n", server_name, buffer);
  }

  free(msg);
  close(mysocket);
  return 0;
}
