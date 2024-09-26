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

static void mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(clock_t *tempos, double *mediaTempos)
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
    int achou;

    inicio = clock();
    achou = buscarNotas(notas, notasProcurar[x].nota.codDisciplina, &temp);
    fim = clock();

    if (!achou)
      perror("Não achou!");

    *tempo += (fim - inicio);
  }

  // printf("o tempo de busca: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

// static void exibirValoresBuscado(NodeNota *notas)
// {
//   printf("Valores Buscado: ");
//   for (int i = 0; i < QTDNOTASTESTADOS; i++)
//     printf("[%02d]", notas[i].nota.codDisciplina);
//   printf("\n\n");
// }

static void exbirResultado(double media, char *titulo, NodeNota *notas)
{
  (void)notas;
  printf("Teste: %s", titulo);
  printf("Resultado: %f\n\n", media);
  // exibirValoresBuscado(notas);
}

static void tempBuscaNota(ListAluno aluno, NodeNota *nodeNota, char *titulo)
{
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeBuscaNota(aluno.aluno.nodeNota, nodeNota, &(tempos[i]));

  double mediaTempo;
  mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(tempos, &mediaTempo);

  exbirResultado(mediaTempo, titulo, aluno.aluno.nodeNota);
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

static void setNotaAluno(ListAluno *aluno, NodeNota *notas)
{
  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    inserctionNota(&aluno->aluno.nodeNota, &(notas[x]));
}

static void setNotasAlunoAndListaAProcurar(ListAluno *aluno, NodeNota *notasProcurar, TipoDeOrdenacao type)
{
  limparNodes(aluno->aluno.nodeNota);
  aluno->aluno.nodeNota = NULL;

  defNotaType(notasProcurar, type);

  setNotaAluno(aluno, notasProcurar);
}

void testTempoBuscaNotaDisciplina()
{
  NodeNota notasProcurar[QTDNOTASTESTADOS];
  ListAluno aluno;

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar, CRESCENTE);
  tempBuscaNota(aluno, notasProcurar, "Busca de notas inserido de forma cresente");

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar, DECRESCENTE);
  tempBuscaNota(aluno, notasProcurar, "Busca de notas inserido de forma decrescente");

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar, ALEATORIO);
  tempBuscaNota(aluno, notasProcurar, "Busca de notas inserido de forma aleatória");
}