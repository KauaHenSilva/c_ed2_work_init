#pragma once

// -**Ordem : **Código da Disciplina
typedef struct stNodeMatricula
{
  int codDisciplina;
  struct stNodeMatricula *dir;
  struct stNodeMatricula *esq;
} NodeMatricula;