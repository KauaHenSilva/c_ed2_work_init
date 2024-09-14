#include <stdio.h>
#include <stdlib.h>

#include <disciplina_crud.h>
#include <curso_crud.h>
#include <utils.h>

void alocDisciplina(NodeDisciplina **new)
{
  *new = (NodeDisciplina *)malloc(sizeof(NodeDisciplina));
  (*new)->cargaHoraria = -1;
  (*new)->codDisciplina = -1;
  (*new)->periodo = -1;
  (*new)->nomeDaDisciplina = NULL;
  (*new)->dir = NULL;
  (*new)->esq = NULL;
}

void freeNodeDisciplina(NodeDisciplina *node)
{
  if (node->nomeDaDisciplina)
    free(node->nomeDaDisciplina);

  free(node);
}

void freeNodeDisciplinas(NodeDisciplina *raiz)
{
  if (raiz)
  {
    freeNodeDisciplinas(raiz->esq);
    freeNodeDisciplinas(raiz->dir);
    freeNodeDisciplina(raiz);
  }
}

int prencherDisciplina(NodeDisciplina *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo da disciplina: ";
  confirm = getInt(&node->codDisciplina, enunciado);

  if (confirm)
  {
    enunciado = "Digite o periodo da disciplina: ";
    confirm = getInt(&node->periodo, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite a carga horaria da disciplina: ";
    confirm = getInt(&node->cargaHoraria, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome da disciplina: ";
    confirm = getString(&node->nomeDaDisciplina, enunciado);
  }

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina!");

  return !confirm;
}

void showDisciplina(NodeDisciplina *disciplina)
{
  printf("Disciplina: \n");
  printf("\tid: %d\n", disciplina->codDisciplina);
  printf("\tNome: %s\n", disciplina->nomeDaDisciplina);
}

void showAllDisciplina(NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    showAllDisciplina(disciplina->esq);
    showAllDisciplina(disciplina->dir);
    showDisciplina(disciplina);
  }
}

void search_disciplina(NodeDisciplina *raiz, int code, NodeDisciplina **result)
{
  if (raiz)
  {
    if (raiz->codDisciplina == code)
      *result = raiz;
    else if (raiz->codDisciplina < code)
      search_disciplina(raiz->dir, code, result);
    else if (raiz->codDisciplina > code)
      search_disciplina(raiz->esq, code, result);
  }
}

static void inserction(NodeDisciplina **raiz, NodeDisciplina *node)
{
  if (!*raiz)
    *raiz = node;
  else
  {
    if (node->codDisciplina < (*raiz)->codDisciplina)
      inserction(&(*raiz)->esq, node);
    else
      inserction(&(*raiz)->dir, node);
  }
}

void cadastrarDisciplinas(NodeCurso *curso)
{
  NodeDisciplina *new;
  alocDisciplina(&new);

  if (prencherDisciplina(new))
    freeNodeDisciplina(new);

  if (new)
  {
    NodeCurso *aux = curso;
    inserction(&(aux->nodeDisciplina), new);
  }
}