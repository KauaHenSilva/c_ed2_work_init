#include <stdlib.h>
#include <stdio.h>

#include "../nota_crud/nota_crud.h"
#include "../matricula_crud/matricula_crud.h"
#include "../disciplina_crud/disciplina_crud.h"

#include "../../utils/utils.h"

/**
 * @brief Aloca memória para uma nova nota.
 *
 * Esta função aloca dinamicamente memória para um novo nó de nota (`NodeNota`),
 * inicializando seus campos com valores padrão (-1 para `codDisciplina`,
 * `notaFinal` e `semestreCursado`) e definindo os ponteiros para subárvores
 * esquerda e direita como `NULL`.
 *
 * @param node Ponteiro duplo para o nó de nota que será alocado.
 */
static void alocNota(NodeNota **node)
{
  *node = (NodeNota *)malloc(sizeof(NodeNota));
  (*node)->nota.codDisciplina = -1;
  (*node)->nota.notaFinal = -1;
  (*node)->nota.semestreCursado = -1;
  (*node)->dir = NULL;
  (*node)->esq = NULL;
}

/**
 * @brief Libera a memória de um nó de nota.
 *
 * Esta função libera a memória associada a um nó de nota.
 *
 * @param node Ponteiro para o nó de nota a ser liberado.
 */
static void freeNodeNota(NodeNota *node)
{
  free(node);
}

/**
 * @brief Libera a memória de uma árvore binária de notas.
 *
 * Função recursiva que percorre toda a árvore binária de notas e libera a
 * memória de cada nó.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de notas.
 */
void freeNodeNotas(NodeNota *raiz)
{
  if (raiz)
  {
    freeNodeNotas(raiz->esq);
    freeNodeNotas(raiz->dir);
    freeNodeNota(raiz);
  }
}

#if DEBUG_MODE
/**
 * @brief Preenche os dados de uma nota com base na entrada do usuário.
 *
 * Solicita ao usuário o código da disciplina para preencher a nota.
 * Se a entrada for inválida, a função retorna um erro.
 *
 * @param raizNota Ponteiro para a raiz de nota a ser preenchido.
 * @param raizMatricula Ponteiro para a raiz de matricula a ser escolhida.
 * @return Retorna 1 se o preenchimento foi bem-sucedido, 0 caso contrário.
 */
static int prencherNota(NodeNota *raizNota, int codDisciplina)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  raizNota->nota.codDisciplina = codDisciplina;

  enunciado = "Digite a nota final do aluno: ";
  confirm = getInt(&raizNota->nota.notaFinal, enunciado);

  enunciado = "Digite o semestre cursado: ";
  confirm = getInt(&raizNota->nota.semestreCursado, enunciado);

  if (!confirm)
    printf("Não foi possivel execultar o prencher a nota: ");

  return !confirm;
}
#else
/**
 * @brief Preenche os dados de uma nota com base na entrada do usuário.
 *
 * Solicita ao usuário o código da disciplina para preencher a nota.
 * Se a entrada for inválida, a função retorna um erro.
 *
 * @param raizNota Ponteiro para a raiz de nota a ser preenchido.
 * @param raizDisciplina Ponteiro para a raiz de nota a ser preenchido.
 * @return Retorna 1 se o preenchimento foi bem-sucedido, 0 caso contrário.
 */
static int prencherNota(NodeNota *raizNota, int codDisciplina, int semestreCursado)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *enunciado;

  raizNota->nota.codDisciplina = codDisciplina;
  raizNota->nota.semestreCursado = semestreCursado;

  enunciado = "Digite a nota final do aluno: ";
  confirm = getInt(&raizNota->nota.notaFinal, enunciado);

  if (!confirm)
    printf("Não foi possivel execultar o prencher a nota: ");

  return !confirm;
}
#endif

/**
 * @brief Exibe os dados de uma nota.
 *
 * Mostra o código da disciplina associado à nota.
 *
 * @param node Ponteiro para o nó de nota a ser exibido.
 */
void showNota(NodeNota *node)
{
  printf("Notas:\n");
  printf("\tCodDisciplina: %d\n", node->nota.codDisciplina);
  printf("\tNotaFinal: %d\n", node->nota.notaFinal);
  printf("\tSemestreCursado: %d\n", node->nota.semestreCursado);
}

