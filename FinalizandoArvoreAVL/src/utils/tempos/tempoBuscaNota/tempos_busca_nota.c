#include "../auxTempo/aux.h"
#include "../tempoBuscaNota/tempos_busca_nota.h"

#include "../../../core/aluno/aluno.h"
#include "../../../core/nota/nota.h"
#include "../../../core/nota/nota.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void tempoDeBuscaNotaDisciplina(
    Arvore *arvoreNota, Arvore *notasProcurar_list, Arvore *arvoreDisciplina, Arvore *disciplinaProcurar_list, clock_t *tempo)
{
  Arvore *temp;
  clock_t inicio, fim;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
  {
    int achouNota, achouDisciplina;

    inicio = clock();
    achouNota = searchNodeTree(arvoreNota, notasProcurar_list[x].info, &temp);
    achouDisciplina = searchNodeTree(arvoreDisciplina, disciplinaProcurar_list[x].info, &temp);
    fim = clock();

    if (!achouNota)
      perror("Não achou Nota!");
    if (!achouDisciplina)
      perror("Não achou Disciplina!");

    *tempo += (fim - inicio);
  }

  // printf("o tempo de busca: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

// static void exibirValoresBuscado(Arvore *arvoreNotas_list)
// {
//   printf("Valores Buscado: ");
//   for (int i = 0; i < QTDNOTASTESTADOS; i++)
//     printf("[%02d]", arvoreNotas_list[i].info.nota.codDisciplina);
//   printf("\n\n");
// }

static void exbirResultado(double media, char *titulo, Arvore *arvoreNotas_list)
{
  (void)arvoreNotas_list;
  printf("Teste: %s\n", titulo);
  printf("Resultado: %f\n\n", media);
  // exibirValoresBuscado(arvoreNotas_list);
}

static void mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

static void tempBuscaNotaAndDisciplina(
    Arvore *arvoreNota, Arvore *notasProcurar_list, Arvore *arvoreDisciplina, Arvore *disciplinaProcurar_list, char *titulo)
{
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeBuscaNotaDisciplina(arvoreNota, notasProcurar_list, arvoreDisciplina, disciplinaProcurar_list, &(tempos[i]));

  double mediaTempo;
  mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(tempos, &mediaTempo);

  exbirResultado(mediaTempo, titulo, notasProcurar_list);
}

static void limparNodes(Arvore *arvore)
{
  if (arvore)
  {
    limparNodes(arvore->esq);
    limparNodes(arvore->dir);
    arvore->esq = NULL;
    arvore->dir = NULL;
  }
}

static void setNotasInListaAProcurar(Arvore **arvoreNota, Arvore *notasProcurar_list)
{
  limparNodes(*arvoreNota);
  *arvoreNota = NULL;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    insertTree(arvoreNota, &(notasProcurar_list[x]));
}

static void setDisciplinaInListaAProcurar(Arvore **arvoreDisciplina, Arvore *disciplinaProcurar_list)
{
  limparNodes(*arvoreDisciplina);
  *arvoreDisciplina = NULL;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    insertTree(arvoreDisciplina, &(disciplinaProcurar_list[x]));
}

static void defNotaListType(Arvore *arvoreNotas_list, int idx, int value)
{
  arvoreNotas_list[idx].info.nota.codDisciplina = value;
  arvoreNotas_list[idx].info.nota.semestreCursado = value;
  arvoreNotas_list[idx].info.nota.notaFinal = value;
  arvoreNotas_list[idx].dir = NULL;
  arvoreNotas_list[idx].esq = NULL;
}

static void defDisciplinaListType(Arvore *arvoreDisciplina_list, int idx, int value)
{
  arvoreDisciplina_list[idx].info.disciplina.codigo = value;
  arvoreDisciplina_list[idx].info.disciplina.cargaHoraria = value;
  arvoreDisciplina_list[idx].info.disciplina.periodo = value;
  arvoreDisciplina_list[idx].dir = NULL;
  arvoreDisciplina_list[idx].esq = NULL;
}

static void defNotaAndDisciplinaType(Arvore *arvoreNotas, Arvore *arvoreDisciplina, TipoDeOrdenacao type)
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
  {
    defNotaListType(arvoreNotas, i, vet[i]);
    defDisciplinaListType(arvoreDisciplina, i, vet[i]);
  }
}

void testTempoBuscaNotaDisciplina()
{
  Arvore notasProcurar_list[QTDNOTASTESTADOS];
  Arvore disciplinaProcurar_list[QTDNOTASTESTADOS];

  Arvore *disciplina;
  Arvore *nota;

  disciplina = NULL;
  nota = NULL;

  defNotaAndDisciplinaType(notasProcurar_list, disciplinaProcurar_list, CRESCENTE);
  setNotasInListaAProcurar(&nota, notasProcurar_list);
  setDisciplinaInListaAProcurar(&disciplina, disciplinaProcurar_list);
  tempBuscaNotaAndDisciplina(nota, notasProcurar_list, disciplina, disciplinaProcurar_list, "Busca de notas inserido de forma cresente");

  defNotaAndDisciplinaType(notasProcurar_list, disciplinaProcurar_list, DECRESCENTE);
  setNotasInListaAProcurar(&nota, notasProcurar_list);
  setDisciplinaInListaAProcurar(&disciplina, disciplinaProcurar_list);
  tempBuscaNotaAndDisciplina(nota, notasProcurar_list, disciplina, disciplinaProcurar_list, "Busca de notas inserido de forma decrescente");

  defNotaAndDisciplinaType(notasProcurar_list, disciplinaProcurar_list, ALEATORIO);
  setNotasInListaAProcurar(&nota, notasProcurar_list);
  setDisciplinaInListaAProcurar(&disciplina, disciplinaProcurar_list);
  tempBuscaNotaAndDisciplina(nota, notasProcurar_list, disciplina, disciplinaProcurar_list, "Busca de notas inserido de forma decrescente");
}
