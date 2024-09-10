#pragma once

// - **Ordem:** Alfabética por Nome do Aluno
typedef struct stAluno
{
  int matricula;
  char *nome;
  int codicoDoCurso;
  // Arvore de notas
  // Arvore de matricula
  struct stAluno *prox;
  struct stAluno *ant;
} Aluno;
