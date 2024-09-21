#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

#include "../crud/curso_crud/curso_crud.h"
#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/disciplina_crud/disciplina_crud.h"
#include "../crud/nota_crud/nota_crud.h"

#include "testes.h"

static void defCurso(NodeCurso *curso, int idx, int value)
{
  curso[idx].curso.codigo = value;
  curso[idx].curso.quantidadeDePeriodo = value;
  curso[idx].curso.nodeDisciplina = NULL;
  curso[idx].curso.nomeDoCurso = NULL;
  curso[idx].dir = NULL;
  curso[idx].esq = NULL;
}

static void resetValuesCurso(NodeCurso *curso, int qtdCursos)
{
  if (curso)
  {
    resetValuesCurso(curso->esq, qtdCursos);
    resetValuesCurso(curso->dir, qtdCursos);
    curso->esq = NULL;
    curso->dir = NULL;
  }
}

static void defCursoType(NodeCurso *cursos, TipoDeOrdenacao type)
{
  for (int i = 0; i < QTDCURSO; i++)
    switch (type)
    {
    case CRESCENTE:
      defCurso(cursos, i, i);
      break;
    case DECRESCENTE:
      defCurso(cursos, i, QTDCURSO - i);
      break;

    case ALEATORIO:
      defCurso(cursos, i, rand() % QTDCURSO / 2);
      break;
    }
}

static Relatorio tempInsercionCurse(NodeCurso *nodeCurso, char *titulo)
{
  NodeCurso *temp;
  double tempos[QTDTESTES];
  int naoAchados[QTDTESTES] = {0};

  clock_t inicio, fim;

  for (int i = 0; i < QTDTESTES; i++)
  {
    temp = NULL;
    clock_t tempo = 0;

    for (int x = 0; x < QTDCURSO; x++)
    {
      int achou;

      inicio = clock();
      achou = inserctionCurso(&temp, &(nodeCurso[x]));
      fim = clock();

      tempo += (fim - inicio);

      if (!achou)
        naoAchados[i]++;
    }
    tempos[i] = ((double)tempo) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f - ", tempos[i]);
    printf("Não achados: %d\n", naoAchados[i]);
    resetValuesCurso(nodeCurso, QTDCURSO);
  }

  double mediaTempos = 0;
  for (int i = 0; i < QTDTESTES; i++)
    mediaTempos += tempos[i];

  int mediaNaoAchados = 0;
  for (int i = 0; i < QTDTESTES; i++)
    mediaNaoAchados += naoAchados[i];

  Relatorio relatorio;
  relatorio.titulo = titulo;
  relatorio.tempo = mediaTempos / QTDTESTES;
  relatorio.qtdFalhas = mediaNaoAchados / QTDTESTES;

  return relatorio;
}

Relatorio *testTimeCurso()
{
  Relatorio *relatorio = (Relatorio *)malloc(3 * sizeof(Relatorio));

  NodeCurso cursos[QTDCURSO];

  defCursoType(cursos, CRESCENTE);

  char *titulo = "tempo de inserção de curso em ordem crescente\n";
  printf("%s", titulo);
  relatorio[0] = tempInsercionCurse(cursos, titulo);

  defCursoType(cursos, DECRESCENTE);

  titulo = "tempo de inserção de curso em ordem decrescente\n";
  printf("%s", titulo);
  relatorio[1] = tempInsercionCurse(cursos, titulo);

  defCursoType(cursos, ALEATORIO);

  titulo = "tempo de inserção de curso aleatório\n";
  printf("%s", titulo);
  relatorio[2] = tempInsercionCurse(cursos, titulo);

  return relatorio;
}

static Relatorio tempBuscaNota(ListAluno Aluno, NodeNota *nodeNota, char *titulo)
{
  NodeNota *temp = Aluno.aluno.nodeNota;

  double Tempos[QTDTESTES];
  int naoAchados[QTDTESTES] = {0};

  clock_t inicio, fim;

  for (int i = 0; i < QTDTESTES; i++)
  {
    clock_t tempo = 0;

    for (int x = 0; x < QTDNOTAS; x++)
    {
      int achou;

      inicio = clock();
      achou = buscar_nota(temp, nodeNota[x].nota.codDisciplina, NULL);
      fim = clock();

      tempo += (fim - inicio);
      if (!achou)
        naoAchados[i]++;
    }

    Tempos[i] = ((double)tempo) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f - ", Tempos[i]);
    printf("Não achados: %d\n", naoAchados[i]);
  }

  double somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += Tempos[i];

  int somaNaoAchados = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaNaoAchados += naoAchados[i];

  Relatorio relatorio;
  relatorio.titulo = titulo;
  relatorio.tempo = somaTempo / QTDTESTES;
  relatorio.qtdFalhas = somaNaoAchados / QTDTESTES;

  return relatorio;
}

