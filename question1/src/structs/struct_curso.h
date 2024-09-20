#pragma once

#include "struct_disciplina.h"

typedef struct Curso
{
  int codigo;
  char *nomeDoCurso;
  int quantidadeDePeriodo;
  NodeDisciplina *nodeDisciplina;
} Curso;

// - Ordem: Código do Curso
// - Free: node, nomeDoCurso, nodeDisciplina.
typedef struct stNodeCurso
{
  Curso curso;
  struct stNodeCurso *esq;
  struct stNodeCurso *dir;
} NodeCurso;