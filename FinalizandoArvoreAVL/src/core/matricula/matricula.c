#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../matricula/matricula.h"
#include "../disciplina/disciplina.h"
#include "../nota/nota.h"

#include "../../utils/get/get.h"

/*
 * @brief Exibe as informações de uma matriculaa.
 * Esta função imprime no console o codigo de matricula.
 *
 * @param node Ponteiro para a estrutura NodeMatricula que contém a informação da matricula.
 */
void showMatricula(Info info)
{
  printf("Matricula:\n");
  printf("\tCodDisciplina: %d\n", info.matricula.codigo);
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

  Info info1;
  info1.nota.codDisciplina = idDisciplina;

  Arvore *arvoreNotaAtual = NULL;

  // Não entedi "conter somente um código de disciplina do curso do aluno", mas acho que é isso
  if (searchNodeTree(aluno->aluno.arvoreNota, info1, &arvoreNotaAtual))
  {
    printf("Aluno já possui uma nota nesta disciplina\n");
    // caso pode possuir mais de uma nota retire esse if.
    // Caso só pode ter uma nota, remova essa nota antes;

    // Exemplo de remoção, retire o else caso for utilizar.
    // removerNodeArvore(&aluno->aluno.arvoreNota, info1, compareInfoInfoNota);

    // caso for outra coisa, não sei acabou as ideias do que posa ser
    // "conter somente um código de disciplina do curso do aluno"

    confirm = 0;
  }
  else
  {
    Arvore *newArvore;
    alocTree(&newArvore);

    newArvore->info.matricula.codigo = idDisciplina;

    if (!insertTree(&aluno->aluno.arvoreMatricula, newArvore))
    {
      confirm = 0;
      freeTree(newArvore, NULL);
    }
  }

  return confirm;
}