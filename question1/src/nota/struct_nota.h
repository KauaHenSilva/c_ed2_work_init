#pragma once

// -**Ordem : **Código da Disciplina
typedef struct stNodeNota
{
  int codDisciplina;
  int semestreCursado;
  int notaFinal;

  struct stNodeNota *esq;
  struct stNodeNota *dir;
} NodeNota;
