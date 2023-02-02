#include <stdio.h>
#include "user.h"

int main()
{
  user a = create_user();
  printf("%s", a.name);
  return 0;
}
