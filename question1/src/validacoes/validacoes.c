#include "validacoes.h"

#include "../crud/curso_crud/curso_crud.h"
#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/disciplina_crud/disciplina_crud.h"
#include "../crud/matricula_crud/matricula_crud.h"

#include "../utils/utils.h"

#include <stdio.h>

int getPeriodoValido(int *periodo, int quantidadeDePeriodo)
{
  int isOk = 1;
  do
  {
    getInt(periodo, "Digite o período: ");
    if (*periodo < 1 || *periodo > quantidadeDePeriodo)
      printf("Período inválido!\n");
  } while (*periodo < 1 || *periodo > quantidadeDePeriodo);

  return isOk;
}

int getCursoValido(int *codigoDoCurso, NodeCurso *cursos, NodeCurso **atual)
{
  int isValide = 1;

  if (!cursos)
    isValide = 0;

  while (!*atual && isValide)
  {
    getInt(codigoDoCurso, "Digite o código do curso: ");
    search_course(cursos, *codigoDoCurso, atual);

    if (!*atual)
      printf("Curso não encontrado!\n");
  }

  return isValide;
}

int getAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual)
{
  int isValide = 1;

  if (!alunos)
    isValide = 0;

  while (!*atual && isValide)
  {
    getInt(matricula, "Digite a matrícula do aluno: ");
    search_aluno(alunos, *matricula, atual);

    if (!*atual)
      printf("Aluno não encontrado!\n");
  }

  return isValide;
}

int getDisciplinaValida(int *codigoDoCurso, NodeDisciplina *nodeDisciplina, NodeDisciplina **disciplinaAtual)
{
  int isValide = 1;

  if (!nodeDisciplina)
    isValide = 0;

  while (!*disciplinaAtual && isValide)
  {
    getInt(codigoDoCurso, "Digite o código da disciplina: ");
    buscarDisciplina(nodeDisciplina, *codigoDoCurso, disciplinaAtual);

    if (!*disciplinaAtual)
      printf("Disciplina não encontrada!\n");
  }

  return isValide;
}

int getMatriculaValida(int *codigoDoCurso, NodeMatricula *nodeMatricula, NodeMatricula **matriculaAtual)
{
  int isValide = 1;

  if (!nodeMatricula)
    isValide = 0;

  while (!*matriculaAtual && isValide)
  {
    getInt(codigoDoCurso, "Digite o código da matrícula: ");
    search_matricula(nodeMatricula, *codigoDoCurso, matriculaAtual);

    if (!*matriculaAtual)
      printf("Matrícula não encontrada!\n");
  }

  return isValide;
}