#pragma once

// -**Ordem : **Código da Disciplina
// - **Free:** node.
typedef struct stNodeNota
{
  int codDisciplina;
  int semestreCursado;
  int notaFinal;
  struct stNodeNota *esq;
  struct stNodeNota *dir;
} NodeNota;
