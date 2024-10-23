#include "../../../core/curso/curso.h"
#include "../../../arvoreBB/arvore_bb.h"

#include "tempos_insercao_de_1000_curso.h"
#include "../auxTempo/aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void tempoDeInsercoesCurso(Arvore **arvoreTemporaria, Arvore *CursosInserir_list, clock_t *tempo)
{
  clock_t inicio = 0, fim = 0;

  for (int x = 0; x < QTD_CURSO_TESTADOS; x++)
  {
    int inseriu;
    inicio = clock();
    inseriu = insertTree(arvoreTemporaria, &(CursosInserir_list[x]));
    fim = clock();

    if (!inseriu)
      perror("Não conseguiu inserir o valor");

    *tempo += (fim - inicio);
  }

  // printf("o tempo de inserção: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

static void tempoInsercionCurses(Arvore *arvoreCursosInserir_list, char *titulo)
{
  Arvore *arvoreTemporariaCurso = NULL;
  clock_t tempos[QTD_TESTES] = {0};

  for (int i = 0; i < QTD_TESTES; i++)
  {
    tempoDeInsercoesCurso(&arvoreTemporariaCurso, arvoreCursosInserir_list, &tempos[i]);
    resetarListaValoresArvore(arvoreCursosInserir_list, QTD_CURSO_TESTADOS);
    arvoreTemporariaCurso = NULL;
  }

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  for (int i = 0; i < QTD_TESTES; i++)
    printf("%lf,", (((double)tempos[i]) / CLOCKS_PER_SEC));
  printf("\n");

  exbirResultado(mediaTempos, titulo);
}

void testTempoInsercao1000Curso()
{
  char *titulo;

  Arvore arvoreCursos_list[QTD_CURSO_TESTADOS];

  defArvoreListType(arvoreCursos_list, CRESCENTE, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de curso crescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defArvoreListType(arvoreCursos_list, DECRESCENTE, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de curso decrescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defArvoreListType(arvoreCursos_list, ALEATORIO, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de curso aleatório";
  tempoInsercionCurses(arvoreCursos_list, titulo);
}