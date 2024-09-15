#pragma once

// - Ordem: Código da Disciplina
// - Free: node.
typedef struct stNodeMatricula
{
  int codDisciplina;
  struct stNodeMatricula *dir;
  struct stNodeMatricula *esq;
} NodeMatricula;