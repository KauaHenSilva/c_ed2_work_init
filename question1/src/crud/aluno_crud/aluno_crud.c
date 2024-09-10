#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aluno_crud.h>
#include <curso_crud.h>
#include <utils.h>

ListAluno *alocAluno()
{
  ListAluno *aluno = (ListAluno *)malloc(sizeof(ListAluno));
  aluno->codigoDoCurso = -1;
  aluno->matricula = -1;
  aluno->nodeMatricula = NULL;
  aluno->ant = NULL;
  aluno->prox = NULL;
  aluno->nodeNota = NULL;
  aluno->nome = NULL;
  return aluno;
}

void freeAluno(ListAluno *aluno)
{
  free(aluno->nome);
  free(aluno);
  aluno = NULL;
}

void freeAlunosList(ListAluno *alunos)
{
  if (!alunos)
    return;

  freeAlunosList(alunos->prox);

  freeAluno(alunos);
}

int prencherAluno(ListAluno *aluno, NodeCurso *cursos)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 0;
  confirm = getInt(&aluno->codigoDoCurso, "Digite o codigo do Curso: ");

#if DEBUG_MODE
  if (isCurseOpen(cursos, aluno->codigoDoCurso) == 0)
  {
    printf("Curso não cadastrado!\n");
    return 1;
  }
#endif

  if (confirm)
    confirm = getInt(&aluno->matricula, "Digite a matricula do aluno: ");

  if (confirm)
    confirm = getString(&aluno->nome, "Digite o nome do aluno: ");

  // Falta alguns.

  if (!confirm)
  {
    printf("Não foi possivel execultar o prencher aluno!");
    return 1;
  }
  return 0;
}

void showAluno(ListAluno *aluno)
{
  printf("Aluno: \n");
  printf("\tid: %d\n", aluno->codigoDoCurso);
  printf("\tNome: %s\n", aluno->nome);
}

void showAllAlunos(ListAluno *alunos)
{
  if (!alunos)
    return;

  showAllAlunos(alunos->prox);
  showAluno(alunos);
}

static ListAluno *inserction(ListAluno *alunos, ListAluno *new)
{
  if (!alunos)
    return new;
  else
  {
    ListAluno *aux = alunos;
    while (aux->prox && strcmp(new->nome, aux->prox->nome))
      aux = aux->prox;

    new->prox = aux->prox;
    aux->prox = new;
    return alunos;
  }
}

int cadastrarAlunos(ListAluno **alunos, NodeCurso *cursos)
{
  ListAluno *new = alocAluno();
  if (prencherAluno(new, cursos))
  {
    freeAluno(new);
    return 1;
  }

  *alunos = inserction(*alunos, new);
  return 0;
}
