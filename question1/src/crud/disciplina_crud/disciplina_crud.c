#include <stdio.h>
#include <stdlib.h>

#include "../curso_crud/curso_crud.h"
#include "../disciplina_crud/disciplina_crud.h"

#include "../../utils/utils.h"

/**
 * @brief Aloca memória para uma nova estrutura NodeDisciplina e inicializa seus membros.
 *
 * Esta função aloca memória para uma nova estrutura NodeDisciplina e define seus membros
 * para valores padrão. Especificamente, define 'cargaHoraria', 'codDisciplina','periodo' com -1,
 * 'nomeDaDisciplina', 'dir' e 'esq' com NULL.
 *
 * @param new Uma refernecia para um ponteiro para uma estrutura NodeDisciplina que será alocada e inicializada.
 */
static void alocDisciplina(NodeDisciplina **new)
{
  *new = (NodeDisciplina *)malloc(sizeof(NodeDisciplina));
  (*new)->disciplina.cargaHoraria = -1;
  (*new)->disciplina.codDisciplina = -1;
  (*new)->disciplina.periodo = -1;
  (*new)->disciplina.nomeDaDisciplina = NULL;
  (*new)->dir = NULL;
  (*new)->esq = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo NodeDisciplina.
 *
 * Esta função libera toda a memória associada ao objeto NodeDisciplina passado como parâmetro, garantindo que não haja vazamentos de memória.
 *
 * @param node Ponteiro para o uma struct NodeDisciplina que será liberado.
 */
static void freeNodeDisciplina(NodeDisciplina *node)
{
  if (node->disciplina.nomeDaDisciplina)
    free(node->disciplina.nomeDaDisciplina);

  free(node);
}

/**
 * @brief Libera a memória alocada para todos os objetos do tipo NodeDisciplina.
 *
 * Esta função percorre a árvore binária de disciplinas e libera toda a memória associada a cada nó.
 * @param raiz Ponteiro para o uma struct NodeDisciplina que será liberado.
 */
void freeNodeDisciplinas(NodeDisciplina *raiz)
{
  if (raiz)
  {
    freeNodeDisciplinas(raiz->esq);
    freeNodeDisciplinas(raiz->dir);
    freeNodeDisciplina(raiz);
  }
}

/**
 * @brief Insere uma nova disciplina na árvore binária de disciplinas.
 *
 * Esta função solicita ao usuário que insira os dados de uma disciplina, como o código da disciplina,
 * periodo e nome.
 *
 * @param node Ponteiro para a estrutura NodeDisciplina onde os dados da disciplina serão armazenados.
 *
 * @return Retorna 1 se os dados foram preenchidos com sucesso, ou 0 se houve algum erro.
 *
 */
static int prencherDisciplina(NodeDisciplina *node, int periodo)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  node->disciplina.periodo = periodo;

  enunciado = "Digite o codigo da disciplina: ";
  confirm = getInt(&node->disciplina.codDisciplina, enunciado);

  if (confirm)
  {
    enunciado = "Digite o nome da disciplina: ";
    confirm = getString(&node->disciplina.nomeDaDisciplina, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite a carga horaria da disciplina: ";
    confirm = getInt(&node->disciplina.cargaHoraria, enunciado);
  }

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina!");

  return !confirm;
}

/*
 * @brief Exibe as informações de uma disciplina.
 * Esta função imprime no console as informações de uma disciplina, incluindo
 * o código da disciplina e nome.
 *
 * @param disciplina Ponteiro para a estrutura NodeDisciplina que contém as informações da disciplina.
 */
void showDisciplina(NodeDisciplina *disciplina)
{
  printf("Disciplina: \n");
  printf("\tid: %d\n", disciplina->disciplina.codDisciplina);
  printf("\tNome: %s", disciplina->disciplina.nomeDaDisciplina);
  printf("\tPeriodo: %d\n", disciplina->disciplina.periodo);
  printf("\tCarga Horaria: %d\n", disciplina->disciplina.cargaHoraria);
}

/*
 * @brief Exibe todas as disciplinas.
 *
 * Função recursiva que percorre a arvore de disciplinas e exibe as
 * informações de cada disciplina. A função chama `showAllDisciplina` para percorret
 * todos os nós, e em seguida chama `showDisciplina` para exibir
 * a disciplina atual.
 *
 * @param disciplina Ponteiro para o nó raiz da arvore de disciplinas.
 */
void showAllDisciplina(NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    showAllDisciplina(disciplina->esq);
    showAllDisciplina(disciplina->dir);
    showDisciplina(disciplina);
  }
}

