#include <stdio.h>
#include "user.h"

int main()
{
  user a = createUser();
  printf("%s", a.name);
  return 0;
}
