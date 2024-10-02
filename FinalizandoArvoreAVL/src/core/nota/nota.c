#include <stdlib.h>
#include <stdio.h>

#include "../nota/nota.h"
#include "../matricula/matricula.h"
#include "../disciplina/disciplina.h"

#include "../../utils/get/get.h"
#include "../../utils/validacoes/validacoes.h"

/**
 * @brief Preenche os dados de uma nota com base na entrada do usuário.
 *
 * Solicita ao usuário o código da disciplina para preencher a nota.
 * Se a entrada for inválida, a função retorna um erro.
 *
 * @param raizNota Ponteiro para a raiz de nota a ser preenchido.
 * @param raizDisciplina Ponteiro para a raiz de nota a ser preenchido.
 * @return Retorna 1 se o preenchimento foi bem-sucedido, 0 caso contrário.
 */
static void prencherNota(Nota *nota, int codDisciplina)
{
  nota->codDisciplina = codDisciplina;
  getInt(&nota->semestreCursado, "Digite o semestre cursado: ");
  getInt(&nota->notaFinal, "Digite a nota final do aluno: ");
}

/**
 * @brief Exibe os dados de uma nota.
 *
 * Mostra o código da disciplina associado à nota.
 *
 * @param node Ponteiro para o nó de nota a ser exibido.
 */
void showNota(Info info)
{
  printf("Notas:\n");
  printf("\tCodDisciplina: %d\n", info.nota.codDisciplina);
  printf("\tNotaFinal: %d\n", info.nota.notaFinal);
  printf("\tSemestreCursado: %d\n", info.nota.semestreCursado);
}

/**
 * @brief Cadastra as notas de um aluno para uma disciplina específica em um semestre cursado.
 *
 * @param aluno Ponteiro para a lista de alunos.
 * @param codDisciplina Código da disciplina para a qual as notas serão cadastradas.
 * @param semestreCursado Semestre em que a disciplina foi cursada.
 * @return int Retorna 0 em caso de sucesso, ou um código de erro em caso de falha.
 */
int cadastrarNotas(ListAluno *alunos)
{
  int confirm = 1;

  int codAluno;
  int codMatricula;

  Arvore *arvoreMatriculaAtual = NULL;

  ListAluno *alunoAtual = NULL;

  if (!alunos)
  {
    printf("Nenhum aluno ou curso cadastrado.\n");
    confirm = 0;
  }
  else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
  {
    printf("Aluno invalido\n");
    confirm = 0;
  }
  else if (!getMatriculaValida(&codMatricula, alunos->aluno.arvoreMatricula, &arvoreMatriculaAtual))
  {
    printf("Disciplina invalida\n");
    confirm = 0;
  }
  else
  {
    Info infoMatricula;
    infoMatricula.matricula.codigo = codMatricula;
    if (!removerNodeArvore(&alunoAtual->aluno.arvoreMatricula, infoMatricula))
    {
      printf("Matricula não encontrada na arvore de matriculas\n");
      confirm = 0;
    }
    else
    {
      Arvore *newTree;
      alocTree(&newTree);
      prencherNota(&newTree->info.nota, codMatricula);

      if (!insertTree(&alunoAtual->aluno.arvoreNota, newTree))
      {
        freeTree(newTree, NULL);
        confirm = 0;
      }
    }
  }

  return confirm;
}