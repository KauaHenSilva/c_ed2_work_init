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

NodeMatricula *remover(NodeMatricula *raiz, int codDisciplina)
{

  if (raiz != NULL)
  {
    if (raiz->codDisciplina == codDisciplina)
    {
      // remove nos folhas
      if (raiz->esq == NULL && raiz->dir == NULL)
      {
        free(raiz);
        return NULL;
      }
      else
      {
        // remove nos que possui apenas um filho
        if (raiz->esq == NULL || raiz->dir == NULL)
        {
          NodeMatricula *temp;
          if (raiz->esq != NULL)
          {
            temp = raiz->esq;
          }
          else
          {
            temp = raiz->dir;  
          }
          free(raiz);
          return temp;

        }else{
          NodeMatricula *aux = raiz->esq;
          while(aux->dir != NULL){
            aux = aux->dir;
          } 
          raiz->codDisciplina = aux->codDisciplina;
          aux->codDisciplina = codDisciplina;
          raiz->esq = remover(raiz->esq, codDisciplina);
          return raiz;
        }
      }
    }
    else
    {
      if (raiz->esq < raiz->codDisciplina)
        raiz->esq = remover(raiz->esq, codDisciplina);
      else
        raiz->dir = remover(raiz->dir, codDisciplina);
      return raiz;
    }
  }
}

void cadastrarNotas(ListAluno *aluno)
{
}
