#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
int inserctionMatricula(NodeMatricula **raiz, NodeMatricula *new)
{
  int confirm = 1;

  if (!*raiz)
    *raiz = new;
  else
  {
    if (new->codDisciplina < (*raiz)->codDisciplina)
      confirm = inserctionMatricula(&(*raiz)->esq, new);
    else if (new->codDisciplina > (*raiz)->codDisciplina)
      confirm = inserctionMatricula(&(*raiz)->dir, new);
    else
      confirm = 0;
  }

  return confirm;
}

int search_matricula(NodeMatricula *raiz, int code, NodeMatricula **result)
{
  int confirm = 1;

  if (raiz)
  {
    if (raiz->codDisciplina == code)
      *result = raiz;
    else if (raiz->codDisciplina < code)
      search_matricula(raiz->dir, code, result);
    else if (raiz->codDisciplina > code)
      search_matricula(raiz->esq, code, result);
  }
  else
    confirm = 0;

  return confirm;
}

NodeMatricula *esqRoot(NodeMatricula *node)
{
  NodeMatricula *current = node;
  while (current && current->esq != NULL)
    current = current->esq;
  return current;
}

/**
 * @brief Verifica se é um nó folha.
 *
 * esta função verifica se o nó é folha, ou seja, se tando a esquerda
 * quanto a direita são nulos.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de disciplinas.
 */
int ehFolha(NodeMatricula *raiz){
  return (raiz->esq == NULL && raiz->dir == NULL);
}

/**
 * @brief Verifica se é o nó possui um filho..
 *
 * esta função verifica qual filho o nó tem, se é o da direita ou da esquerda.
 *
 * @param raiz Ponteiro para o nó raiz da árvore de disciplinas.
 */
NodeMatricula *soUmFilho(NodeMatricula *raiz){
  NodeMatricula *aux = NULL;
  if(raiz->esq == NULL && raiz->dir!= NULL)
    aux = raiz->dir;
  else if(raiz->esq!= NULL && raiz->dir == NULL)
    aux = raiz->esq;
  return aux;
}


NodeMatricula *menorFilho(NodeMatricula *raiz){
  NodeMatricula* atual = raiz;
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

int removerMatricula(NodeMatricula **raiz, int codDisciplina)
{
  int confirm = 1;
  NodeMatricula *endFilho = NULL;
  if ((*raiz) != NULL)
  {
    if ((*raiz)->codDisciplina == codDisciplina)
    {
      if (ehFolha(*raiz))
      {
        free((*raiz));
        (*raiz) = NULL;
      }
      else if ((endFilho = soUmFilho(*raiz)) != NULL)
      {
        NodeMatricula *aux = (*raiz);
        (*raiz) = endFilho;
        free(aux);
      }
      else
      {
        NodeMatricula *aux = menorFilho((*raiz)->dir);
        (*raiz)->codDisciplina = aux->codDisciplina;
        confirm = removerMatricula(&(*raiz)->dir, aux->codDisciplina);
      }
    }
    else
    {
      if (codDisciplina < (*raiz)->codDisciplina)
        confirm = removerMatricula(&(*raiz)->esq, codDisciplina);
      else
        confirm = removerMatricula(&(*raiz)->dir, codDisciplina);
    }
  }

  return confirm;
}

NodeMatricula *buscarMatriculas(NodeMatricula *raiz, int codDisciplina)
{
  NodeMatricula *aux = NULL; // Inicializa o ponteiro

  if (raiz != NULL)
  {
    if (codDisciplina == raiz->codDisciplina)
      aux = raiz;
    else if (codDisciplina < raiz->codDisciplina)
      aux = buscarMatriculas(raiz->esq, codDisciplina);
    else
      aux = buscarMatriculas(raiz->dir, codDisciplina);
  }

  return aux; // Retorna o ponteiro encontrado ou NULL
}

<<<<<<< HEAD
=======
/**
 * @brief Busca um aluno na lista de alunos pelo número de matrícula.
 *
 * Esta função percorre a lista encadeada de alunos em busca de um aluno
 * cujo número de matrícula corresponde ao valor fornecido como parâmetro.
 * Se o aluno for encontrado, retorna um ponteiro para o nó do aluno; caso
 * contrário, retorna NULL.
 *
 * @param alunos Ponteiro para a lista encadeada de alunos.
 * @param matricula Número da matrícula do aluno a ser buscado.
 * @return Retorna um ponteiro para o nó do aluno encontrado ou NULL se não encontrado.
 */

>>>>>>> teste
ListAluno *buscarAluno(ListAluno *alunos, int matricula)
{
  ListAluno *aluno = alunos;
  while (aluno != NULL && aluno->aluno.matricula == matricula)
    aluno = aluno->prox;

<<<<<<< HEAD
  return aluno;
=======
/**
 * @brief Verifica o número de alunos matriculados em uma disciplina específica.
 *
 * Esta função percorre uma lista de alunos e conta quantos alunos
 * estão matriculados na disciplina cujo código é fornecido como parâmetro.
 * O contador é incrementado sempre que um aluno possui uma matrícula
 * associada à disciplina especificada.
 *
 * @param aluno Ponteiro para a lista encadeada de alunos.
 * @param disciplina Código da disciplina a ser verificada.
 * @return Retorna o número de alunos matriculados na disciplina.
 */

int VerificarAlunosMatriculados(ListAluno *aluno, int disciplina)
{
  int encontrou = 0;
  while (aluno != NULL)
  {
    if (aluno->aluno.nodeMatricula != NULL && aluno->aluno.nodeMatricula->codDisciplina == disciplina)
    {
      encontrou += 1;
    }
    aluno = aluno->prox;
  }
  return encontrou;
>>>>>>> teste
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
int cadastrarMatriculas(ListAluno *aluno, int idDisciplina)
{
  int confirm = 1;

  NodeMatricula *new;
  alocMatricula(&new);

  new->codDisciplina = idDisciplina;

  if (!inserctionMatricula(&(aluno->aluno.nodeMatricula), new))
  {
    confirm = 0;
    freeNodeMatricula(new);
  }

  return confirm;
}