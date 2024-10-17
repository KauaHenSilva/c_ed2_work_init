#pragma once

#define QTDTESTES 100
#define QTDCURSOTESTADOS 1000

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

void defCurso(Arvore *arvoreCurso_list, int idx, int value);
void resetarValoresDaArvoreCurso(Arvore *raizCurso);
void restarListaValoresListaCurso(Arvore *arvoreCurso_list);
void defCursoType(Arvore *cursos_list, TipoDeOrdenacao type);
