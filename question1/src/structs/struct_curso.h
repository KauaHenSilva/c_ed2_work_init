#pragma once

#include <struct_disciplina.h>

// - **Ordem:** Código do Curso
typedef struct NodeCurso
{
  int codigo;
  char *nomeDoCurso;
  int quantidadeDePeriodo;
  NodeDisciplina *nodeDisciplina;
  struct NodeCurso *esq;
  struct NodeCurso *dir;
} NodeCurso;