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

void mediaTempoEmSegundos(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

// void exibirValoresInseridos(Arvore *arvoreCurso_list)
// {
//   printf("ValoresInseridos: ");
//   for (int i = 0; i < QTDCURSOTESTADOS; i++)
//     printf("[%02d]", arvoreCurso_list[i].info.curso.codigo);
//   printf("\n\n");
// }

void exbirResultado(double media, char *titulo)
{
  printf("Teste: %s\n", titulo);
  printf("Resultado: %f\n\n", media);
}

void defCurso(Arvore *arvoreCurso_list, int idx, int value)
{
  arvoreCurso_list[idx].info.curso.codigo = value;
  arvoreCurso_list[idx].info.curso.quantidadeDePeriodo = rand() % (1000 * 1000);
  arvoreCurso_list[idx].info.curso.arvoreDisciplinas = NULL;
  arvoreCurso_list[idx].info.curso.nomeDoCurso = NULL;
  arvoreCurso_list[idx].dir = NULL;
  arvoreCurso_list[idx].esq = NULL;
}

void resetarValoresDaArvoreCurso(Arvore *raizCurso)
{
  if (raizCurso)
  {
    resetarValoresDaArvoreCurso(raizCurso->esq);
    resetarValoresDaArvoreCurso(raizCurso->dir);
    raizCurso->esq = NULL;
    raizCurso->dir = NULL;
  }
}

void restarListaValoresListaCurso(Arvore *arvoreCurso_list)
{
  for (int x = 0; x < QTDCURSOTESTADOS; x++)
  {
    arvoreCurso_list[x].dir = NULL;
    arvoreCurso_list[x].esq = NULL;
  }
}


void defCursoType(Arvore *cursos_list, TipoDeOrdenacao type)
{
  int vet[QTDCURSOTESTADOS];

  switch (type)
  {
  case CRESCENTE:
    vetIntCrescente(vet, QTDCURSOTESTADOS);
    break;
  case DECRESCENTE:
    vetIntDecrescente(vet, QTDCURSOTESTADOS);
    break;
  case ALEATORIO:
    vetIntAleatorioSemRepeticao(vet, QTDCURSOTESTADOS);
    break;
  default:
    break;
  }

  for (int i = 0; i < QTDCURSOTESTADOS; i++)
    defCurso(cursos_list, i, vet[i]);
}
