#include <stdio.h>
#include <stdlib.h>

#include "../curso/curso.h"
#include "../disciplina/disciplina.h"
#include "../nota/nota.h"

#include "../../utils/get/get.h"
#include "../../utils/validacoes/validacoes.h"

/**
 * @brief Libera a memória alocada para um objeto do tipo NodeDisciplina.
 *
 * Esta função libera toda a memória associada ao objeto NodeDisciplina passado como parâmetro, garantindo que não haja vazamentos de memória.
 *
 * @param node Ponteiro para o uma struct NodeDisciplina que será liberado.
 */
void freeNodeDisciplina(Info info)
{
  if (info.disciplina.nomeDaDisciplina)
    free(info.disciplina.nomeDaDisciplina);
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
static void prencherDisciplina(Disciplina *disciplina, int periodo)
{
  disciplina->periodo = periodo;
  getInt(&disciplina->codigo, "Digite o codigo da disciplina: ");
  getString(&disciplina->nomeDaDisciplina, "Digite o nome da disciplina: ");
  getIntMult5(&disciplina->cargaHoraria, "Digite a carga horaria da disciplina: ");
}

/**
 * @brief Exibe as informações de uma disciplina.
 *
 * Esta função recebe uma estrutura Info contendo os dados de uma disciplina
 * e exibe essas informações de forma formatada.
 *
 * @param info Estrutura Info contendo os dados da disciplina a ser exibida.
 */
void showDisciplina(Info info)
{
  printf("Disciplina: \n");
  printf("\tid: %d\n", info.disciplina.codigo);
  printf("\tNome: %s", info.disciplina.nomeDaDisciplina);
  printf("\tPeriodo: %d\n", info.disciplina.periodo);
  printf("\tCarga Horaria: %d\n", info.disciplina.cargaHoraria);
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
int cadastrarDisciplinas(Arvore *arvoreCursos)
{
  int confirm = 1;

  int codCurso = 0;
  int periodo = 0;

  Arvore *arvoreCursoAtual = NULL;

  if (!arvoreCursos)
  {
    printf("Nenhum curso cadastrado\n");
    confirm = 0;
  }
  else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
  {
    printf("Curso invalido\n");
    confirm = 0;
  }
  else if (!getPeriodoValido(&periodo, arvoreCursoAtual->info.curso.quantidadeDePeriodo))
  {
    printf("periodo invalido\n");
    confirm = 0;
  }
  else
  {
    Arvore *newArvore;
    alocTree(&newArvore);
    prencherDisciplina(&newArvore->info.disciplina, periodo);

    if (!insertTree(&arvoreCursoAtual->info.curso.arvoreDisciplinas, newArvore))
    {
      freeTree(newArvore, freeNodeDisciplina);
      confirm = 0;
    }
  }

  return confirm;
}
