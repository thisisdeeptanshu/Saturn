#include <stdlib.h>
#include <string.h>

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

  // Czech if user accepts name
  printf("this good? %s [y/n]\n", user.name);
  char c_temp;
  scanf(" %c", &c_temp);
  while (getchar() != '\n'); // Prevents scanf from auto-executing
  if (c_temp != 'y' && c_temp != 'Y')
  {
    user.name = "";
    printf("lol");
    return user;
  }

  // Checking if user exists in list of users
  FILE* p_file = fopen("users.txt", "r");
  char* line = NULL;
  size_t len = 0;
  int taken = 0;
  while (getline(&line, &len, p_file) != -1)
  {
    line[strlen(line) - 1] = '\0';
    if (strcmp(line, user.name) == 0)
    {
      user.name = "";
      printf("Unfortunately, that name is taken :(\nBetter luck next time");
      taken = 1;
      break;
    }
  }
  fclose(p_file);
  free(line);
  if (taken) return user;

  // Adding user to list of users
  p_file = fopen("users.txt", "a");
  fputs(user.name, p_file);
  fputs("\n", p_file);
  fclose(p_file);

  // Generate public key

  // Generate private key

  return user;
}
