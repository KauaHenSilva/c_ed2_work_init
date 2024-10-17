#include "../../../core/curso/curso.h"

#include "tempos_insercao_de_1000_curso.h"
#include "../auxTempo/aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static void tempoInsercionCurses(Arvore *arvoreCursosInserir_list, char *titulo)
{
  Arvore *arvoreTemporariaCurso = NULL;
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDTESTES; i++)
  {
    arvoreTemporariaCurso = NULL;
    tempoDeInsercoesCurso(arvoreTemporariaCurso, arvoreCursosInserir_list, &tempos[i]);
    resetarValoresDaArvoreCurso(arvoreTemporariaCurso);
    restarListaValoresListaCurso(arvoreCursosInserir_list);
  }

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  exbirResultado(mediaTempos, titulo);
}

void testTempoInsercao1000Curso()
{
  char *titulo;

  Arvore arvoreCursos_list[QTDCURSOTESTADOS];

  defCursoType(arvoreCursos_list, CRESCENTE);
  titulo = "tempo de inserção de curso crescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, DECRESCENTE);
  titulo = "tempo de inserção de curso decrescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, ALEATORIO);
  titulo = "tempo de inserção de curso aleatório";
  tempoInsercionCurses(arvoreCursos_list, titulo);
}