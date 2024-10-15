#pragma once

#include "info/info.h"

typedef union unInfo
{
  Curso curso;
  Disciplina disciplina;
  Nota nota;
  Matricula matricula;
  int codigo;
} Info;

typedef struct stArvore
{
  Info info;
  int altura;
  struct stArvore *esq;
  struct stArvore *dir;
} Arvore;
