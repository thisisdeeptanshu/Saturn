#include <stdlib.h>

#define MAX_USERNAME_LENGTH 21

typedef struct {
  char* name;
  char* publicKey;
  char* privateKey;
} user;

int in_combination(char to_check)
{
  char combination[36] = "abcdefghijklmnopqrstuvwxyz123456789_";
  for (int i = 0; i < 36; i++)
  {
    if (combination[i] == to_check) return 1;
  }
  return 0;
}

user create_user()
{
  user user;
  char temp[MAX_USERNAME_LENGTH - 1];

  // Getting the username
  printf("enter username (can only contain lowercase-letters, numbers and underscores, max length = %d)\n", MAX_USERNAME_LENGTH - 1);
  scanf("%s", temp);
  user.name = (char*) malloc(0);
  int ending = MAX_USERNAME_LENGTH;
  for (int i = 0; i < MAX_USERNAME_LENGTH - 1; i++)
  {
    if (in_combination(temp[i]))
    {
      user.name = (char*) realloc(user.name, sizeof(char) * (i + 1));
      user.name[i] = temp[i];
    }
    else
    {
      ending = i;
      break;
    }
  }
  user.name[ending] = '\0';

  // printf("%s", user.name);

  // if (user.name == "") printf("shit");

  // Generate public key

  // Generate private key

  return user;
}
