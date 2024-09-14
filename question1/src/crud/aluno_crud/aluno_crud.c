#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aluno_crud.h>
#include <curso_crud.h>
#include <matricula_crud.h>

#include <utils.h>

/**
 * @brief Aloca memória para uma nova estrutura ListAluno e inicializa seus membros.
 *
 * Esta função aloca memória para uma nova estrutura ListAluno e define seus membros
 * para valores padrão. Especificamente, define 'codigoDoCurso' e 'matricula' como -1,
 * e inicializa 'nome', 'nodeMatricula', 'nodeNota', 'ant' e 'prox' como NULL.
 *
 * @param new Uma refernecia para um ponteiro para uma estrutura ListAluno que será alocada e inicializada.
 */
static void alocAluno(ListAluno **new)
{
  *new = (ListAluno *)malloc(sizeof(ListAluno));
  (*new)->codigoDoCurso = -1;
  (*new)->matricula = -1;
  (*new)->nome = NULL;
  (*new)->nodeMatricula = NULL;
  (*new)->nodeNota = NULL;
  (*new)->ant = NULL;
  (*new)->prox = NULL;
}

/**
 * @brief Libera a memória alocada para um objeto do tipo ListAluno.
 *
 * Esta função libera toda a memória associada ao objeto ListAluno passado como parâmetro,
 * garantindo que não haja vazamentos de memória.
 *
 * @param aluno Ponteiro para o uma struct ListAluno que será liberado.
 */
static void freeAluno(ListAluno *aluno)
{
  if (aluno->nome)
    free(aluno->nome);

  freeNodeMatriculas(aluno->nodeMatricula);
  free(aluno);
}

/**
 * @brief Preenche os dados de um aluno.
 *
 * Esta função solicita ao usuário que insira os dados de um aluno, como o código do curso,
 * matrícula e nome. Se o modo de depuração (DEBUG_MODE) estiver desativado, a função também
 * verifica se o curso está cadastrado.
 *
 * @param aluno Ponteiro para a estrutura ListAluno onde os dados do aluno serão armazenados.
 * @param cursos Ponteiro para a estrutura NodeCurso contendo a lista de cursos cadastrados.
 *
 * @return Retorna 0 se os dados foram preenchidos com sucesso, ou 1 se houve algum erro.
 */
static int prencherAluno(ListAluno *aluno, NodeCurso *cursos)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  enunciado = "Digite o codigo do Curso: ";
  confirm = getInt(&aluno->codigoDoCurso, enunciado);

  int verificacao = 0;
  isCurseOpen(cursos, aluno->codigoDoCurso, &verificacao);
  if (verificacao)
  {
    printf("Curso não cadastrado!\n");
    return 1;
  }

  if (confirm)
  {
    enunciado = "Digite a matricula do aluno: ";
    confirm = getInt(&aluno->matricula, enunciado);
  }

  if (confirm)
  {
    enunciado = "Digite o nome do aluno: ";
    confirm = getString(&aluno->nome, enunciado);
  }

  // Falta alguns.

  if (!confirm)
    printf("Não foi possivel execultar o prencher aluno!");

  return !confirm;
}

/**
 * @brief Exibe as informações de um aluno.
 *
 * Esta função imprime no console as informações de um aluno, incluindo
 * o código do curso, matrícula, nome e todas as matrículas associadas.
 *
 * @param aluno Ponteiro para a estrutura ListAluno que contém as informações do aluno.
 */
static void showAluno(ListAluno *aluno)
{
  printf("Aluno: \n");
  printf("\tid: %d\n", aluno->codigoDoCurso);
  printf("\tMatricula: %d\n", aluno->matricula);
  printf("\tNome: %s\n", aluno->nome);

  showAllMatriculas(aluno->nodeMatricula);
}

/**
 * @brief Insere um novo aluno na lista de alunos de forma ordenada.
 *
 * A função insere um novo aluno na lista de alunos de acordo com o código do curso
 * e o nome do aluno, mantendo a lista ordenada. A inserção pode ocorrer no início,
 * no meio ou no final da lista.
 *
 * @param alunos Ponteiro duplo para a lista de alunos.
 * @param new Ponteiro para o novo aluno a ser inserido.
 */
void inserctionAluno(ListAluno **alunos, ListAluno *new)
{
  if (!*alunos)
    *alunos = new;
  else
  {
    // Adidiconar no inicio
    if (new->codigoDoCurso < (*alunos)->codigoDoCurso)
    {
      new->prox = *alunos;
      (*alunos)->ant = new;
      *alunos = new;
    }
    else
    {
      // Adicionar no final
      if (!(*alunos)->prox)
      {
        new->ant = *alunos;
        (*alunos)->prox = new;
      }

      // Adicionar no meio
      else
      {
        ListAluno *aux = *alunos;
        while (aux->prox && strcmp(new->nome, aux->prox->nome))
          aux = aux->prox;

        new->prox = aux;
        new->ant = aux->ant;
        aux->ant->prox = new;
        aux->ant = new;
      }
    }
  }
}

void showAllAlunos(ListAluno *alunos)
{
  if (alunos)
  {
    showAllAlunos(alunos->prox);
    showAluno(alunos);
  }
}

void freeAlunosList(ListAluno *alunos)
{
  if (alunos)
  {
    freeAlunosList(alunos->prox);
    freeAluno(alunos);
  }
}

int cadastrarAlunos(ListAluno **alunos, NodeCurso *cursos)
{
  ListAluno *new;
  alocAluno(&new);

  if (prencherAluno(new, cursos))
    freeAluno(new);

  if (new)
    inserctionAluno(alunos, new);

  return new ? 1 : 0;
}
