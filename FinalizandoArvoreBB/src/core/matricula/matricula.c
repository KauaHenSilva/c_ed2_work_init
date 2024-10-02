#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../matricula/matricula.h"
#include "../disciplina/disciplina.h"
#include "../nota/nota.h"
#include "../../arvoreBB/arvore_bb.h"

#include "../../utils/get/get.h"
#include "../../utils/validacoes/validacoes.h"

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
int cadastrarMatriculas(ListAluno *alunos, Arvore *arvoreCursos)
{
  int confirm = 1;

  int codCurso;
  int codAluno;
  int codDisciplina;

  Arvore *arvoreNotaAtual = NULL;
  Arvore *arvoreCursoAtual = NULL;
  Arvore *arvoreDisciplinaAtual = NULL;
  Arvore *arvoreDisciplinas = NULL;

  ListAluno *alunoAtual = NULL;

  if (!alunos || !arvoreCursos)
  {
    printf("Nenhum aluno ou curso cadastrado!\n");
    confirm = 0;
  }
  else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
    printf("Curso invalido\n");
  else if (!(arvoreDisciplinas = arvoreCursoAtual->info.curso.arvoreDisciplinas))
    printf("Curso sem disciplinas\n");
  else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
    printf("Aluno invalido\n");
  else if (!getDisciplinaValida(&codDisciplina, arvoreDisciplinas, &arvoreDisciplinaAtual))
    printf("Disciplina invalida\n");
  else
  {
    Info info1;
    info1.nota.codDisciplina = codDisciplina;
    if (searchNodeTree(alunoAtual->aluno.arvoreNota, info1, &arvoreNotaAtual))
    {
      // Não entedi "conter somente um código de disciplina do curso do aluno", mas acho que é isso

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

      newArvore->info.matricula.codigo = codDisciplina;

      if (!insertTree(&alunoAtual->aluno.arvoreMatricula, newArvore))
      {
        confirm = 0;
        freeTree(newArvore, NULL);
      }
    }
  }

  return confirm;
}