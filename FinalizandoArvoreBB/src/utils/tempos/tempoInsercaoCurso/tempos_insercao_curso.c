#include "../../../core/curso/curso.h"
#include "../../../arvoreBB/arvore_bb.h"

#include "tempos_insercao_curso.h"
#include "../auxTempo/aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void defCurso(Arvore *arvoreCurso_list, int idx, int value)
{
  arvoreCurso_list[idx].info.curso.codigo = value;
  arvoreCurso_list[idx].info.curso.quantidadeDePeriodo = value;
  arvoreCurso_list[idx].info.curso.arvoreDisciplinas = NULL;
  arvoreCurso_list[idx].info.curso.nomeDoCurso = NULL;
  arvoreCurso_list[idx].dir = NULL;
  arvoreCurso_list[idx].esq = NULL;
}

static void resetarValoresDaArvoreCurso(Arvore *raizCurso)
{
  if (raizCurso)
  {
    resetarValoresDaArvoreCurso(raizCurso->esq);
    resetarValoresDaArvoreCurso(raizCurso->dir);
    raizCurso->esq = NULL;
    raizCurso->dir = NULL;
  }
}

static void defCursoType(Arvore *cursos_list, TipoDeOrdenacao type)
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
    defCurso(cursos_list, i, vet[i]);
}

static void tempoDeInsercoesCurso(Arvore *arvoreTemporaria, Arvore *CursosInserir_list, clock_t *tempo)
{
  clock_t inicio, fim;

  for (int x = 0; x < QTDCURSOTESTADOS; x++)
  {
    int inseriu;
    inicio = clock();
    inseriu = insertTree(&arvoreTemporaria, &(CursosInserir_list[x]));
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

// static void exibirValoresInseridos(Arvore *arvoreCurso_list)
// {
//   printf("ValoresInseridos: ");
//   for (int i = 0; i < QTDCURSOTESTADOS; i++)
//     printf("[%02d]", arvoreCurso_list[i].info.curso.codigo);
//   printf("\n\n");
// }

static void exbirResultado(double media, char *titulo, Arvore *arvoreCursos_list)
{
  (void)arvoreCursos_list;
  printf("Teste: %s", titulo);
  printf("Resultado: %f\n\n", media);
  // exibirValoresInseridos(arvoreCursos_list);
}

static void restarListaValoresListaCurso(Arvore *arvoreCurso_list)
{
  for (int x = 0; x < QTDCURSOTESTADOS; x++)
  {
    arvoreCurso_list[x].dir = NULL;
    arvoreCurso_list[x].esq = NULL;
  }
}

static void tempoInsercionCurses(Arvore *arvoreCursosInserir_list, char *titulo)
{
  Arvore *arvoreTemporariaCurso = NULL;
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
  {
    arvoreTemporariaCurso = NULL;
    tempoDeInsercoesCurso(arvoreTemporariaCurso, arvoreCursosInserir_list, &tempos[i]);
    // é nessesario?
    resetarValoresDaArvoreCurso(arvoreTemporariaCurso);
    restarListaValoresListaCurso(arvoreCursosInserir_list);
  }

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  exbirResultado(mediaTempos, titulo, arvoreCursosInserir_list);
}

void testTempoCurso()
{
  char *titulo;

  Arvore arvoreCursos_list[QTDCURSOTESTADOS];

  defCursoType(arvoreCursos_list, CRESCENTE);
  titulo = "tempo de inserção de curso crescente\n";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, DECRESCENTE);
  titulo = "tempo de inserção de curso decrescente\n";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, ALEATORIO);
  titulo = "tempo de inserção de curso aleatório\n";
  tempoInsercionCurses(arvoreCursos_list, titulo);
}