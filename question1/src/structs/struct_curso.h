#pragma once

#include <struct_disciplina.h>

// - Ordem: Código do Curso
// - Free: node, nomeDoCurso, nodeDisciplina.
typedef struct stNodeCurso
{
  int codigo;
  char *nomeDoCurso;
  int quantidadeDePeriodo;
  NodeDisciplina *nodeDisciplina;
  struct stNodeCurso *esq;
  struct stNodeCurso *dir;
} NodeCurso;