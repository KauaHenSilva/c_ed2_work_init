#pragma once

#define QTD_TESTES 30
#define QTD_CURSO_TESTADOS 1000
#define QTD_NOTAS_TESTADOS 1000
#define QTD_ALUNOS_TESTADOS 1000
#define QTD_DISCIPLINA_TESTADOS 1000

#include "../../../structs/arvore_avl.h"
#include "../../../structs/struct_aluno.h"

#include <time.h>

typedef enum enTipoDeOrdenacao
{
  CRESCENTE,
  DECRESCENTE,
  ALEATORIO,
} TipoDeOrdenacao;

typedef enum enTypeValor
{
  NOTAS,
  DISCIPLINAS,
  ALUNOS
} TypeValor;

typedef struct stEstruturaParaTeste
{
  Arvore *arvoreNotas;
  Arvore *arvoreDisciplina;
  ListAluno *alunos;

  ListAluno *alunoProcurar;
  Arvore *notasProcurar;
  Arvore *disciplinaProcurar;
} EstruturaParaTeste;

void vetIntAleatorioSemRepeticao(int *vetor, int qtd);
void vetIntCrescente(int *vetor, int qtd);
void vetIntDecrescente(int *vetor, int qtd);

void mediaTempoEmSegundos(clock_t *tempos, double *mediaTempos);
// void exibirValoresInseridos(Arvore *arvoreCurso_list);
void exbirResultado(double media, char *titulo);

void limparNodes(Arvore *arvore);
void resetarListaValoresArvore(Arvore *arvore_list, int qtd);

void defArvoreListType(Arvore *arvore_list, TipoDeOrdenacao type, int qtd_valores);
