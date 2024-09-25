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
static void prencherNota(NodeNota *raizNota, int codDisciplina, int semestreCursado)
{
  raizNota->nota.codDisciplina = codDisciplina;
  raizNota->nota.semestreCursado = semestreCursado;
  getInt(&raizNota->nota.notaFinal, "Digite a nota final do aluno: ");
}

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

int buscarNotas(NodeNota *nota, int codDisciplina, NodeNota **valor)
{
  int encontrou = 1;

  if (nota)
  {
    if (codDisciplina == nota->nota.codDisciplina)
      *valor = nota;
    else
    {
      if (codDisciplina < nota->nota.codDisciplina)
        encontrou = buscarNotas(nota->esq, codDisciplina, valor);
      else
        encontrou = buscarNotas(nota->dir, codDisciplina, valor);
    }
  }
  else
    encontrou = 0;

  return encontrou;
}

int cadastrarNotas(ListAluno *aluno, int codDisciplina, int semestreCursado)
{
  int confirm = 1;

  NodeNota *new;
  alocNota(&new);
  prencherNota(new, codDisciplina, semestreCursado);

  if (!inserctionNota(&(aluno->aluno.nodeNota), new) ||
      !removerMatricula(&(aluno->aluno.nodeMatricula), codDisciplina))
  {
    freeNodeNota(new);
    confirm = 0;
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
