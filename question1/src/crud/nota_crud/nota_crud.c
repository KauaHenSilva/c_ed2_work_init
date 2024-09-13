#include <nota_crud.h>
#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

void alocNota(NodeNota **node)
{
  *node = (NodeNota *)malloc(sizeof(NodeNota));
  (*node)->codDisciplina = -1;
  (*node)->notaFinal = -1;
  (*node)->semestreCursado = -1;
  (*node)->dir = NULL;
  (*node)->esq = NULL;
}

void freeNodeNota(NodeNota *node)
{
  free(node);
}

void freeNodeNotas(NodeNota *raiz)
{
  if (raiz)
  {
    freeNodeNotas(raiz->esq);
    freeNodeNotas(raiz->dir);
    freeNodeNota(raiz);
  }
}

void showNota(NodeNota *node)
{
  printf("Notas:\n");
  printf("\tCodDisciplina: %d\n", node->codDisciplina);
}

void showAllNotas(NodeNota *raiz)
{
  if (raiz)
  {
    showAllNotas(raiz->esq);
    showAllNotas(raiz->dir);
    showNota(raiz);
  }
}

int prencherNota(NodeNota *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  eneunciado = "Digite o codigo da disciplina da nota: ";
  confirm = getInt(&node->codDisciplina, eneunciado);

  if (!confirm)
    printf("Não foi possivel execultar o prencher a nota: ");

  return !confirm;
}

void inserctionNota(NodeNota **raiz, NodeNota *new)
{
  if (!*raiz)
    *raiz = new;
  else
  {
    if ((*raiz)->codDisciplina < new->codDisciplina)
      inserctionNota(&(*raiz)->esq, new);
    else
      inserctionNota(&(*raiz)->dir, new);
  }
}

void cadastrarNotas(ListAluno *aluno)
{

}
