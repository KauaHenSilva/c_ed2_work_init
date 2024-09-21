#pragma once

#include "struct_nota.h"
#include "struct_matricula.h"

typedef struct Aluno
{
  int matricula;
  char *nome;
  int codigoDoCurso;
  NodeNota *nodeNota;
  NodeMatricula *nodeMatricula;
} Aluno;

// - Ordem: Alfabética por Nome do Aluno
// - Free: node, nome, nodeNota, nodeMatricula.
typedef struct stListAluno
{
  Aluno aluno;
  struct stListAluno *prox;
  struct stListAluno *ant;
} ListAluno;
