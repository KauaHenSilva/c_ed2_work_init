#pragma once

#include <struct_nota.h>
#include <struct_matricula.h>

// - **Ordem:** Alfabética por Nome do Aluno
typedef struct stAluno
{
  int matricula;
  char *nome;
  int codicoDoCurso;
  NodeNota *nodeNota;
  NodeMatricula *nodeMatricula;
  struct stAluno *prox;
  struct stAluno *ant;
} Aluno;
