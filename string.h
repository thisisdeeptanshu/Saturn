#include <stdlib.h>
#include <string.h>

char* concat(char* a, char* b)
{
  char* c = malloc(sizeof(char) * (strlen(a) + strlen(b)));
  strcat(c, a);
  strcat(c, b);
  return c;
}
