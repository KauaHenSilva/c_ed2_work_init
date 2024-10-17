#include "../../../arvoreAVL/arvore_avl.h"

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
  inserir_temporario->info.codigo = inserir->info.codigo;
  inserir_temporario->altura = -1;

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
  clock_t tempos[QTDTESTES] = {0};

  for (int i = 0; i < QTDCURSOTESTADOS - 1; i++)
    if (!insertTree(&arvoreTemporariaCurso, &(arvoreCursosInserir_list[i])))
      perror("Não conseguiu inserir o valor");

  for (int i = 0; i < QTDTESTES; i++)
    tempoDeInsercoesCurso(arvoreTemporariaCurso, &(arvoreCursosInserir_list[QTDCURSOTESTADOS - 1]), tempos + i);

  double mediaTempos;
  mediaTempoEmSegundos(tempos, &mediaTempos);

  exbirResultado(mediaTempos, titulo);
}

void testTempoInsercao1Curso()
{
  char *titulo;
  Arvore arvoreCursos_list[QTDCURSOTESTADOS];

  defCursoType(arvoreCursos_list, CRESCENTE);
  titulo = "tempo de inserção de um curso crescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, DECRESCENTE);
  titulo = "tempo de inserção de um curso decrescente";
  tempoInsercionCurses(arvoreCursos_list, titulo);

  defCursoType(arvoreCursos_list, ALEATORIO);
  titulo = "tempo de inserção de um curso aleatório";
  tempoInsercionCurses(arvoreCursos_list, titulo);
}