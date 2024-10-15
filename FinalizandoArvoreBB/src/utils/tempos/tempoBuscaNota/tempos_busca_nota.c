#include "../auxTempo/aux.h"
#include "../tempoBuscaNota/tempos_busca_nota.h"

#include "../../../core/aluno/aluno.h"
#include "../../../core/nota/nota.h"
#include "../../../arvoreBB/arvore_bb.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void tempoDeBuscaNotaDisciplina(EstruturaParaTeste estruturaParaTeste, clock_t *tempo)
{
  Arvore *tempArvore;
  ListAluno *tempAluno;
  clock_t inicio, fim;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
  {
    int achouNota, achouDisciplina, achouAluno;
    tempArvore = NULL;
    tempAluno = NULL;

    inicio = clock();
    achouAluno = searchAluno(estruturaParaTeste.alunos, estruturaParaTeste.alunoProcurar[x].aluno.matricula, &tempAluno);
    achouNota = searchNodeTree(estruturaParaTeste.arvoreNotas, estruturaParaTeste.notasProcurar[x].info, &tempArvore);
    achouDisciplina = searchNodeTree(estruturaParaTeste.arvoreDisciplina, estruturaParaTeste.disciplinaProcurar[x].info, &tempArvore);
    fim = clock();

    if (!achouNota)
      perror("Não achou Nota!");
    if (!achouDisciplina)
      perror("Não achou Disciplina!");
    if (!achouAluno)
      perror("Não achou Aluno!");

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

static void exbirResultado(double media, char *titulo)
{
  printf("Teste: %s\n", titulo);
  printf("Resultado: %f\n\n", media);
}

static void mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

static void tempBusca(EstruturaParaTeste estruturaParaTeste, char *titulo)
{
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeBuscaNotaDisciplina(estruturaParaTeste, &(tempos[i]));

  double mediaTempo;
  mediaTempoEmSegundosDivididoPelaQuantidadeDeTeste(tempos, &mediaTempo);
  exbirResultado(mediaTempo, titulo);
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

static void limparList(ListAluno *aluno)
{
  if (aluno)
  {
    limparList(aluno->prox);
    aluno->prox = NULL;
  }
}

static void setListaAProcurar(EstruturaParaTeste *estrutura)
{
  limparNodes(estrutura->arvoreDisciplina);
  limparNodes(estrutura->arvoreNotas);
  limparList(estrutura->alunos);

  estrutura->arvoreDisciplina = NULL;
  estrutura->arvoreNotas = NULL;
  estrutura->alunos = NULL;

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    insertTree(&(estrutura->arvoreDisciplina), &(estrutura->disciplinaProcurar[x]));

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    insertTree(&(estrutura->arvoreNotas), &(estrutura->notasProcurar[x]));

  for (int x = 0; x < QTDNOTASTESTADOS; x++)
    inserctionAluno(&(estrutura->alunos), estrutura->alunoProcurar[x].aluno);
}

static void defEstruturaParaTesteAluno(EstruturaParaTeste *estrutura, int idx, int value)
{
  estrutura->alunoProcurar[idx].aluno.codigoDoCurso = value;
  estrutura->alunoProcurar[idx].aluno.nome = (char *)malloc(50 * sizeof(char));
  snprintf(estrutura->alunoProcurar[idx].aluno.nome, 50, "%d", value);
  estrutura->alunoProcurar[idx].aluno.matricula = value;
  estrutura->alunoProcurar[idx].aluno.arvoreNota = NULL;
  estrutura->alunoProcurar[idx].aluno.arvoreMatricula = NULL;
  estrutura->alunoProcurar[idx].prox = NULL;
}

static void defEstruturaParaTesteNota(EstruturaParaTeste *estrutura, int idx, int value)
{
  estrutura->notasProcurar[idx].info.nota.codDisciplina = value;
  estrutura->notasProcurar[idx].info.nota.notaFinal = value;
  estrutura->notasProcurar[idx].info.nota.semestreCursado = value;
  estrutura->notasProcurar[idx].dir = NULL;
  estrutura->notasProcurar[idx].esq = NULL;
}

static void defEstruturaParaTesteDisciplina(EstruturaParaTeste *estrutura, int idx, int value)
{
  estrutura->disciplinaProcurar[idx].info.disciplina.codigo = value;
  estrutura->disciplinaProcurar[idx].info.disciplina.cargaHoraria = value;
  estrutura->disciplinaProcurar[idx].info.disciplina.periodo = value;
  estrutura->disciplinaProcurar[idx].dir = NULL;
  estrutura->disciplinaProcurar[idx].esq = NULL;
}

static void setEstruturaParaTest(EstruturaParaTeste estrutura, TipoDeOrdenacao typeOrdenacao, TypeValor typeValor)
{
  int vet[QTDNOTASTESTADOS];

  switch (typeOrdenacao)
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

  switch (typeValor)
  {
  case NOTAS:
    for (int x = 0; x < QTDNOTASTESTADOS; x++)
      defEstruturaParaTesteNota(&estrutura, x, vet[x]);
    break;
  case DISCIPLINAS:
    for (int x = 0; x < QTDNOTASTESTADOS; x++)
      defEstruturaParaTesteDisciplina(&estrutura, x, vet[x]);
    break;
  case ALUNOS:
    for (int x = 0; x < QTDNOTASTESTADOS; x++)
      defEstruturaParaTesteAluno(&estrutura, x, vet[x]);
    break;
  }
}

void testTempoBuscaNotaDisciplina()
{
  Arvore notasProcurar_list[QTDNOTASTESTADOS];
  Arvore disciplinaProcurar_list[QTDNOTASTESTADOS];
  ListAluno alunos_list[QTDNOTASTESTADOS];

  Arvore *disciplina;
  Arvore *nota;
  ListAluno *alunos;

  disciplina = NULL;
  nota = NULL;
  alunos = NULL;

  EstruturaParaTeste estrutura;
  estrutura.alunos = alunos;
  estrutura.arvoreDisciplina = disciplina;
  estrutura.arvoreNotas = nota;
  estrutura.alunoProcurar = alunos_list;
  estrutura.disciplinaProcurar = disciplinaProcurar_list;
  estrutura.notasProcurar = notasProcurar_list;

  setEstruturaParaTest(estrutura, CRESCENTE, NOTAS);
  setEstruturaParaTest(estrutura, CRESCENTE, DISCIPLINAS);
  setEstruturaParaTest(estrutura, CRESCENTE, ALUNOS);
  setListaAProcurar(&estrutura);
  tempBusca(estrutura, "Busca de notas forma cresente");

  setEstruturaParaTest(estrutura, DECRESCENTE, NOTAS);
  setEstruturaParaTest(estrutura, DECRESCENTE, DISCIPLINAS);
  setEstruturaParaTest(estrutura, DECRESCENTE, ALUNOS);
  setListaAProcurar(&estrutura);
  tempBusca(estrutura, "Busca de notas forma decrescente");

  setEstruturaParaTest(estrutura, ALEATORIO, NOTAS);
  setEstruturaParaTest(estrutura, ALEATORIO, DISCIPLINAS);
  setEstruturaParaTest(estrutura, ALEATORIO, ALUNOS);
  setListaAProcurar(&estrutura);
  tempBusca(estrutura, "Busca de notas forma aleatorio");
}