static void defNotaTime(NodeNota *notas, int idx, int value)
{
  notas[idx].nota.codDisciplina = value;
  notas[idx].nota.semestreCursado = value;
  notas[idx].nota.notaFinal = value;
  notas[idx].dir = NULL;
  notas[idx].esq = NULL;
}

static void defNotaType(NodeNota *notas, TipoDeOrdenacao type)
{
  for (int i = 0; i < QTDNOTAS; i++)
    switch (type)
    {
    case CRESCENTE:
      defNotaTime(notas, i, i);
      break;
    case DECRESCENTE:
      defNotaTime(notas, i, QTDNOTAS - i);
      break;
    case ALEATORIO:
      defNotaTime(notas, i, rand() % (QTDNOTAS * 2));
      break;
    }
}

static Relatorio *bateriaDeTestes(ListAluno aluno, char **titulo)
{
  NodeNota notas[QTDNOTAS];

  Relatorio *relatorio = (Relatorio *)malloc(3 * sizeof(Relatorio));

  defNotaType(notas, CRESCENTE);

  char *tituloAtual = titulo[0];
  printf("%s", tituloAtual);
  relatorio[0] = tempBuscaNota(aluno, notas, tituloAtual);

  defNotaType(notas, DECRESCENTE);

  tituloAtual = titulo[1];
  printf("%s", tituloAtual);
  relatorio[1] = tempBuscaNota(aluno, notas, tituloAtual);

  defNotaType(notas, ALEATORIO);

  tituloAtual = titulo[2];
  printf("%s", tituloAtual);
  relatorio[2] = tempBuscaNota(aluno, notas, tituloAtual);

  return relatorio;
}

Relatorio **testTimeBuscaNotaDisciplina()
{
  srand((unsigned)time(NULL));

  NodeCurso curso;
  curso.curso.codigo = 1;
  curso.curso.nomeDoCurso = "Curso";
  curso.curso.quantidadeDePeriodo = 1;
  curso.curso.nodeDisciplina = NULL;
  curso.dir = NULL;
  curso.esq = NULL;

  ListAluno aluno;
  aluno.aluno.codigoDoCurso = curso.curso.codigo;
  aluno.aluno.nome = "Aluno";
  aluno.aluno.nodeMatricula = NULL;
  aluno.aluno.nodeNota = NULL;
  aluno.prox = NULL;

  NodeNota notasAluno[QTDNOTAS];

  Relatorio **relatorio = (Relatorio **)malloc(3 * sizeof(Relatorio *));

  defNotaType(notasAluno, CRESCENTE);

  for (int x = 0; x < QTDNOTAS; x++)
    inserctionNota(&aluno.aluno.nodeNota, &notasAluno[x]);

  char *titulosTestes1[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas cressente )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas cressente )\n",
      "tempo de busca de nota aleatório ( Lista de notas cressente )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas cressente )\n",
  };
  relatorio[0] = bateriaDeTestes(aluno, titulosTestes1);

  defNotaType(notasAluno, DECRESCENTE);
  char *titulosTestes2[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas decressente )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas decressente )\n",
      "tempo de busca de nota aleatório ( Lista de notas decressente )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas decressente )\n",
  };
  relatorio[1] = bateriaDeTestes(aluno, titulosTestes2);

  defNotaType(notasAluno, ALEATORIO);
  char *titulosTestes3[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas aleatório )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas aleatório )\n",
      "tempo de busca de nota aleatório ( Lista de notas aleatório )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas aleatório )\n",
  };
  relatorio[2] = bateriaDeTestes(aluno, titulosTestes3);

  return relatorio;
}

void showRelatorio(Relatorio *relatorio)
{
  printf("\n");
  printf("Titulo: %s", relatorio->titulo);
  printf("Tempo: %f\n", relatorio->tempo);
  printf("media de falhas: %d\n", relatorio->qtdFalhas);
}

void testAll()
{
  Relatorio *curso = testTimeCurso();
  Relatorio **disciplina = testTimeBuscaNotaDisciplina();

  printf("\n\n");
  for (int i = 0; i < 3; i++)
    showRelatorio(&curso[i]);

  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      showRelatorio(&disciplina[i][j]);
    printf("\n\n");
  }

  free(curso);
  for (int i = 0; i < 3; i++)
    free(disciplina[i]);
  free(disciplina);
}