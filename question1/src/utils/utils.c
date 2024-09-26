#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

void clearBuffer()
{
  while (getchar() != '\n')
    ;
}

int getString(char **string, const char *msg)
{
  char buffer[1024];
  do
  {
    printf("%s", msg);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
      *string = (char *)malloc(strlen(buffer) + 1);
      if (*string != NULL)
        strcpy(*string, buffer);
    }

    if (!*string)
      printf("Digite um valor válido!\n");

  } while (*string == NULL);

  return 1;
}

int getInt(int *inteiro, const char *msg)
{
  int isOk;

  do
  {
    isOk = 1;

    printf("%s", msg);
    if (scanf("%d", inteiro) == 0)
      isOk = 0;

    if (*inteiro <= 0)
      isOk = 0;

    if (!isOk)
      printf("Digite um valor válido!\n");

    clearBuffer();
  } while (!isOk);

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
    clearBuffer();

    isOk = 0;
    for (int i = 0; i < 13 && !isOk; i++)
      if (*inteiro == mult5entre30e90[i])
        isOk = 1;

    if (!isOk)
      printf("Valor inválido! Digite um valor múltiplo de 5 entre 30 e 90.\n");

  } while (!isOk);

  return isOk;
}

NomeCmp myStrCmp(char *texto1, char *texto2)
{
  char *temp1, *temp2;

  temp1 = (char *)malloc(sizeof(char) * sizeof(texto1));
  temp2 = (char *)malloc(sizeof(char) * sizeof(texto2));

  strcpy(temp1, texto1);
  strcpy(temp2, texto2);

  for (int x = 0; x < (int)sizeof(temp1); x++)
    if (temp1[x] >= 'A' && temp1[x] <= 'Z')
      temp1[x] += 32;

  for (int x = 0; x < (int)sizeof(temp2); x++)
    if (temp2[x] >= 'A' && temp2[x] <= 'Z')
      temp2[x] += 32;

  NomeCmp resp = strcmp(temp1, temp2);

  if (resp > 0)
    resp = PRIMEIRO_ARGUMENTO_MAIOR;
  else if (resp < 0)
    resp = PRIMEIRO_ARGUMENTO_MENOR;
  else
    resp = PRIMEIRO_ARGUMENTO_IGUAL;

  free(temp1);
  free(temp2);

  return resp;
}