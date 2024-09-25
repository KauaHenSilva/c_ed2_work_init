#include "aux.h"
#include "tempos_busca_nota.h"

#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/nota_crud/nota_crud.h"
#include "../crud/nota_crud/nota_crud.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void defNotaTime(NodeNota *notas, int idx, int value)
{
  notas[idx].nota.codDisciplina = value;
  notas[idx].nota.semestreCursado = value;
  notas[idx].nota.notaFinal = value;
  notas[idx].dir = NULL;
  notas[idx].esq = NULL;
}

static void defNotaType(NodeNota *notas, TipoDeOrdenacao type)
{
  int vet[QTDNOTASTESTADOS];

  switch (type)
  {
  case CRESCENTE:
    vetIntCrescente(vet, QTDNOTASTESTADOS);
    break;
  case DECRESCENTE:
    vetIntDecrescente(vet, QTDNOTASTESTADOS);
    break;
  case ALEATORIO:
    vetIntAleatorioSemRepeticao(vet, QTDNOTASTESTADOS);
    break;
  }

  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    defNotaTime(notas, i, vet[i]);
}

static void mediaTempoEmSegundos(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

static void tempoDeBuscaNota(NodeNota *notas, NodeNota *notasProcurar, clock_t *tempo)
{
  NodeNota *temp;
  clock_t inicio, fim;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
  {
    inicio = clock();
    buscarNotas(notas, notasProcurar[x].nota.codDisciplina, &temp);
    fim = clock();

    *tempo += (fim - inicio);
  }

  printf("o tempo de busca: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

static void tempBuscaNota(ListAluno aluno, NodeNota *nodeNota, char *titulo)
{
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeBuscaNota(aluno.aluno.nodeNota, nodeNota, &(tempos[i]));

  double mediaTempo;
  mediaTempoEmSegundos(tempos, &mediaTempo);

  printf("%s\n", titulo);
  printf("Media de tempo de execução: %f\n", mediaTempo);
}

static void limparNodes(NodeNota *notas)
{
  if (notas)
  {
    limparNodes(notas->esq);
    limparNodes(notas->dir);
    notas->esq = NULL;
    notas->dir = NULL;
  }
}

static void exibirValoresBuscado(NodeNota *notas)
{

  printf("Valores Buscado: ");
  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    printf("[%02d]", notas[i].nota.codDisciplina);
  printf("\n\n");
}

void testTempoBuscaNotaDisciplina()
{
  NodeNota notasProcurar[QTDNOTASTESTADOS];

  NodeNota notas[QTDNOTASTESTADOS];
  defNotaType(notas, ALEATORIO);

  ListAluno aluno;
  aluno.aluno.nodeNota = NULL;
  defNotaType(notasProcurar, CRESCENTE);
  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    inserctionNota(&aluno.aluno.nodeNota, &notas[i]);

  tempBuscaNota(aluno, notasProcurar, "Busca de notas: Inserido de forma cresente");
  exibirValoresBuscado(notasProcurar);

  limparNodes(aluno.aluno.nodeNota);
  aluno.aluno.nodeNota = NULL;
  defNotaType(notasProcurar, DECRESCENTE);
  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    inserctionNota(&aluno.aluno.nodeNota, &notas[i]);

  tempBuscaNota(aluno, notasProcurar, "Busca de notas: Inserido de forma decrescente");
  exibirValoresBuscado(notasProcurar);

  limparNodes(aluno.aluno.nodeNota);
  aluno.aluno.nodeNota = NULL;
  defNotaType(notasProcurar, ALEATORIO);
  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    inserctionNota(&aluno.aluno.nodeNota, &notas[i]);

  tempBuscaNota(aluno, notasProcurar, "Busca de notas: Inserido de forma aleatória");
  exibirValoresBuscado(notasProcurar);
}