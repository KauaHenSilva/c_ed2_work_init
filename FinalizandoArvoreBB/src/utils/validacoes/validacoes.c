#include "validacoes.h"

#include "../../core/curso/curso.h"
#include "../../core/aluno/aluno.h"
#include "../../core/disciplina/disciplina.h"
#include "../../core/matricula/matricula.h"

#include "../get/get.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getPeriodoValido(int *periodo, int quantidadeDePeriodo)
{
  int isOk = 1;

  getInt(periodo, "Digite o período: ");
  if (*periodo < 1 || *periodo > quantidadeDePeriodo)
    isOk = 0;

  return isOk;
}

int getCursoValido(int *codigoDoCurso, Arvore *arvoreCurso, Arvore **arvoreCursoAtual)
{
  int isValide = 1;

  getInt(codigoDoCurso, "Digite o código do curso: ");
  Info info;
  info.curso.codigo = *codigoDoCurso;

  if (!searchNodeTree(arvoreCurso, info, arvoreCursoAtual))
    isValide = 0;

  return isValide;
}

int getAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual)
{
  int isValide = 1;

  getInt(matricula, "Digite a matrícula do aluno: ");
  if (!searchAluno(alunos, *matricula, atual))
    isValide = 0;

  return isValide;
}

int getDisciplinaValida(int *codigoDoCurso, Arvore *arvoreDisciplina, Arvore **arvoreDisciplinaAtual)
{
  int isValide = 1;

  getInt(codigoDoCurso, "Digite o código da disciplina: ");
  Info info;
  info.disciplina.codigo = *codigoDoCurso;

  if (!searchNodeTree(arvoreDisciplina, info, arvoreDisciplinaAtual))
    isValide = 0;

  return isValide;
}

int getMatriculaValida(int *codigoMatricula, Arvore *arvoreMatricula, Arvore **arvoreMatriculaAtual)
{
  int isValide = 1;

  getInt(codigoMatricula, "Digite o código da matrícula: ");
  Info info;
  info.matricula.codigo = *codigoMatricula;

  if (!searchNodeTree(arvoreMatricula, info, arvoreMatriculaAtual))
    isValide = 0;

  return isValide;
}

int boolAlunoInDisciplina(ListAluno *aluno, int disciplina)
{
  int bool = 0;
  if (aluno)
  {
    Info info;
    info.codigo = disciplina;

    Arvore *arvoreDisciplina = NULL;
    if (searchNodeTree(aluno->aluno.arvoreMatricula, info, &arvoreDisciplina))
      bool = 1;
    else
      bool = boolAlunoInDisciplina(aluno->prox, disciplina);
  }
  return bool;
}

NomeCmp myStrCmp(char *texto1, char *texto2)
{
  char *temp1, *temp2;

  temp1 = (char *)malloc(sizeof(char) * sizeof(texto1));
  temp2 = (char *)malloc(sizeof(char) * sizeof(texto2));

  strcpy(temp1, texto1);
  strcpy(temp2, texto2);

  for (int x = 0; x < (int)sizeof(temp1); x++)
    if (temp1[x] >= 'A' && temp1[x] <= 'Z')
      temp1[x] += 32;

  for (int x = 0; x < (int)sizeof(temp2); x++)
    if (temp2[x] >= 'A' && temp2[x] <= 'Z')
      temp2[x] += 32;

  NomeCmp resp = strcmp(temp1, temp2);

  if (resp > 0)
    resp = PRIMEIRO_ARGUMENTO_MAIOR;
  else if (resp < 0)
    resp = PRIMEIRO_ARGUMENTO_MENOR;
  else
    resp = PRIMEIRO_ARGUMENTO_IGUAL;

  free(temp1);
  free(temp2);

  return resp;
}