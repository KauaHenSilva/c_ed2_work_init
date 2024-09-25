#include "../crud/curso_crud/curso_crud.h"

#include "tempos_insercao_curso.h"
#include "aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  int vet[QTDCURSOTESTADOS];

  switch (type)
  {
  case CRESCENTE:
    vetIntCrescente(vet, QTDCURSOTESTADOS);
    break;
  case DECRESCENTE:
    vetIntDecrescente(vet, QTDCURSOTESTADOS);
    break;
  case ALEATORIO:
    vetIntAleatorioSemRepeticao(vet, QTDCURSOTESTADOS);
    break;
  default:
    break;
  }

  for (int i = 0; i < QTDCURSOTESTADOS; i++)
    defCurso(cursos, i, vet[i]);
}

static Relatorio tempInsercionCurse(NodeCurso *listaCursosInserir, char *titulo)
{
  NodeCurso *arvoreTemporaria;
  double tempos[QTDTESTES];

  clock_t inicio, fim;

  for (int i = 0; i < QTDTESTES; i++)
  {
    arvoreTemporaria = NULL;
    clock_t tempo = 0;

    for (int x = 0; x < QTDCURSOTESTADOS; x++)
    {
      inicio = clock();
      inserctionCurso(&arvoreTemporaria, &(listaCursosInserir[x]));
      fim = clock();

      tempo += (fim - inicio);
    }

    tempos[i] = ((double)tempo) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f - ", tempos[i]);
    printf("Nome do teste: %s", titulo);
    resetValuesCurso(listaCursosInserir, QTDCURSOTESTADOS);
  }

  double mediaTempos = 0;
  for (int i = 0; i < QTDTESTES; i++)
    mediaTempos += tempos[i];

  Relatorio relatorio;
  relatorio.titulo = titulo;
  relatorio.tempo = mediaTempos / QTDTESTES;
  relatorio.quantidadeDeElementos = QTDCURSOTESTADOS;
  return relatorio;
}

Relatorio *testTempoCurso()
{
  Relatorio *relatorio = (Relatorio *)malloc(3 * sizeof(Relatorio));

  NodeCurso cursos[QTDCURSOTESTADOS];

  defCursoType(cursos, CRESCENTE);
  char *titulo = "tempo de inserção de curso crescente\n";
  relatorio[0] = tempInsercionCurse(cursos, titulo);

  defCursoType(cursos, DECRESCENTE);
  titulo = "tempo de inserção de curso decrescente\n";
  relatorio[1] = tempInsercionCurse(cursos, titulo);

  defCursoType(cursos, ALEATORIO);
  titulo = "tempo de inserção de curso aleatório\n";
  relatorio[2] = tempInsercionCurse(cursos, titulo);

  return relatorio;
}
