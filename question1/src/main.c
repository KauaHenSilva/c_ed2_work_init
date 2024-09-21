#include <stdio.h>
#include <stdlib.h>

#include "crud/aluno_crud/aluno_crud.h"
#include "crud/curso_crud/curso_crud.h"
#include "crud/disciplina_crud/disciplina_crud.h"
#include "crud/matricula_crud/matricula_crud.h"
#include "crud/nota_crud/nota_crud.h"

#include "actions/actions.h"

void menu(int *opcao)
{
  printf("1 - Cadastrar Curso\n");
  printf("2 - Cadastrar Disciplina\n");
  printf("3 - Cadastrar Aluno\n");
  printf("4 - Cadastrar Matricula\n");
  printf("5 - Cadastrar Nota\n");
  printf("6 - Mostrar Todos os Cursos\n");
  printf("7 - Mostrar Todos os Alunos de um Curso\n");
  printf("8 - Mostrar Todas as Disciplinas de um Curso\n");
  printf("9 - Mostrar Disciplinas de um Período de um Curso\n");
  printf("10 - Mostrar Disciplinas de um Aluno\n");
  printf("11 - Mostrar Notas de um Aluno por Período\n");
  printf("12 - Sair\n");
  printf("Digite a opção desejada: ");
  scanf("%d", opcao);
}

int main()
{
  ListAluno *alunos = NULL;
  NodeCurso *cursos = NULL;

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}