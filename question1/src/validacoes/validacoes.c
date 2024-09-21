#include "validacoes.h"

#include "../crud/curso_crud/curso_crud.h"
#include "../crud/aluno_crud/aluno_crud.h"

#include <stdio.h>

void isPeriodoValido(int *periodo, int quantidadeDePeriodo)
{
  while (*periodo < 1 || *periodo > quantidadeDePeriodo)
  {
    printf("Periodo invalido! Digite um periodo valido: ");
    scanf("%d", periodo);
  }
}

void isCursoValido(int *codigoDoCurso, NodeCurso *cursos, NodeCurso **atual)
{
  while (!atual)
  {
    printf("Digite o código do curso: ");
    scanf("%d", codigoDoCurso);
    search_course(cursos, *codigoDoCurso, *atual);

    if (!atual)
      printf("Curso não encontrado!\n");
  }
}

void isAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual)
{
  while (!atual)
  {
    printf("Digite a matricula do aluno: ");
    scanf("%d", matricula);
    search_aluno(alunos, *matricula, atual);

    if (!atual)
      printf("Aluno não encontrado!\n");
  }
}
