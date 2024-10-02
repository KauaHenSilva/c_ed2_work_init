#pragma once

#include "struct_disciplina.h"

typedef struct stCurso
{
  int codigo;
  int quantidadeDePeriodo;
  char *nomeDoCurso;
  struct stArvore *arvoreDisciplinas;
} Curso;
