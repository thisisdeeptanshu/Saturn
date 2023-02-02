#include <stdlib.h>

#define MAX_USERNAME_LENGTH 20

typedef struct {
  char* name;
  char* publicKey;
  char* privateKey;
} user;

int check_if_number_letter_combination()
{
}

user create_user()
{
  user user;
  char temp[MAX_USERNAME_LENGTH];

  // Getting the username
  printf("enter username (must not contain space, max length = 20)\n");
  scanf("%s", temp);
  user.name = (char*) malloc(0);
  for (int i = 0; i < MAX_USERNAME_LENGTH; i++)
  {
    if (temp[i] != '')
    {
      user.name = (char*) realloc(user.name, sizeof(char) * (i + 1));
      user.name[i] = temp[i];
      printf("%c\n", temp[i]);
    }
    else break;
  }
  printf("asd");

  // printf("%s", user.name);

  // if (user.name == "") printf("shit");

  // Generate public key

  // Generate private key

  return user;
}
