#include <stdlib.h>
#include <stdio.h>

#include "../matricula_crud/matricula_crud.h"
#include "../disciplina_crud/disciplina_crud.h"

#include "../../utils/utils.h"


/**
 * @brief Aloca memória para uma nova estrutura NodeMatricula e inicializa seus membros.
 *
 * Esta função aloca memória para uma nova estrutura NodeMatricula e define seus membros
 * para valores padrão. Especificamente, define 'codDissciplina' com -1, 'dir' e 'esq' com NULL.
 *
 * @param node Uma refernecia para um ponteiro para uma estrutura NodeMatricula que será alocada e inicializada.
 */
static void alocMatricula(NodeMatricula **node)
{
  *node = (NodeMatricula *)malloc(sizeof(NodeMatricula));
  (*node)->codDisciplina = -1;
  (*node)->dir = NULL;
  (*node)->esq = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo NodeMatricula.
 *
 * Esta função libera toda a memória associada ao objeto NodeMatricula passado como parâmetro,
 * garantindo que não haja vazamentos de memória.
 *
 * @param node Ponteiro para o uma struct NodeMatricula que será liberado.
 */
static void freeNodeMatricula(NodeMatricula *node)
{
  free(node);
}

/**
 * @brief Libera a memória alocada para todos os objetos do tipo NodeMatricula.
 *
 * Esta função percorre a árvore binária de Matriculas e libera toda a memória associada a cada nó.
 * @param raiz Ponteiro para o uma struct NodeMatricula que será liberado.
 */
void freeNodeMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    freeNodeMatriculas(raiz->esq);
    freeNodeMatriculas(raiz->dir);
    freeNodeMatricula(raiz);
  }
}

/*
 * @brief Exibe as informações de uma matriculaa.
 * Esta função imprime no console o codigo de matricula.
 *
 * @param node Ponteiro para a estrutura NodeMatricula que contém a informação da matricula.
 */
static void showMatricula(NodeMatricula *node)
{
  printf("Matricula:\n");
  printf("\tCodDisciplina: %d\n", node->codDisciplina);
}

/**
 * @brief Exibe todas as matriculas.
 *
 * Função recursiva que percorre a arvore de matriculas e exibe o codigo de cada matricula
 * . A função chama `showAllMatriculas` para percorrer todos os nós, e em seguida chama
 * `showMatricula` para exibir a matricula atual.
 *
 * @param raiz Ponteiro para o nó raiz da arvore de matriculas.
 */
void showAllMatriculas(NodeMatricula *raiz)
{
  if (raiz)
  {
    showAllMatriculas(raiz->esq);
    showAllMatriculas(raiz->dir);
    showMatricula(raiz);
  }
}

#if DEBUG_MODE
/**
 * @brief Insere uma nova matricula na árvore binária de matriculas.
 *
 * Esta função solicita ao usuário que insira o codigo da matricula.
 *
 * @param node Ponteiro para a estrutura NodeMatricula onde os dados da matricula serão armazenados.
 *
 * @return Retorna 1 se os dados foram preenchidos com sucesso, ou 0 se houve algum erro.
 *
 */
static int prencherMatricula(NodeMatricula *new, NodeDisciplina *raizDisciplina, NodeMatricula *matricula)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  NodeDisciplina *searchDisciplina;
  NodeMatricula *searchMatricula;
  do
  {
    searchDisciplina = NULL;
    searchMatricula = NULL;

    eneunciado = "Digite o codigo da disciplina: ";

    if (new->codDisciplina == -1)
      confirm = getInt(&new->codDisciplina, eneunciado);
    else
      printf("[DEBUG]: procurando disciplinas com o id: %d\n", --new->codDisciplina);

    search_disciplina(raizDisciplina, new->codDisciplina, &searchDisciplina);
    search_matricula(matricula, new->codDisciplina, &searchMatricula);

    // Logica do while
    // Caso ele ache a disciplina (searchDisciplina != NULL) e caso a disiplina não esteja nas disciplinas já matriculadas. o mesmo deve sair do while.

  } while (!(searchDisciplina && !searchMatricula));

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina: ");

  return !confirm;
}
#else
/**
 * @brief Insere uma nova matricula na árvore binária de matriculas.
 *
 * Esta função solicita ao usuário que insira o codigo da matricula.
 *
 * @param node Ponteiro para a estrutura NodeMatricula onde os dados da matricula serão armazenados.
 *
 * @return Retorna 1 se os dados foram preenchidos com sucesso, ou 0 se houve algum erro.
 *
 */
int prencherMatricula(NodeMatricula *node, NodeDisciplina *raizDisciplina)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm;
  char *eneunciado;

  NodeDisciplina *search = NULL;
  do
  {
    eneunciado = "Digite o codigo da disciplina: ";
    confirm = getInt(&node->codDisciplina, eneunciado);

    search_disciplina(raizDisciplina, node->codDisciplina, &search);
  } while (!search);

  if (!confirm)
    printf("Não foi possivel execultar o prencher disciplina: ");

  return !confirm;
}
#endif

/**
 * @brief Insere um novo nó na árvore binária de matriculas.
 *
 * A função insere um novo nó `node` na árvore binária de matriculas com base
 * no código de matricula. Ela percorre a árvore comparando os códigos para garantir
 * que os nós à esquerda tenham valores menores e os nós à direita tenham valores maiores.
 *
 * @param raiz Ponteiro duplo para o nó raiz da árvore de disciplinas.
 * @param node Ponteiro para o nó de disciplina a ser inserido.
 */
void inserctionMatricula(NodeMatricula **raiz, NodeMatricula *new)
{
  if (!*raiz)
    *raiz = new;
  else
  {
    if (new->codDisciplina < (*raiz)->codDisciplina)
      inserctionMatricula(&(*raiz)->esq, new);
    else
      inserctionMatricula(&(*raiz)->dir, new);
  }
}

void search_matricula(NodeMatricula *raiz, int code, NodeMatricula **result)
{
  if (raiz)
  {
    if (raiz->codDisciplina == code)
      *result = raiz;
    else if (raiz->codDisciplina < code)
      search_matricula(raiz->dir, code, result);
    else if (raiz->codDisciplina > code)
      search_matricula(raiz->esq, code, result);
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
void removerDisciplinaDaArvoreDeMatricula(NodeMatricula **matricula, int codDisciplina)
{
  NodeMatricula *atual = *matricula;
  NodeMatricula *temp = *matricula;

  if (matricula)
  {
    if (atual->codDisciplina > codDisciplina)
      removerDisciplinaDaArvoreDeMatricula(&(atual->esq), codDisciplina);
    else if (atual->codDisciplina < codDisciplina)
      removerDisciplinaDaArvoreDeMatricula(&(atual->dir), codDisciplina);
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

/**
 * @brief Cadastra uma nova matrícula para um aluno em uma disciplina.
 *
 * Esta função cria uma nova matrícula e a insere na árvore de matrículas de um aluno,
 * associando a matrícula à disciplina correspondente.
 *
 * @param aluno Lista de alunos onde a matrícula será adicionada.
 * @param raizDisciplina Raiz da árvore de disciplinas disponíveis.
 */
void cadastrarMatriculas(ListAluno *aluno, NodeDisciplina *raizDisciplina)
{
  NodeMatricula *new;
  alocMatricula(&new);

  if (prencherMatricula(new, raizDisciplina, aluno->nodeMatricula))
    freeNodeMatriculas(new);

  if (new)
  {
    ListAluno *auxAluno = aluno;
    inserctionMatricula(&(auxAluno->nodeMatricula), new);
  }
}