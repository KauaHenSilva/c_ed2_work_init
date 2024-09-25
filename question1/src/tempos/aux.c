#include "aux.h"
#include <stdlib.h>
#include <stdio.h>

void vetIntAleatorioSemRepeticao(int *vetor, int qtd)
{
  for (int i = 0; i < qtd; i++)
  {
    int num = rand() % (qtd * 2);
    int j = 0;

    int isRepetido = 0;
    for (j = 0; j < i && !isRepetido; j++)
      if (vetor[j] == num)
        isRepetido = 1;

    if (!isRepetido)
      vetor[i] = num;
    else
      i--;
  }
}

void vetIntCrescente(int *vetor, int qtd)
{
  for (int i = 0; i < qtd; i++)
    vetor[i] = i;
}

void vetIntDecrescente(int *vetor, int qtd)
{
  for (int i = 0; i < qtd; i++)
    vetor[i] = qtd - i;
}