/**
 * @brief Insere um novo nó de nota na árvore binária.
 *
 * A função insere um novo nó de nota em uma árvore binária de acordo com o
 * código da disciplina, preservando a ordenação.
 *
 * @param raiz Ponteiro para o ponteiro do nó raiz da árvore de notas.
 * @param new Ponteiro para o novo nó de nota a ser inserido.
 */
int inserctionNota(NodeNota **raiz, NodeNota *new)
{
  int confirm = 1;

  if (!*raiz)
    *raiz = new;
  else
  {
    if (new->nota.codDisciplina < (*raiz)->nota.codDisciplina)
      confirm = inserctionNota(&(*raiz)->esq, new);
    else if (new->nota.codDisciplina > (*raiz)->nota.codDisciplina)
      confirm = inserctionNota(&(*raiz)->dir, new);
    else
      confirm = 0;
  }

  return confirm;
}

NodeMatricula *remover(NodeMatricula *raiz, int codDisciplina)
{
  if (raiz == NULL)
  {
    return NULL;
  }

  // Caso base: encontrar o nó a ser removido
  if (raiz->codDisciplina == codDisciplina)
  {
    // Caso 1: Nó folha
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
      free(raiz);
      return NULL;
    }
    // Caso 2: Nó com um filho
    else if (raiz->esq == NULL || raiz->dir == NULL)
    {
      NodeMatricula *temp = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
      free(raiz);
      return temp;
    }
    // Caso 3: Nó com dois filhos
    else
    {
      NodeMatricula *aux = raiz->esq;
      while (aux->dir != NULL)
      {
        aux = aux->dir;
      }
      raiz->codDisciplina = aux->codDisciplina;
      raiz->esq = remover(raiz->esq, aux->codDisciplina);
      return raiz;
    }
  }
  // Se o código da disciplina a ser removido é menor que o código do nó atual, continue na subárvore esquerda
  else if (codDisciplina < raiz->codDisciplina)
  {
    raiz->esq = remover(raiz->esq, codDisciplina);
  }
  // Se o código da disciplina a ser removido é maior que o código do nó atual, continue na subárvore direita
  else
  {
    raiz->dir = remover(raiz->dir, codDisciplina);
  }

  return raiz;
}

/**
 * @brief Exibe todas as notas de uma árvore binária.
 *
 * Função recursiva que percorre toda a árvore de notas e exibe os detalhes
 * de cada nó.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de notas.
 */
void showAllNotas(NodeNota *raiz)
{
  if (raiz)
  {
    showAllNotas(raiz->esq);
    showAllNotas(raiz->dir);
    showNota(raiz);
  }
}

int cadastrarNotas(ListAluno *aluno, int codDisciplina, int semestreCursado)
{
  int confirm = 1;

  NodeNota *new;
  alocNota(&new);

  if (prencherNota(new, codDisciplina, semestreCursado))
  {
    freeNodeNotas(new);
    confirm = 0;
  }

  if (new)
  {
    ListAluno *auxAluno = aluno;

    // if(!removerDisciplinaDaArvoreDeMatricula(&aluno->aluno.nodeMatricula, new->nota.codDisciplina) && confirm)
    // {
    //   freeNodeNota(new);
    //   confirm = 0;
    // }

    if (!inserctionNota(&auxAluno->aluno.nodeNota, new) && confirm)
    {
      confirm = 0;
      freeNodeNota(new);
    }
  }

  return confirm;
}

int buscar_nota(NodeNota *raiz, int codigo, NodeNota *valor)
{
  int encontrou = 1;

  if (raiz != NULL)
  {
    if (codigo == raiz->nota.codDisciplina)
      valor = raiz;
    else
    {
      if (codigo < raiz->nota.codDisciplina)
        encontrou = buscar_nota(raiz->esq, codigo, valor);
      else if (codigo > raiz->nota.codDisciplina)
        encontrou = buscar_nota(raiz->dir, codigo, valor);
      else
        encontrou = 0;
    }
  }

  return encontrou;
}
