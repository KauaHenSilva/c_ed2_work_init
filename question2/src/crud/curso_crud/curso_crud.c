#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../curso_crud/curso_crud.h"
#include "../disciplina_crud/disciplina_crud.h"
#include "../aluno_crud/aluno_crud.h"

#include "../../utils/utils.h"

/**
 * @brief Aloca memória para um novo curso e inicializa seus atributos.
 *
 * Esta função aloca dinamicamente um novo nó de curso (`NodeCurso`) e inicializa
 * seus campos com valores padrão. O código do curso e a quantidade de períodos
 * são definidos como -1, e os ponteiros para disciplinas e outros nós da árvore
 * são inicializados como `NULL`.
 *
 * @return Um ponteiro para o novo curso alocado.
 */
static NodeCurso *alocCurso()
{
  NodeCurso *new = (NodeCurso *)malloc(sizeof(NodeCurso));
  new->curso.codigo = -1;
  new->curso.quantidadeDePeriodo = -1;
  new->curso.nodeDisciplina = NULL;
  new->curso.nomeDoCurso = NULL;
  new->dir = NULL;
  new->esq = NULL;
  return new;
}

/**
 * @brief Libera a memória alocada para um nó de curso e suas disciplinas associadas.
 *
 * Esta função libera a memória associada a um curso, incluindo o nome do curso
 * e a árvore de disciplinas vinculada a ele. Finalmente, libera a memória do
 * próprio nó de curso.
 *
 * @param node Ponteiro para o nó de curso a ser liberado.
 */
static void freeNodeCurso(NodeCurso *node)
{
  if (node->curso.nomeDoCurso)
    free(node->curso.nomeDoCurso);

  if (node->curso.nodeDisciplina)
    freeNodeDisciplinas(node->curso.nodeDisciplina);

  free(node);
}

/**
 * @brief Libera a memória de uma árvore binária de cursos.
 *
 * Função recursiva que libera a memória de cada nó de uma árvore binária de
 * cursos, percorrendo os nós da esquerda e da direita antes de liberar o nó atual.
 *
 * @param node Ponteiro para o nó raiz da árvore de cursos.
 */
void freeNodeCursos(NodeCurso *node)
{
  if (node)
  {
    freeNodeCursos(node->esq);
    freeNodeCursos(node->dir);
    freeNodeCurso(node);
  }
}

/**
 * @brief Preenche os dados de um curso com base nas entradas do usuário.
 *
 * Solicita ao usuário o código do curso, a quantidade de períodos e o nome do
 * curso, preenchendo os campos correspondentes na estrutura `NodeCurso`.
 * Se o usuário inserir dados inválidos ou optar por sair, a função retorna uma
 * falha.
 *
 * @param node Ponteiro para o curso a ser preenchido.
 * @return Retorna 1 se o preenchimento foi bem-sucedido, 0 caso contrário.
 */
static int prencherCurso(NodeCurso *node)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo do curso: ";
  confirm = getInt(&node->curso.codigo, enunciado);

  if (confirm)
  {
    enunciado = "Digite a quantidade de periodo do curso: ";
    confirm = getInt(&node->curso.quantidadeDePeriodo, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome do curso: ";
    confirm = getString(&node->curso.nomeDoCurso, enunciado);
  }

  // Falta outros.

  if (!confirm)
    printf("Não foi possivel execultar o prencher aluno!");

  return !confirm;
}

/**
 * @brief Exibe as informações de um curso.
 *
 * Mostra o código, o nome e todas as disciplinas associadas a um curso.
 * Usa a função `showAllDisciplina` para exibir a árvore de disciplinas do curso.
 *
 * @param curso Ponteiro para o curso a ser exibido.
 */
static void showCurso(NodeCurso *nodeCurso)
{
  printf("Curso: \n");
  printf("\tid: %d\n", nodeCurso->curso.codigo);
  printf("\tNome: %s", nodeCurso->curso.nomeDoCurso);
  printf("\tQuantidade de periodo: %d\n", nodeCurso->curso.quantidadeDePeriodo);
  showAllDisciplina(nodeCurso->curso.nodeDisciplina);
}

/**
 * @brief Exibe todas as informações de uma árvore de cursos.
 *
 * Função recursiva que percorre todos os nós de uma árvore binária de cursos
 * e exibe as informações de cada curso e suas respectivas disciplinas.
 *
 * @param curso Ponteiro para o nó raiz da árvore de cursos.
 */
void showAllCurso(NodeCurso *nodeCurso)
{
  if (nodeCurso)
  {
    showAllCurso(nodeCurso->esq);
    showAllCurso(nodeCurso->dir);
    showCurso(nodeCurso);
  }
}

/**
 * @brief Verifica se um curso com determinado ID está aberto.
 *
 * Função recursiva que percorre a árvore de cursos e compara o código de cada
 * curso com o ID fornecido. Se o curso for encontrado, a variável `bool` é
 * atualizada para 1.
 *
 * @param curso Ponteiro para o nó raiz da árvore de cursos.
 * @param id ID do curso a ser verificado.
 * @param bool Ponteiro para o valor de controle (1 se o curso for encontrado)
 */
