#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno_crud.h"
#include "../curso_crud/curso_crud.h"
#include "../matricula_crud/matricula_crud.h"
#include "../nota_crud/nota_crud.h"

#include "../../utils/utils.h"

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
  (*new)->aluno.codigoDoCurso = -1;
  (*new)->aluno.matricula = -1;
  (*new)->aluno.nome = NULL;
  (*new)->aluno.nodeMatricula = NULL;
  (*new)->aluno.nodeNota = NULL;
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
static void freeAluno(ListAluno *listAluno)
{
  if (listAluno->aluno.nome)
    free(listAluno->aluno.nome);

  freeNodeMatriculas(listAluno->aluno.nodeMatricula);
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
static int prencherAluno(Aluno *aluno, int codigoCurso)
{
  printf("Para sair só digite 'sair'.\n");

  int confirm = 1;
  char *enunciado;

  aluno->codigoDoCurso = codigoCurso;

  enunciado = "Digite a matricula do aluno: ";
  confirm = getInt(&aluno->matricula, enunciado);

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
void showAluno(ListAluno *listAluno)
{
  printf("Aluno: \n");
  printf("\tCursoId: %d\n", listAluno->aluno.codigoDoCurso);
  printf("\tMatricula: %d\n", listAluno->aluno.matricula);
  printf("\tNome: %s\n", listAluno->aluno.nome);
  
  showAllMatriculas(listAluno->aluno.nodeMatricula);
  showAllNotas(listAluno->aluno.nodeNota);
}

void search_aluno(ListAluno *aluno, int code, ListAluno **result)
{
  if (aluno)
  {
    if (aluno->aluno.matricula == code && !*result)
      *result = aluno;

    search_aluno(aluno->prox, code, result);
  }
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
void inserctionAluno(ListAluno **listAlunos, Aluno new)
{
  if (!*listAlunos)
  {
    *listAlunos = (ListAluno *)malloc(sizeof(ListAluno));
    (*listAlunos)->ant = NULL;
    (*listAlunos)->prox = NULL;
    (*listAlunos)->aluno = new;
  }
  else
  {
    // Adidiconar no inicio
    if (strcmp(new.nome, (*listAlunos)->aluno.nome) < 0)
    {
      ListAluno *aux = *listAlunos;
      *listAlunos = (ListAluno *)malloc(sizeof(ListAluno));
      (*listAlunos)->aluno = new;
      (*listAlunos)->prox = aux;
      aux->ant = *listAlunos;
    }
    else
    {
      // Adicionar no final
      if (!(*listAlunos)->prox)
      {
        ListAluno *aux = *listAlunos;
        while (aux->prox)
          aux = aux->prox;

        aux->prox = (ListAluno *)malloc(sizeof(ListAluno));
        aux->prox->ant = aux;
        aux->prox->aluno = new;
      }

      // Adicionar no meio
      else
      {
        ListAluno *aux = *listAlunos;
        while (aux->prox && strcmp(new.nome, aux->prox->aluno.nome) > 0)
          aux = aux->prox;

        if (aux->prox)
        {
          ListAluno *temp = aux->prox;
          aux->prox = (ListAluno *)malloc(sizeof(ListAluno));
          aux->prox->ant = aux;
          aux->prox->prox = temp;
          aux->prox->aluno = new;
          temp->ant = aux->prox;
        }
      }
    }
  }
}
/**
 * @brief Exibe todos os alunos da lista.
 *
 * Função recursiva que percorre a lista encadeada de alunos e exibe as
 * informações de cada aluno. A função chama `showAllAlunos` para o próximo nó
 * até que o fim da lista seja alcançado, e em seguida chama `showAluno` para exibir
 * o aluno atual.
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
 * alocada para cada nó da lista. A função chama `freeAlunosList` para o próximo nó
 * até que o fim da lista seja alcançado, e em seguida chama `freeAluno` para
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
 * A função aloca memória para um novo aluno, preenche os dados do aluno usando a função `prencherAluno`
 * e insere o aluno na lista se o preenchimento for bem-sucedido. Se o cadastro do aluno falhar,
 * a memória alocada para o aluno é liberada.
 *
 * @param alunos Ponteiro para o ponteiro da lista de alunos.
 * @param cursos Ponteiro para a lista de cursos disponíveis (usado no preenchimento do aluno).
 *
 * @return Retorna 1 se o cadastro foi bem-sucedido, ou 0 caso contrário.
 */
int cadastrarAlunos(ListAluno **alunos, int codigoCurso)
{
  ListAluno *new;
  alocAluno(&new);

  if (prencherAluno(&new->aluno, codigoCurso))
    freeAluno(new);
  
  if (new)
    inserctionAluno(alunos, new->aluno);

  return new ? 1 : 0;
}


