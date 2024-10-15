#pragma once

#define QTDTESTES 100

#include "../../../structs/arvore_avl.h"
#include "../../../structs/struct_aluno.h"

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
