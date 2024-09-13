#include <matricula_crud.h>
#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

void alocMatricula(NodeMatricula **node)
{
  *node = (NodeMatricula *)malloc(sizeof(NodeMatricula));
  (*node)->codDisciplina = -1;
  (*node)->dir = NULL;
  (*node)->esq = NULL;
}

void freeNodeMatricula(NodeMatricula *node)
{
  free(node);
}

void freeNodeMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    freeNodeMatriculas(raiz->esq);
    freeNodeMatriculas(raiz->dir);
    freeNodeMatricula(raiz);
  }
}

void showMatricula(NodeMatricula *node)
{
  printf("Matricula:\n");
  printf("\tCodDisciplina: %d\n", node->codDisciplina);
}

void showAllMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    showAllMatriculas(raiz->esq);
    showAllMatriculas(raiz->dir);
    showMatricula(raiz);
  }
}

int prencherMatricula(NodeMatricula *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  eneunciado = "Digite o codigo da disciplina!";
  confirm = getInt(&node->codDisciplina, eneunciado);

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina!");

  return !confirm;
}

void inserctionMatricula(NodeMatricula **raiz, NodeMatricula *new)
{
  if (!*raiz)
    *raiz = new;
  else
  {
    if ((*raiz)->codDisciplina < new->codDisciplina)
      inserctionMatricula(&(*raiz)->esq, new);
    else
      inserctionMatricula(&(*raiz)->dir, new);
  }
}

void cadastrarMatriculas(ListAluno *aluno, NodeDisciplina *raizDisciplina)
{
  NodeMatricula *new;
  alocMatricula(&new);

  if (new)
  {
    // insirir no utimo aluno da lista. MUDAR.
    ListAluno *auxAluno = aluno;
    if (auxAluno->prox)
      while (auxAluno->prox->prox)
        auxAluno = auxAluno->prox;

    // inserir no utima disciplina na direita. MUDAR.
    NodeDisciplina *auxDisciplina = raizDisciplina;
    while (auxDisciplina->dir)
      auxDisciplina = auxDisciplina->dir;

    new->codDisciplina = auxDisciplina->codDisciplina;
    inserctionMatricula(&(auxAluno->nodeMatricula), new);
  }
}