// void search_disciplina(NodeDisciplina *raiz, int code, NodeDisciplina **result)
// {
//   if (raiz)
//   {
//     if (raiz->disciplina.codDisciplina == code)
//       *result = raiz;
//     else if (raiz->disciplina.codDisciplina < code)
//       search_disciplina(raiz->dir, code, result);
//     else if (raiz->disciplina.codDisciplina > code)
//       search_disciplina(raiz->esq, code, result);
//   }
// }

/**
 * @brief Insere um novo nó na árvore binária de disciplinas.
 *
 * A função insere um novo nó `node` na árvore binária de disciplinas com base
 * no código da disciplina. Ela percorre a árvore comparando os códigos de
 * disciplina para garantir que os nós à esquerda tenham valores menores e os
 * nós à direita tenham valores maiores.
 *
 * @param raiz Ponteiro duplo para o nó raiz da árvore de disciplinas.
 * @param node Ponteiro para o nó de disciplina a ser inserido.
 */
static int inserction(NodeDisciplina **raiz, NodeDisciplina *node)
{
  int insert = 1;

  if (!*raiz)
    *raiz = node;
  else
  {
    if (node->disciplina.codDisciplina < (*raiz)->disciplina.codDisciplina)
      insert = inserction(&(*raiz)->esq, node);
    else if (node->disciplina.codDisciplina > (*raiz)->disciplina.codDisciplina)
      insert = inserction(&(*raiz)->dir, node);
    else
      insert = 0;
  }

  return insert;
}

/**
 * @brief Cadastra uma nova disciplina em um curso.
 *
 * A função aloca memória para um novo nó de disciplina, preenche as informações
 * da disciplina e a insere na árvore binária de disciplinas do curso. Se o
 * preenchimento da disciplina falhar, a memória alocada para o novo nó é liberada.
 *
 * @param curso Ponteiro para o nó raiz da árvore de cursos.
 */
int cadastrarDisciplinas(NodeCurso *curso, int periodo)
{
  int confirm = 1;

  NodeDisciplina *new;
  alocDisciplina(&new);

  if (prencherDisciplina(new, periodo))
  {
    freeNodeDisciplina(new);
    confirm = 0;
  }

  if (new)
  {
    NodeCurso *aux = curso;
    if (!inserction(&(aux->curso.nodeDisciplina), new))
    {
      freeNodeDisciplina(new);
      confirm = 0;
    }
  }

  return confirm;
}

void buscarDisciplina(NodeDisciplina *raiz, int codigo, NodeDisciplina **result)
{
  if (raiz)
  {
    if (raiz->disciplina.codDisciplina == codigo)
      *result = raiz;
    else if (raiz->disciplina.codDisciplina < codigo)
      buscarDisciplina(raiz->dir, codigo, result);
    else if (raiz->disciplina.codDisciplina > codigo)
      buscarDisciplina(raiz->esq, codigo, result);
  }
}

NodeDisciplina *removerDisciplina(NodeDisciplina *raiz, int codDisciplina)
{
  if (raiz != NULL)
  {
    if (raiz->disciplina.codDisciplina == codDisciplina)
    {
      if (raiz->esq == NULL && raiz->dir != NULL)
      {
        free(raiz);
        raiz = NULL;
      }
      else if (raiz->esq == NULL || raiz->dir == NULL)
      {
        NodeDisciplina *aux;
        if (raiz->esq == NULL)
        {
          aux = raiz;
          raiz = raiz->dir;
        }
        else
        {
          aux = raiz;
          raiz = raiz->esq;
        }
        free(aux);
      }
      else
      {
        NodeDisciplina *aux = raiz->dir;
        while (aux->esq != NULL)
          aux = aux->esq;
        raiz->disciplina.codDisciplina = aux->disciplina.codDisciplina;
        raiz->dir = removerDisciplina(raiz->dir, aux->disciplina.codDisciplina);
      }
    }
    else
    {
      if (codDisciplina < raiz->disciplina.codDisciplina)
        raiz->esq = removerDisciplina(raiz->esq, codDisciplina);
      else
        raiz->dir = removerDisciplina(raiz->dir, codDisciplina);
    }
  }
  return raiz;
}