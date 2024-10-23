#include "../../../arvoreBB/arvore_bb.h"

#include "tempos_insercao_de_1_curso.h"
#include "../auxTempo/aux.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void tempoDeInsercoesCurso(Arvore *arvoreTemporaria, Arvore *inserir, clock_t *tempo)
{
  clock_t inicio, fim;
  int inseriu, removido = 0;

  Arvore *inserir_temporario = malloc(sizeof(Arvore));
  inserir_temporario->info = inserir->info;

  inicio = clock();
  inseriu = insertTree(&arvoreTemporaria, inserir_temporario);
  fim = clock();

  removido = removerNodeArvore(&arvoreTemporaria, inserir_temporario->info);

  if (!inseriu)
    perror("Não conseguiu inserir o valor");
  if (!removido)
    perror("Não conseguiu remover o valor");

  *tempo += (fim - inicio);

  // printf("o tempo de inserção: %lf\n", (((double)(*tempo)) / CLOCKS_PER_SEC));
}

static void tempoInsercionCurses(Arvore *arvoreCursosInserir_list, char *titulo)
{
  Arvore *arvoreTemporariaCurso = NULL;
  clock_t tempos[QTD_TESTES] = {0};

  for (int i = 0; i < QTD_CURSO_TESTADOS - 1; i++)
    if (!insertTree(&arvoreTemporariaCurso, &(arvoreCursosInserir_list[i])))
      perror("Não conseguiu inserir o valor");

  for (int i = 0; i < QTD_TESTES; i++)
    tempoDeInsercoesCurso(arvoreTemporariaCurso, &(arvoreCursosInserir_list[QTD_CURSO_TESTADOS - 1]), tempos + i);

  resetarListaValoresArvore(arvoreCursosInserir_list, QTD_CURSO_TESTADOS);
  arvoreTemporariaCurso = NULL;

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  for (int i = 0; i < QTD_TESTES; i++)
    printf("%lf,", (((double)tempos[i]) / CLOCKS_PER_SEC));
  printf("\n");

  exbirResultado(mediaTempos, titulo);
}

void testTempoInsercao1Curso()
{
  char *titulo;
  Arvore arvoreCursos_list[QTD_CURSO_TESTADOS];

  defArvoreListType(arvoreCursos_list, CRESCENTE, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de um curso crescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defArvoreListType(arvoreCursos_list, DECRESCENTE, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de um curso decrescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defArvoreListType(arvoreCursos_list, ALEATORIO, QTD_CURSO_TESTADOS);
  titulo = "tempo de inserção de um curso aleatório";
  tempoInsercionCurses(arvoreCursos_list, titulo);
}