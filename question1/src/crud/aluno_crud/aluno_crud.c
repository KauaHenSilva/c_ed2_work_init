#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aluno_crud.h>
#include <curso_crud.h>
#include <matricula_crud.h>

#include <utils.h>

void alocAluno(ListAluno **new)
{
  *new = (ListAluno *)malloc(sizeof(ListAluno));
  (*new)->codigoDoCurso = -1;
  (*new)->matricula = -1;
  (*new)->nome = NULL;
  (*new)->nodeMatricula = NULL;
  (*new)->nodeNota = NULL;
  (*new)->ant = NULL;
  (*new)->prox = NULL;
}

void freeAluno(ListAluno *aluno)
{
  if (aluno->nome)
    free(aluno->nome);

  freeNodeMatriculas(aluno->nodeMatricula);

  free(aluno);
}

void freeAlunosList(ListAluno *alunos)
{
  if (alunos)
  {
    freeAlunosList(alunos->prox);
    freeAluno(alunos);
  }
}

int prencherAluno(ListAluno *aluno, NodeCurso *cursos)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo do Curso: ";
  confirm = getInt(&aluno->codigoDoCurso, enunciado);

#if DEBUG_MODE
  if (isCurseOpen(cursos, aluno->codigoDoCurso) == 0)
  {
    printf("Curso não cadastrado!\n");
    return 1;
  }
#else
  (void)cursos;
#endif

  if (confirm)
  {
    enunciado = "Digite a matricula do aluno: ";
    confirm = getInt(&aluno->matricula, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome do aluno: ";
    confirm = getString(&aluno->nome, enunciado);
  }

  // Falta alguns.

  if (!confirm)
    printf("Não foi possivel execultar o prencher aluno!");

  return !confirm;
}

void showAluno(ListAluno *aluno)
{
  printf("Aluno: \n");
  printf("\tid: %d\n", aluno->codigoDoCurso);
  printf("\tMatricula: %d\n", aluno->matricula);
  printf("\tNome: %s\n", aluno->nome);

  showAllMatriculas(aluno->nodeMatricula);
}

void showAllAlunos(ListAluno *alunos)
{
  if (alunos)
  {
    showAllAlunos(alunos->prox);
    showAluno(alunos);
  }
}

void inserctionAluno(ListAluno **alunos, ListAluno *new)
{
  if (!*alunos)
    *alunos = new;
  else
  {
    // Adidiconar no inicio
    if (new->codigoDoCurso < (*alunos)->codigoDoCurso)
    {
      new->prox = *alunos;
      (*alunos)->ant = new;
      *alunos = new;
    }
    else
    {
      // Adicionar no final
      if (!(*alunos)->prox)
      {
        new->ant = *alunos;
        (*alunos)->prox = new;
      }

      // Adicionar no meio
      else
      {
        ListAluno *aux = *alunos;
        while (aux->prox && strcmp(new->nome, aux->prox->nome))
          aux = aux->prox;

        new->prox = aux;
        new->ant = aux->ant;
        aux->ant->prox = new;
        aux->ant = new;
      }
    }
  }
}

int cadastrarAlunos(ListAluno **alunos, NodeCurso *cursos)
{
  ListAluno *new;
  alocAluno(&new);

  if (prencherAluno(new, cursos))
    freeAluno(new);

  if (new)
    inserctionAluno(alunos, new);

  return new ? 1 : 0;
}
