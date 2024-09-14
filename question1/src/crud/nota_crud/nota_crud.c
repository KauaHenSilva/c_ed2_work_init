#include <nota_crud.h>
#include <matricula_crud.h>

#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

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
void alocNota(NodeNota **node)
{
  *node = (NodeNota *)malloc(sizeof(NodeNota));
  (*node)->codDisciplina = -1;
  (*node)->notaFinal = -1;
  (*node)->semestreCursado = -1;
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
void freeNodeNota(NodeNota *node)
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
 * @brief Exibe os dados de uma nota.
 *
 * Mostra o código da disciplina associado à nota.
 *
 * @param node Ponteiro para o nó de nota a ser exibido.
 */
void showNota(NodeNota *node)
{
  printf("Notas:\n");
  printf("\tCodDisciplina: %d\n", node->codDisciplina);
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


#if DEBUG_MODE
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
int prencherNota(NodeNota *raizNota, NodeDisciplina *raizDisciplina)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  NodeDisciplina *search = NULL;
  do
  {
    eneunciado = "Digite o codigo da disciplina da nota: ";

    if (raizNota->codDisciplina == -1)
      confirm = getInt(&raizNota->codDisciplina, eneunciado);
    else
      printf("[DEBUG]: procurando disciplinas com o id: %d\n", --raizNota->codDisciplina);

    search_matricula(raizDisciplina, raizNota->codDisciplina, &search);
  } while (!search);

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
int prencherNota(NodeNota *raizNota, NodeDisciplina *raizDisciplina)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  NodeDisciplina *search = NULL;
  do
  {
    eneunciado = "Digite o codigo da disciplina da nota: ";
    confirm = getInt(&raizNota->codDisciplina, eneunciado);

    search_matricula(raizDisciplina, raizNota->codDisciplina, &search);
  } while (!search);

  if (!confirm)
    printf("Não foi possivel execultar o prencher a nota: ");

  return !confirm;
}
#endif

/**
 * @brief Insere um novo nó de nota na árvore binária.
 *
 * A função insere um novo nó de nota em uma árvore binária de acordo com o
 * código da disciplina, preservando a ordenação.
 *
 * @param raiz Ponteiro para o ponteiro do nó raiz da árvore de notas.
 * @param new Ponteiro para o novo nó de nota a ser inserido.
 */
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

void cadastrarNotas(ListAluno *aluno, NodeDisciplina *raizDisciplina)
{
  NodeNota *new;
  alocNota(&new);

  if (prencherNota(new, raizDisciplina))
    freeNodeNotas(new);

  if (new)
  {
    ListAluno *auxAluno = aluno;
    removerDisciplinaDaArvoreDeMatricula(&aluno->nodeMatricula, new->codDisciplina);
    inserctionNota(&auxAluno->nodeNota, new);
  }
}
