#include <stdio.h>
#include <stdlib.h>

#include <curso_crud.h>
#include <struct_curso.h>
#include <utils.h>

NodeCurso *alocCurso()
{
  NodeCurso *new = (NodeCurso *)malloc(sizeof(NodeCurso));
  new->codigo = -1;
  new->quantidadeDePeriodo = 1;
  new->dir = NULL;
  new->esq = NULL;
  new->nodeDisciplina = NULL;
  new->nomeDoCurso = NULL;
  return new;
}

void freeNodeCurso(NodeCurso *node)
{
  free(node->nomeDoCurso);
  free(node);
}

void freeNodeCursos(NodeCurso *node)
{
  if (!node)
    return;

  freeNodeCursos(node->esq);
  freeNodeCursos(node->dir);

  freeNodeCurso(node);
}

int prencherCurso(NodeCurso *node)
{
  int confirm = 1;

  if (confirm)
    confirm = getInt(&node->codigo, "Digite o codigo do curso: ");

  if (confirm)
    confirm = getInt(
        &node->quantidadeDePeriodo,
        "Digite a quantidade de periodo do curso: ");

  if (confirm)
    confirm = getString(&node->nomeDoCurso, "Digite o nome do curso: ");

  // Falta outros.

  if (!confirm)
  {
    printf("Não foi possivel execultar o prencher aluno!");
    return 1;
  }
  return 0;
}

void showCurso(NodeCurso *curso)
{
  printf("Curso: \n");
  printf("\tid: %d\n", curso->codigo);
  printf("\tNome: %s\n", curso->nomeDoCurso);
}

void showAllCurso(NodeCurso *curso)
{
  if (!curso)
    return;

  showAllCurso(curso->dir);
  showAllCurso(curso->esq);
  showCurso(curso);
}

int isCurseOpen(NodeCurso *curso, int id)
{
  if (!curso)
    return 0;

  if (curso->codigo == id)
    return 1;

  return isCurseOpen(curso->dir, id) || isCurseOpen(curso->esq, id);
}

static NodeCurso *inserction(NodeCurso *raiz, NodeCurso *node)
{
  if (!raiz)
    return node;
  else
  {
    if (node->codigo < raiz->codigo)
      raiz->esq = inserction(raiz->esq, node);
    else
      raiz->dir = inserction(raiz->dir, node);
  }

  return raiz;
}

int cadastrarCursos(NodeCurso **nodeCurso)
{
  NodeCurso *new = alocCurso();
  if (prencherCurso(new))
  {
    freeNodeCurso(new);
    return 1;
  }

  *nodeCurso = inserction(*nodeCurso, new);
  return 0;
}
