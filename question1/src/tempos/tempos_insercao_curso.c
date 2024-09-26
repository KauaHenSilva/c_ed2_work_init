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

static void resetarValoresDaArvoreCurso(NodeCurso *curso)
{
  if (curso)
  {
    resetarValoresDaArvoreCurso(curso->esq);
    resetarValoresDaArvoreCurso(curso->dir);
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

static void tempoDeInsercoesCurso(NodeCurso *arvoreTemporaria, NodeCurso *listaCursosInserir, clock_t *tempo)
{
  clock_t inicio, fim;

  for (int x = 0; x < QTDCURSOTESTADOS; x++)
  {
    int inseriu;
    inicio = clock();
    inseriu = inserctionCurso(&arvoreTemporaria, &(listaCursosInserir[x]));
    fim = clock();

    if (!inseriu)
      perror("Não conseguiu inserir o valor");

    *tempo += (fim - inicio);
  }

  // printf("o tempo de inserção: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

static void mediaTempoEmSegundos(clock_t *tempos, double *mediaTempos)
{
  clock_t somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += tempos[i];

  *mediaTempos = ((double)somaTempo / (CLOCKS_PER_SEC)) / (QTDTESTES);
}

// static void exibirValoresInseridos(NodeCurso *cursos)
// {
//   printf("ValoresInseridos: ");
//   for (int i = 0; i < QTDCURSOTESTADOS; i++)
//     printf("[%02d]", cursos[i].curso.codigo);
//   printf("\n\n");
// }

static void exbirResultado(double media, char *titulo, NodeCurso *cursos)
{
  (void)cursos;
  printf("Teste: %s", titulo);
  printf("Resultado: %f\n\n", media);
  // exibirValoresInseridos(cursos);
}

static void restarListaValoresListaCurso(NodeCurso *listaCurso)
{
  for (int x = 0; x < QTDCURSOTESTADOS; x++)
  {
    listaCurso[x].dir = NULL;
    listaCurso[x].esq = NULL;
  }
}

static void tempoInsercionCurses(NodeCurso *listaCursosInserir, char *titulo)
{
  NodeCurso *arvoreTemporaria = NULL;
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
  {
    arvoreTemporaria = NULL;
    tempoDeInsercoesCurso(arvoreTemporaria, listaCursosInserir, &tempos[i]);
    resetarValoresDaArvoreCurso(arvoreTemporaria);
    restarListaValoresListaCurso(listaCursosInserir);
  }

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  exbirResultado(mediaTempos, titulo, listaCursosInserir);
}

void testTempoCurso()
{
  char *titulo;

  NodeCurso cursos[QTDCURSOTESTADOS];

  defCursoType(cursos, CRESCENTE);
  titulo = "tempo de inserção de curso crescente\n";
  tempoInsercionCurses(cursos, titulo);

  defCursoType(cursos, DECRESCENTE);
  titulo = "tempo de inserção de curso decrescente\n";
  tempoInsercionCurses(cursos, titulo);

  defCursoType(cursos, ALEATORIO);
  titulo = "tempo de inserção de curso aleatório\n";
  tempoInsercionCurses(cursos, titulo);
}