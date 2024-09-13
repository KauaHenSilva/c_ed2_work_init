#include <stdio.h>
#include <stdlib.h>

#include <curso_crud.h>
#include <struct_curso.h>
#include <disciplina_crud.h>
#include <utils.h>

NodeCurso *alocCurso()
{
  NodeCurso *new = (NodeCurso *)malloc(sizeof(NodeCurso));
  new->codigo = -1;
  new->quantidadeDePeriodo = -1;
  new->nodeDisciplina = NULL;
  new->nomeDoCurso = NULL;
  new->dir = NULL;
  new->esq = NULL;
  return new;
}

void freeNodeCurso(NodeCurso *node)
{
  if (node->nomeDoCurso)
    free(node->nomeDoCurso);

  if (node->nodeDisciplina)
    freeNodeDisciplinas(node->nodeDisciplina);

  free(node);
}

void freeNodeCursos(NodeCurso *node)
{
  if (node)
  {
    freeNodeCursos(node->esq);
    freeNodeCursos(node->dir);
    freeNodeCurso(node);
  }
}

int prencherCurso(NodeCurso *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo do curso: ";
  confirm = getInt(&node->codigo, enunciado);

  if (confirm)
  {
    enunciado = "Digite a quantidade de periodo do curso: ";
    confirm = getInt(&node->quantidadeDePeriodo, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome do curso: ";
    confirm = getString(&node->nomeDoCurso, enunciado);
  }

  // Falta outros.

  if (!confirm)
    printf("Não foi possivel execultar o prencher aluno!");

  return !confirm;
}

void showCurso(NodeCurso *curso)
{
  printf("Curso: \n");
  printf("\tid: %d\n", curso->codigo);
  printf("\tNome: %s\n", curso->nomeDoCurso);
  showAllDisciplina(curso->nodeDisciplina);
}

void showAllCurso(NodeCurso *curso)
{
  if (curso)
  {
    showAllCurso(curso->esq);
    showAllCurso(curso->dir);
    showCurso(curso);
  }
}

// Revisar logica.
void isCurseOpen(NodeCurso *curso, int id, int *bool)
{
  if (curso)
  {
    if (curso->codigo == id)
      *bool = 1;
    else
    {
      isCurseOpen(curso->esq, id, bool);
      isCurseOpen(curso->dir, id, bool);
    }
  }
}

void inserctionCurso(NodeCurso **raiz, NodeCurso *node)
{
  if (!*raiz)
    *raiz = node;
  else
  {
    if (node->codigo < (*raiz)->codigo)
      inserctionCurso(&(*raiz)->esq, node);
    else
      inserctionCurso(&(*raiz)->dir, node);
  }
}

int cadastrarCursos(NodeCurso **nodeCurso)
{
  NodeCurso *new = alocCurso();
  if (prencherCurso(new))
    freeNodeCurso(new);

  if (new)
    inserctionCurso(nodeCurso, new);

  return new ? 1 : 0;
}
