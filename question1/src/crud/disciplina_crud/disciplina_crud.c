#include <stdio.h>
#include <stdlib.h>

#include "../curso_crud/curso_crud.h"
#include "../disciplina_crud/disciplina_crud.h"
#include "../nota_crud/nota_crud.h"

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
static void prencherDisciplina(NodeDisciplina *node, int periodo)
{
  node->disciplina.periodo = periodo;
  getInt(&node->disciplina.codDisciplina, "Digite o codigo da disciplina: ");
  getString(&node->disciplina.nomeDaDisciplina, "Digite o nome da disciplina: ");
  getIntMult5(&node->disciplina.cargaHoraria, "Digite a carga horaria da disciplina: ");
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
  prencherDisciplina(new, periodo);

  if (!inserction(&(curso->curso.nodeDisciplina), new))
  {
    freeNodeDisciplina(new);
    confirm = 0;
  }

  return confirm;
}

int buscarDisciplina(NodeDisciplina *raiz, int codigo, NodeDisciplina **result)
{
  int confirm = 1;

  if (raiz)
  {
    if (raiz->disciplina.codDisciplina == codigo)
      *result = raiz;
    else if (raiz->disciplina.codDisciplina < codigo)
      confirm = buscarDisciplina(raiz->dir, codigo, result);
    else if (raiz->disciplina.codDisciplina > codigo)
      confirm = buscarDisciplina(raiz->esq, codigo, result);
  }
  else
    confirm = 0;

  return confirm;
}

/**
 * @brief Verifica se é um nó folha.
 *
 * esta função verifica se o nó é folha, ou seja, se tando a esquerda
 * quanto a direita são nulos.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de disciplinas.
 */

int ehFolhaDisciplina(NodeDisciplina *raiz){
  return (raiz->esq == NULL && raiz->dir == NULL);
}

/**
 * @brief Verifica se é o nó possui um filho..
 *
 * esta função verifica qual filho o nó tem, se é o da direita ou da esquerda.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de disciplinas.
 */

NodeDisciplina *soUmFilhoDisciplina(NodeDisciplina *raiz){
  NodeDisciplina *aux = NULL;
  if(raiz->esq == NULL && raiz->dir!= NULL)
    aux = raiz->dir;
  else if(raiz->esq!= NULL && raiz->dir == NULL)
    aux = raiz->esq;
  return aux;
}

NodeDisciplina *menorFilhoDisciplina(NodeDisciplina *raiz){
  NodeDisciplina* atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq; 
    }
  return atual;
}

/**
 * @brief Remove um nó da arvore.
 *
 * esta função remove um nó da arvore, nos 3 diferentes casos,
 * quando é um nó folha, um nó com apenas um filho, ou um nó com 2 filhos.
 *
 * @param raiz Ponteiro duplo para o nó raiz da árvore de disciplinas.
 * @param codDisciplina codigo da disciplina que deseja remover a matricula
 */

int removerDisciplina(NodeDisciplina **raiz, int codDisciplina)
{
  int confirm = 1;

  NodeDisciplina *endFilho = NULL;

  if ((*raiz) != NULL)
  {
    if ((*raiz)->disciplina.codDisciplina == codDisciplina)
    {
      if (ehFolhaDisciplina(*raiz))
      {
        free((*raiz));
        (*raiz) = NULL;
      }
      else if ((endFilho = soUmFilhoDisciplina(*raiz)) != NULL)
      {
        NodeDisciplina *aux = (*raiz);
        (*raiz) = endFilho;
        free(aux);
      }
      else
      {
        NodeDisciplina *aux = menorFilhoDisciplina((*raiz)->dir);
        (*raiz)->disciplina.codDisciplina = aux->disciplina.codDisciplina;
        confirm = removerDisciplina(&(*raiz)->dir, aux->disciplina.codDisciplina);
      }
    }
    else
    {
      if (codDisciplina < (*raiz)->disciplina.codDisciplina)
        confirm = removerDisciplina(&(*raiz)->esq, codDisciplina);
      else
        confirm = removerDisciplina(&(*raiz)->dir, codDisciplina);
    }
  }

  return confirm;
}
