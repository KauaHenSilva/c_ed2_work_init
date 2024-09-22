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
      if (strcmp(buffer, "sair") != 0)
      {
        *string = (char *)malloc(strlen(buffer) + 1);
        if (*string != NULL)
          strcpy(*string, buffer);
      }

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
int getIntMult5(int *inteiro, const char *msg)
{
  int isOk = 1;

  int mult5entre30e90[] = {30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90};

  printf("%s", msg);
  inteiro = mult5entre30e90[rand() % 13];

  return isOk;
}
#else
int getInt(int *inteiro, const char *msg)
{
  int isOk = 1;

  printf("%s", msg);
  if (scanf("%d", inteiro) == 0)
    isOk = 0;

  while (getchar() != '\n')
    ;
  return isOk;
}

int getIntMult5(int *inteiro, const char *msg)
{
  int isOk;
  int mult5entre30e90[] = {30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90};

  do
  {
    printf("%s", msg);
    scanf("%d", inteiro);

    while (getchar() != '\n')
      ;

    isOk = 0;
    for (int i = 0; i < 13 && !isOk; i++)
      if (*inteiro == mult5entre30e90[i])
        isOk = 1;

    if (!isOk)
      printf("Valor inválido! Digite um valor múltiplo de 5 entre 30 e 90.\n");

  } while (!isOk);

  return isOk;
}
#endif
