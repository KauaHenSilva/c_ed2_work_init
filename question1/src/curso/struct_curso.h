#pragma once

typedef struct NodeCurso
{
  int codigo;
  char *nomeDoCurso;
  int quantidadeDePeriodo;
  // Arvore das disciplinas;

  struct NodeCurso *esq;
  struct NodeCurso *dir;
} NodeCurso;