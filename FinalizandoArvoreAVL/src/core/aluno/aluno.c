#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"
#include "../curso/curso.h"
#include "../matricula/matricula.h"
#include "../nota/nota.h"

#include "../../utils/get/get.h"
#include "../../utils/validacoes/validacoes.h"

#include "../../arvoreAVL/arvore_avl.h"

/**
 * @brief Aloca memória para uma nova estrutura ListAluno e inicializa seus
 * membros.
 *
 * Esta função aloca memória para uma nova estrutura ListAluno e define seus
 * membros para valores padrão. Especificamente, define 'codigoDoCurso' e
 * 'matricula' como -1, e inicializa 'nome', 'nodeMatricula', 'nodeNota', 'ant'
 * e 'prox' como NULL.
 *
 * @param new Uma refernecia para um ponteiro para uma estrutura ListAluno que
 * será alocada e inicializada.
 */
static void alocAluno(ListAluno **new)
{
  *new = (ListAluno *)malloc(sizeof(ListAluno));
  (*new)->prox = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo ListAluno.
 *
 * Esta função libera toda a memória associada ao objeto ListAluno passado como
 * parâmetro, garantindo que não haja vazamentos de memória.
 *
 * @param aluno Ponteiro para o uma struct ListAluno que será liberado.
 */
static void freeAluno(ListAluno *listAluno)
{
  if (listAluno->aluno.nome)
    free(listAluno->aluno.nome);
}

/**
 * @brief Preenche os dados de um aluno.
 *
 * Esta função solicita ao usuário que insira os dados de um aluno, como o
 * código do curso, matrícula e nome. Se o modo de depuração (DEBUG_MODE)
 * estiver desativado, a função também verifica se o curso está cadastrado.
 *
 * @param aluno Ponteiro para a estrutura ListAluno onde os dados do aluno serão
 *  armazenados.
 * @param cursos Ponteiro para a estrutura NodeCurso contendo a lista de cursos
 * cadastrados.
 *
 * @return Retorna 0 se os dados foram preenchidos com sucesso, ou 1 se houve
 * algum erro.
 */
static void prencherAluno(Aluno *aluno, int codigoCurso)
{
  aluno->codigoDoCurso = codigoCurso;
  getInt(&aluno->matricula, "Digite a matricula do aluno: ");
  getString(&aluno->nome, "Digite o nome do aluno: ");
}

/**
 * @brief Exibe as informações de um aluno.
 *
 * Esta função imprime no console as informações de um aluno, incluindo
 * o código do curso, matrícula, nome e todas as matrículas associadas.
 *
 * @param aluno Ponteiro para a estrutura ListAluno que contém as informações do
 * aluno.
 */
void showAluno(ListAluno *listAluno)
{
  printf("Aluno: \n");
  printf("\tCursoId: %d\n", listAluno->aluno.codigoDoCurso);
  printf("\tMatricula: %d\n", listAluno->aluno.matricula);
  printf("\tNome: %s\n", listAluno->aluno.nome);

  showTree(listAluno->aluno.arvoreMatricula, showMatricula);
  showTree(listAluno->aluno.arvoreNota, showNota);
}

/**
 * @brief Procura um aluno na lista de alunos pelo código.
 *
 * Esta função percorre a lista de alunos e procura um aluno que tenha o código
 * especificado. Se o aluno for encontrado, o ponteiro result é atualizado para
 * apontar para o aluno encontrado.
 *
 * @param aluno Ponteiro para a lista de alunos.
 * @param code Código do aluno a ser procurado.
 * @param result Ponteiro para armazenar o resultado da busca (aluno encontrado).
 * @return int Retorna 1 se o aluno for encontrado, 0 caso contrário.
 */
int searchAluno(ListAluno *aluno, int code, ListAluno **result)
{
  int confirm = 1;

  if (aluno)
  {
    if (aluno->aluno.matricula == code && !*result)
      *result = aluno;
    else
      confirm = searchAluno(aluno->prox, code, result);
  }
  else
    confirm = 0;

  return confirm;
}

/**
 * @brief Verifica se um aluno está matriculado.
 *
 * Esta função verifica se um aluno, identificado pelo código fornecido, está
 * matriculado na lista de alunos.
 *
 * @param aluno Ponteiro para a lista de alunos.
 * @param code Código do aluno a ser verificado.
 * @return Retorna 1 se o aluno estiver matriculado, caso contrário, retorna 0.
 */
static int alunoMatriculado(ListAluno *aluno, int code)
{
  int confirm = 1;

  if (aluno)
  {
    if (aluno->aluno.matricula == code)
      confirm = 0;
    else
      confirm = alunoMatriculado(aluno->prox, code);
  }

  return confirm;
}

/**
 * @brief Insere um novo aluno na lista de alunos de forma ordenada.
 *
 * A função insere um novo aluno na lista de alunos de acordo com o código do
 * curso e o nome do aluno, mantendo a lista ordenada. A inserção pode ocorrer
 * no início, no meio ou no final da lista.
 *
 * @param alunos Ponteiro duplo para a lista de alunos.
 * @param new Ponteiro para o novo aluno a ser inserido.
 */
int inserctionAluno(ListAluno **AlunoRaiz, Aluno newValue)
{
  int isAdd = alunoMatriculado(*AlunoRaiz, newValue.matricula);

  ListAluno *newList;
  newList = (ListAluno *)malloc(sizeof(ListAluno));
  newList->aluno = newValue;
  newList->prox = NULL;

  if (isAdd)
  {
    if (!*AlunoRaiz)
      *AlunoRaiz = newList;
    else
    {
      if (!(*AlunoRaiz)->prox)
      {
        if (myStrCmp((*AlunoRaiz)->aluno.nome, newValue.nome) == PRIMEIRO_ARGUMENTO_MENOR)
          (*AlunoRaiz)->prox = newList;
        else
        {
          newList->prox = *AlunoRaiz;
          *AlunoRaiz = newList;
        }
      }
      else
      {
        ListAluno *aux = *AlunoRaiz;

        while (aux->prox &&
               myStrCmp(aux->prox->aluno.nome, newValue.nome) == PRIMEIRO_ARGUMENTO_MENOR)
          aux = aux->prox;

        if (myStrCmp(aux->aluno.nome, newValue.nome) == PRIMEIRO_ARGUMENTO_MENOR)
        {
          newList->prox = aux->prox;
          aux->prox = newList;
        }
        else
        {
          newList->prox = aux;
          *AlunoRaiz = newList;
        }
      }
    }
  }

  return isAdd;
}

/**
 * @brief Exibe todos os alunos da lista.
 *
 * Função recursiva que percorre a lista encadeada de alunos e exibe as
 * informações de cada aluno. A função chama `showAllAlunos` para o próximo nó
 * até que o fim da lista seja alcançado, e em seguida chama `showAluno` para
 * exibir o aluno atual.
 *
 * @param alunos Ponteiro para o primeiro nó da lista de alunos.
 */
void showAllAlunos(ListAluno *alunos)
{
  if (alunos)
  {
    showAllAlunos(alunos->prox);
    showAluno(alunos);
  }
}

/**
 * @brief Libera a memória alocada para a lista de alunos.
 *
 * Função recursiva que percorre a lista encadeada de alunos e libera a memória
 * alocada para cada nó da lista. A função chama `freeAlunosList` para o próximo
 * nó até que o fim da lista seja alcançado, e em seguida chama `freeAluno` para
 * liberar o aluno atual.
 *
 * @param alunos Ponteiro para o primeiro nó da lista de alunos.
 */
void freeAlunosList(ListAluno *alunos)
{
  if (alunos)
  {
    freeAlunosList(alunos->prox);
    freeAluno(alunos);
  }
}

/**
 * @brief Cadastra um novo aluno na lista de alunos.
 *
 * A função aloca memória para um novo aluno, preenche os dados do aluno usando
 * a função `prencherAluno` e insere o aluno na lista se o preenchimento for
 * bem-sucedido. Se o cadastro do aluno falhar, a memória alocada para o aluno é
 * liberada.
 *
 * @param alunos Ponteiro para o ponteiro da lista de alunos.
 * @param cursos Ponteiro para a lista de cursos disponíveis (usado no
 * preenchimento do aluno).
 *
 * @return Retorna 1 se o cadastro foi bem-sucedido, ou 0 caso contrário.
 */
int cadastrarAlunos(ListAluno **alunos, Arvore *arvoreCursos)
{
  int confirm = 1;

  int codCurso = 0;
  Arvore *arvoreCursoAtual = NULL;

  if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
  {
    printf("Curso invalido\n");
    confirm = 0;
  }
  else
  {
    ListAluno *new;
    alocAluno(&new);

    prencherAluno(&new->aluno, codCurso);

    if (!inserctionAluno(alunos, new->aluno))
    {
      freeAluno(new);
      confirm = 0;
    }
  }

  return confirm;
}
