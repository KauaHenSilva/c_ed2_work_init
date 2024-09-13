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

  eneunciado = "Digite o codigo da disciplina: ";
  confirm = getInt(&node->codDisciplina, eneunciado);

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina: ");

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

NodeMatricula *esqRoot(NodeMatricula *node)
{
  NodeMatricula *current = node;
  while (current && current->esq != NULL)
    current = current->esq;
  return current;
}

// Tem que testar ainda. (Quebrou a parte que os cursos não tem o codigo correto.)
void removMatricula(NodeMatricula **matricula, int codDisciplina)
{
  NodeMatricula *atual = *matricula;
  NodeMatricula *temp = *matricula;

  if (matricula)
  {
    if (atual->codDisciplina > codDisciplina)
      removMatricula(&(atual->esq), codDisciplina);
    else if (atual->codDisciplina < codDisciplina)
      removMatricula(&(atual->dir), codDisciplina);
    else
    {
      if (atual->esq == NULL)
        temp = atual->dir;
      else if (atual->dir == NULL)
        temp = atual->esq;
      else
        temp = esqRoot(atual->dir);

      *matricula = temp;
      free(atual);
    }
  }
}

void cadastrarMatriculas(ListAluno *aluno, NodeDisciplina *raizDisciplina)
{
  NodeMatricula *new;
  alocMatricula(&new);

  if (new)
  {
    ListAluno *auxAluno = aluno;
    NodeDisciplina *auxDisciplina = raizDisciplina;

    new->codDisciplina = auxDisciplina->codDisciplina;
    inserctionMatricula(&(auxAluno->nodeMatricula), new);
  }
}