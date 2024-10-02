#pragma once

#include "arvore_bb.h"

typedef struct stAluno
{
  int matricula;
  char *nome;
  int codigoDoCurso;
  struct stArvore *arvoreNota;
  struct stArvore *arvoreMatricula;
} Aluno;

// - Ordem: Alfabética por Nome do Aluno
// - Free: node, nome, nodeNota, nodeMatricula.
typedef struct stListAluno
{
  Aluno aluno;
  struct stListAluno *prox;
} ListAluno;
