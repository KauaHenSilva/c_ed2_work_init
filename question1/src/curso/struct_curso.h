#pragma once

#include <struct_disciplina.h>

typedef struct NodeCurso
{
  int codigo;
  char *nomeDoCurso;
  int quantidadeDePeriodo;
  NodeDisciplina *nodeDisciplina;
  struct NodeCurso *esq;
  struct NodeCurso *dir;
} NodeCurso;