void isCurseOpen(NodeCurso *node, int id, int *bool)
{
  if (node)
  {
    if (node->curso.codigo == id)
      *bool = 1;
    else
    {
      if (node->curso.codigo < id)
        isCurseOpen(node->dir, id, bool);
      else
        isCurseOpen(node->esq, id, bool);
    }
  }
}

void search_course(NodeCurso *raiz, int code, NodeCurso *result)
{
  if (raiz->curso.codigo == code || !raiz)
    result = raiz;
  else if (raiz->curso.codigo < code)
    search_course(raiz->dir, code, result);
  else if (raiz->curso.codigo > code)
    search_course(raiz->esq, code, result);
}

/**
 * @brief Insere um novo nó de curso na árvore binária.
 *
 * A função insere um novo curso na árvore binária, comparando o código do
 * novo curso com os cursos existentes e inserindo-o no local apropriado, de
 * acordo com a ordenação.
 *
 * @param raiz Ponteiro para o ponteiro do nó raiz da árvore de cursos.
 * @param node Ponteiro para o novo nó de curso a ser inserido.
 */
int inserctionCurso(NodeCurso **raiz, NodeCurso *node)
{
  int confirm = 1;

  if (!*raiz)
    *raiz = node;
  else
  {
    if (node->curso.codigo < (*raiz)->curso.codigo)
      confirm = inserctionCurso(&(*raiz)->esq, node);
    else if (node->curso.codigo > (*raiz)->curso.codigo)
      confirm = inserctionCurso(&(*raiz)->dir, node);
    else
      confirm = 0;
  }

  return confirm;
}

/**
 * @brief Cadastra um novo curso e o insere na árvore de cursos.
 *
 * A função aloca memória para um novo curso, preenche suas informações
 * chamando `prencherCurso` e o insere na árvore binária de cursos através de
 * `inserctionCurso`. Se houver falha durante o preenchimento do curso, a memória
 * alocada é liberada.
 *
 * @param nodeCurso Ponteiro para o ponteiro da árvore de cursos.
 * @return Retorna 1 se o curso foi cadastrado com sucesso, 0 caso contrário.
 */
int cadastrarCursos(NodeCurso **nodeCurso)
{
  int confirm = 1;
  NodeCurso *new = alocCurso();
  if (prencherCurso(new))
  {
    freeNodeCurso(new);
    confirm = 0;
  }

  if (confirm)
    if (!inserctionCurso(nodeCurso, new))
    {
      freeNodeCurso(new);
      confirm = 0;
    }

  return confirm;
}

// int buscarDisciplina(ListAluno *alunos, int codDisciplina)
// {
//   ListAluno *aux = alunos;
//   int encontrou = 0;
//   while (aux != NULL)
//   {
//     NodeDisciplina *disciplina = aux->aluno->nodeDisciplina;
//     while (disciplina != NULL)
//     {
//       if (disciplina->codDisciplina == codDisciplina)
//       {
//         encontrou = 1;
//       }
//       disciplina = disciplina->dir;
//     }
//     aux = aux->prox;
//   }
//   return encontrou;
// }

// NodeDisciplina *removerDisciplina(NodeDisciplina *raiz, int codDisciplina, ListAluno *aluno)
// {

//   if (raiz != NULL)
//   {
//     if (raiz->codDisciplina == codDisciplina)
//     {
//       // remove nos folhas
//       if (raiz->esq == NULL && raiz->dir == NULL)
//       {
//         free(raiz);
//         return NULL;
//       }
//       else
//       {
//         // remove nos que possui apenas um filho
//         if (raiz->esq == NULL || raiz->dir == NULL)
//         {
//           NodeDisciplina *temp;
//           if (raiz->esq != NULL)
//           {
//             temp = raiz->esq;
//           }
//           else
//           {
//             temp = raiz->dir;
//           }
//           free(raiz);
//           return temp;
//         }
//         else
//         {
//           NodeDisciplina *aux = raiz->esq;
//           while (aux->dir != NULL)
//           {
//             aux = aux->dir;
//           }
//           raiz->codDisciplina = aux->codDisciplina;
//           aux->codDisciplina = codDisciplina;
//           raiz->esq = removerDisciplina(raiz->esq, codDisciplina);
//           return raiz;
//         }
//       }
//     }
//     else
//     {
//       if (raiz->esq > codDisciplina)
//         raiz->esq = removerDisciplina(raiz->esq, codDisciplina);
//       else
//         raiz->dir = removerDisciplina(raiz->dir, codDisciplina);
//       return raiz;
//     }
//   }
// }

// NodeCurso *removerDisciplinaCurso(ListAluno *aluno, int codDisciplina)
// {

//   int encontrou = buscarDisciplina(aluno, codDisciplina);

//   if (encontrou == 0)
//   {
//     raiz->nodeDisciplina = removerDisciplina(raiz->nodeDisciplina, codDisciplina, aluno);
//   }

//   return raiz;
// }
NodeCurso *buscarCurso(NodeCurso *curso, int codigo)
{
  NodeCurso *aux = NULL;
  if (curso != NULL)
  {
    if (codigo == curso->curso.codigo)
    {
      aux = curso;
    }
    else
    {
      if (codigo < curso->curso.codigo)
      {
        aux = buscarCurso(curso->esq, codigo);
      }
      else
      {
        aux = buscarCurso(curso->dir, codigo);
      }
    }
  }
  return aux;
}
