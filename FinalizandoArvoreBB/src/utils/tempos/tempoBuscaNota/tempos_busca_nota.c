#include "../auxTempo/aux.h"
#include "../tempoBuscaNota/tempos_busca_nota.h"

#include "../../../core/aluno/aluno.h"
#include "../../../core/nota/nota.h"
#include "../../../core/nota/nota.h"
#include "../../../arvoreBB/arvore_bb.h"


#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void defNotaTime(Arvore *arvoreNotas_list, int idx, int value)
{
  arvoreNotas_list[idx].info.nota.codDisciplina = value;
  arvoreNotas_list[idx].info.nota.semestreCursado = value;
  arvoreNotas_list[idx].info.nota.notaFinal = value;
  arvoreNotas_list[idx].dir = NULL;
  arvoreNotas_list[idx].esq = NULL;
}

static void defNotaType(Arvore *arvoreNotas, TipoDeOrdenacao type)
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
    defNotaTime(arvoreNotas, i, vet[i]);
}

static void mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

static void tempoDeBuscaNota(Arvore *arvoreNotas, Arvore *notasProcurar_list, clock_t *tempo)
{
  Arvore *temp;
  clock_t inicio, fim;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
  {
    int achou;

    inicio = clock();
    achou = searchNodeTree(arvoreNotas, notasProcurar_list[x].info, &temp);
    fim = clock();

    if (!achou)
      perror("Não achou!");

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

static void tempBuscaNota(ListAluno aluno, Arvore *notasProcurar_list, char *titulo)
{
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeBuscaNota(aluno.aluno.arvoreNota, notasProcurar_list, &(tempos[i]));

  double mediaTempo;
  mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(tempos, &mediaTempo);

  exbirResultado(mediaTempo, titulo, notasProcurar_list);
}

static void limparNodes(Arvore *arvoreNotas)
{
  if (arvoreNotas)
  {
    limparNodes(arvoreNotas->esq);
    limparNodes(arvoreNotas->dir);
    arvoreNotas->esq = NULL;
    arvoreNotas->dir = NULL;
  }
}

static void setNotaAluno(ListAluno *aluno, Arvore *arvoreNotas_list)
{
  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    insertTree(&aluno->aluno.arvoreNota, &(arvoreNotas_list[x]));
}

static void setNotasAlunoAndListaAProcurar(ListAluno *aluno, Arvore *notasProcurar_list, TipoDeOrdenacao type)
{
  limparNodes(aluno->aluno.arvoreNota);
  aluno->aluno.arvoreNota = NULL;

  defNotaType(notasProcurar_list, type);
  setNotaAluno(aluno, notasProcurar_list);
}

void testTempoBuscaNotaDisciplina()
{
  Arvore notasProcurar_list[QTDNOTASTESTADOS];
  ListAluno aluno;
  aluno.aluno.arvoreNota = NULL;

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar_list, CRESCENTE);
  tempBuscaNota(aluno, notasProcurar_list, "Busca de notas inserido de forma cresente");

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar_list, DECRESCENTE);
  tempBuscaNota(aluno, notasProcurar_list, "Busca de notas inserido de forma decrescente");

  setNotasAlunoAndListaAProcurar(&aluno, notasProcurar_list, ALEATORIO);
  tempBuscaNota(aluno, notasProcurar_list, "Busca de notas inserido de forma aleatória");
}
