#include <stdio.h>
#include "actions.h"

#include "../crud/aluno_crud/aluno_crud.h"

void mostrarTodosOsAlunosDeUmCurso(NodeCurso *curso, ListAluno *alunos)
{
  if (alunos)
  {
    if (curso->curso.codigo == alunos->aluno.codigoDoCurso)
      showAluno(alunos);
    mostrarTodosOsAlunosDeUmCurso(curso, alunos->prox);
  }
}

void mostrarNotasDeUmAlunoPorPeriodo(NodeNota *raiz, int periodo)
{
  if (raiz != NULL)
  {
    mostrarNotasDeUmAlunoPorPeriodo(raiz->esq, periodo);
    if (raiz->nota.semestreCursado == periodo){
      printf("Codigo da disciplina: %d\n", raiz->nota.codDisciplina);
      printf("Semestre cursado: %d\n", raiz->nota.semestreCursado);
      printf("Nota Final: %d\n", raiz->nota.notaFinal);
    }
    mostrarNotasDeUmAlunoPorPeriodo(raiz->dir, periodo);
  }
}