#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

#include "../crud/curso_crud/curso_crud.h"

#include "testes.h"

static int exists(int *numbers, int size, int n)
{
  int isExists = 0;
  for (int i = 0; i < size && isExists == 0; i++)
    if (numbers[i] == n)
      isExists = 1;

  return isExists;
}

double tempInsercionCurse(NodeCurso *nodeCurso, int qtdCursos)
{
  NodeCurso *temp = NULL;

  clock_t inicio, fim;

  double testes[QTDTESTES];

  for (int i = 0; i < QTDTESTES; i++)
  {
    inicio = clock();

    for (int i = 0; i < qtdCursos; i++)
      inserctionCurso(&temp, &(nodeCurso[i]));

    fim = clock();

    testes[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f\n", testes[i]);
  }

  double media = 0;
  for (int i = 0; i < QTDTESTES; i++)
    media += testes[i];

  printf("Media: %f\n", media / QTDTESTES);
  return media / QTDTESTES;
}

void testTimeCurso()
{
  NodeCurso cursos[QTDCURSO];

  // Cursos em ordem crescente
  for (int i = 0; i < QTDCURSO; i++)
  {
    cursos[i].curso.codigo = i;
    cursos[i].curso.quantidadeDePeriodo = i;
    cursos[i].curso.nomeDoCurso = "Curso";
    cursos[i].curso.nodeDisciplina = NULL;
    cursos[i].dir = NULL;
    cursos[i].esq = NULL;
  }

  printf("Inicio do teste de tempo de inserção de curso em ordem crescente\n");
  tempInsercionCurse(cursos, QTDCURSO);

  // Inverter a ordem dos cursos
  for (int x = 0, y = QTDCURSO - 1; x < y; x++, y--)
  {
    NodeCurso temp = cursos[x];
    cursos[x] = cursos[y];
    cursos[y] = temp;
  }

  printf("Inicio do teste de tempo de inserção de curso em ordem decrescente\n");
  tempInsercionCurse(cursos, QTDCURSO);

  srand((unsigned)time(NULL));

  // Cursos aleatórios que podem se repetir
  for (int i = 0; i < QTDCURSO; i++)
  {
    cursos[i].curso.codigo = rand() % 1000000;
    cursos[i].curso.quantidadeDePeriodo = rand() % 1000;
    cursos[i].curso.nomeDoCurso = "Curso";
    cursos[i].curso.nodeDisciplina = NULL;
    cursos[i].dir = NULL;
    cursos[i].esq = NULL;
  }

  printf("Inicio do teste de tempo de inserção de curso aleatório que pode se repetir\n");
  tempInsercionCurse(cursos, QTDCURSO);

  // Cursos em ordem aleatória que não se repetem
  int numbers[QTDCURSO];
  for (int i = 0; i < QTDCURSO; i++)
  {
    int n = rand() % 1000000;
    while (exists(numbers, i, n))
      n = rand() % 1000000;

    numbers[i] = n;
  }

  for (int i = 0; i < QTDCURSO; i++)
  {
    cursos[i].curso.codigo = numbers[i];
    cursos[i].curso.quantidadeDePeriodo = i;
    cursos[i].curso.nomeDoCurso = "Curso";
    cursos[i].curso.nodeDisciplina = NULL;
    cursos[i].dir = NULL;
    cursos[i].esq = NULL;
  }

  printf("Inicio do teste de tempo de inserção de curso em ordem aleatória que não se repetem\n");
  tempInsercionCurse(cursos, QTDCURSO);

  // Cursos em ordem aleatória que se repetem
  for (int i = 0; i < QTDCURSO; i++)
  {
    cursos[i].curso.codigo = 1;
    cursos[i].curso.quantidadeDePeriodo = i;
    cursos[i].curso.nomeDoCurso = "Curso";
    cursos[i].curso.nodeDisciplina = NULL;
    cursos[i].dir = NULL;
    cursos[i].esq = NULL;
  }

  printf("Inicio do teste de tempo de inserção de curso em se repetem\n");
  tempInsercionCurse(cursos, QTDCURSO);

}