#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

#if DEBUG_MODE
int getString(char **string, const char *msg)
{
  printf("%s", msg);

  // Simulate user input
  char buffer[1024];
  int valor = rand() % 1000000000;
  snprintf(buffer, sizeof(buffer), "25%d\n", valor);

  *string = (char *)malloc(strlen(buffer) + 1);
  if (*string != NULL)
    strcpy(*string, buffer);

  printf("%s", buffer);
  return string ? 1 : 0;
}
#else
int getString(char **string, const char *msg)
{
  char buffer[1024];
  while (1)
  {
    printf("%s", msg);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "sair") == 0)
        return 0;

      *string = (char *)malloc(strlen(buffer) + 1);
      if (*string != NULL)
        strcpy(*string, buffer);

      return string ? 1 : 0;
    }
  }
}
#endif

#if DEBUG_MODE
int getInt(int *inteiro, const char *msg)
{
  char buffer[1024];
  printf("%s", msg);

  // Simulate user input
  int valor = rand() % 2000000;
  snprintf(buffer, sizeof(buffer), "25%d\n", valor);

  printf("%s", buffer);

  int is_number = 1;
  for (int i = 0; buffer[i] != '\n' && is_number == 1; i++)
    if (!isdigit(buffer[i]))
      is_number = 0;

  if (is_number)
    *inteiro = atoi(buffer);

  return is_number;
}
#else
int getInt(int *inteiro, const char *msg)
{
  char buffer[1024];
  while (1)
  {
    printf("%s", msg);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "sair") == 0)
        return 0;

      int is_number = 1;
      for (int i = 0; buffer[i] != '\0' && isdigit(buffer[i]); i++)
        is_number = 0;

      if (is_number)
      {
        *inteiro = atoi(buffer);
        return 1;
      }
    }

    printf("Valor invalido!\n\n");
  }
}
#endif
