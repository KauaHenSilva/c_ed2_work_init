#pragma once

#define DEBUG_MODE 0

typedef enum
{
  PRIMEIRO_ARGUMENTO_MENOR = 1,
  PRIMEIRO_ARGUMENTO_MAIOR = -1,
  PRIMEIRO_ARGUMENTO_IGUAL = 0
} NomeCmp;

int getString(char **string, const char *msg);
int getInt(int *inteiro, const char *msg);
int getIntMult5(int *inteiro, const char *msg);
NomeCmp myStrCmp(char *texto1, char *texto2);