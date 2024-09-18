#pragma once

#include "struct_nota.h"
#include "struct_matricula.h"

// - Ordem: Alfabética por Nome do Aluno
// - Free: node, nome, nodeNota, nodeMatricula.
typedef struct stListAluno
{
  int matricula;
  char *nome;
  int codigoDoCurso;
  NodeNota *nodeNota;
  NodeMatricula *nodeMatricula;
  struct stListAluno *prox;
  struct stListAluno *ant;
} ListAluno;
