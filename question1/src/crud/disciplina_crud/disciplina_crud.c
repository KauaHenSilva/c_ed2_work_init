#include <stdio.h>
#include <stdlib.h>

#include <disciplina_crud.h>
#include <curso_crud.h>
#include <utils.h>


/**
 * @brief Aloca memória para uma nova estrutura NodeDisciplina e inicializa seus membros.
 * 
 * Esta função aloca memória para uma nova estrutura NodeDisciplina e define seus membros
 * para valores padrão. Especificamente, define 'cargaHoraria', 'codDisciplina','periodo' com -1,
 * 'nomeDaDisciplina', 'dir' e 'esq' com NULL.
 * 
 * @param new Uma refernecia para um ponteiro para uma estrutura NodeDisciplina que será alocada e inicializada.
 */
void alocDisciplina(NodeDisciplina **new)
{
  *new = (NodeDisciplina *)malloc(sizeof(NodeDisciplina));
  (*new)->cargaHoraria = -1;
  (*new)->codDisciplina = -1;
  (*new)->periodo = -1;
  (*new)->nomeDaDisciplina = NULL;
  (*new)->dir = NULL;
  (*new)->esq = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo NodeDisciplina.
 *
 * Esta função libera toda a memória associada ao objeto NodeDisciplina passado como parâmetro,
 * garantindo que não haja vazamentos de memória.
 *
 * @param node Ponteiro para o uma struct NodeDisciplina que será liberado.
 */
void freeNodeDisciplina(NodeDisciplina *node)
{
  if (node->nomeDaDisciplina)
    free(node->nomeDaDisciplina);

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
int prencherDisciplina(NodeDisciplina *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo da disciplina: ";
  confirm = getInt(&node->codDisciplina, enunciado);

  if (confirm)
  {
    enunciado = "Digite o periodo da disciplina: ";
    confirm = getInt(&node->periodo, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite a carga horaria da disciplina: ";
    confirm = getInt(&node->cargaHoraria, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome da disciplina: ";
    confirm = getString(&node->nomeDaDisciplina, enunciado);
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
  printf("\tid: %d\n", disciplina->codDisciplina);
  printf("\tNome: %s\n", disciplina->nomeDaDisciplina);
}

/**
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

static void inserction(NodeDisciplina **raiz, NodeDisciplina *node)
{
  if (!*raiz)
    *raiz = node;
  else
  {
    if (node->codDisciplina < (*raiz)->codDisciplina)
      inserction(&(*raiz)->esq, node);
    else
      inserction(&(*raiz)->dir, node);
  }
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

void cadastrarDisciplinas(NodeCurso *curso)
{
  NodeDisciplina *new;
  alocDisciplina(&new);

  if (prencherDisciplina(new))
    freeNodeDisciplina(new);

  if (new)
  {
    // temporario, para inserir no ultimo curso a direita. // O usuario deve escolher o curso.
    NodeCurso *aux = curso;
    while (aux->dir)
      aux = aux->dir;

    inserction(&(aux->nodeDisciplina), new);
  }
}