#pragma once

#define QTDTESTES 100

typedef enum enTipoDeOrdenacao
{
  CRESCENTE,
  DECRESCENTE,
  ALEATORIO,
} TipoDeOrdenacao;

void vetIntAleatorioSemRepeticao(int *vetor, int qtd);
void vetIntCrescente(int *vetor, int qtd);
void vetIntDecrescente(int *vetor, int qtd);
