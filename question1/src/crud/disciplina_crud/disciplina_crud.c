#include <stdio.h>
#include <stdlib.h>

#include <disciplina_crud.h>
#include <curso_crud.h>
#include <utils.h>

NodeDisciplina *alocDisciplina()
{
  NodeDisciplina *new = (NodeDisciplina *)malloc(sizeof(NodeDisciplina));
  new->cargaHoraria = -1;
  new->codDisciplina = -1;
  new->periodo = -1;
  new->nomeDaDisciplina = NULL;
  new->dir = NULL;
  new->esq = NULL;
  return new;
}

void freeNodeDisciplina(NodeDisciplina *node)
{
  free(node->nomeDaDisciplina);
  free(node);
}

void freeNodeDisciplinas(NodeDisciplina *node)
{
  if (!node)
    return;

  freeNodeDisciplinas(node->esq);
  freeNodeDisciplinas(node->dir);

  freeNodeDisciplina(node);
}

int prencherDisciplina(NodeDisciplina *node)
{
  int confirm = 1;

  if (confirm)
    confirm = getInt(&node->codDisciplina, "Digite o codigo da disciplina: ");

  if (confirm)
    // Fazer a verificação se o periodo é valido.
    confirm = getInt(&node->periodo, "Digite o periodo da disciplina: ");

  if (confirm)
    // Fazer a verificação se a carga horaria é valida. multiplo de 15 e entre 30 e 90.
    confirm = getInt(&node->cargaHoraria, "Digite a carga horaria da disciplina: ");

  if (confirm)
    confirm = getString(&node->nomeDaDisciplina, "Digite o nome da disciplina: ");

  if (!confirm)
  {
    printf("Não foi possivel execultar o prencher disciplina!");
    return 1;
  }
  return 0;
}

void showDisciplina(NodeDisciplina *disciplina)
{
  printf("Disciplina: \n");
  printf("\tid: %d\n", disciplina->codDisciplina);
  printf("\tNome: %s\n", disciplina->nomeDaDisciplina);
}

void showAllDisciplina(NodeDisciplina *disciplina)
{
  if (!disciplina)
    return;

  showAllDisciplina(disciplina->esq);
  showAllDisciplina(disciplina->dir);
  showDisciplina(disciplina);
}

static NodeDisciplina *inserction(NodeDisciplina *raiz, NodeDisciplina *node)
{
  if (!raiz)
    return node;
  else
  {
    if (node->codDisciplina < raiz->codDisciplina)
      raiz->esq = inserction(raiz->esq, node);
    else
      raiz->dir = inserction(raiz->dir, node);
  }

  return raiz;
}

void cadastrarDisciplinas(NodeCurso *curso)
{
  NodeDisciplina *new = alocDisciplina();
  if (prencherDisciplina(new))
  {
    freeNodeDisciplina(new);
    return;
  }

  // temporario, para inserir no ultimo curso.
  NodeCurso *aux = curso;
  while (aux->dir)
    aux = aux->dir;

  aux->nodeDisciplina = inserction(aux->nodeDisciplina, new);
}