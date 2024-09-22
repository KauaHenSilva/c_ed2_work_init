#pragma once

typedef struct Nota
{
  int codDisciplina;
  int semestreCursado;
  int notaFinal;
} Nota;

// - Ordem: Código da Disciplina
// - Free: node.
typedef struct stNodeNota
{
  Nota nota;
  struct stNodeNota *esq;
  struct stNodeNota *dir;
} NodeNota;
