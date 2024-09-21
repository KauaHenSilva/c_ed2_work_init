#pragma once

#include "../structs/struct_curso.h"

#define QTDCURSO 666
#define QTDNOTAS 666

#define QTDTESTES 30

typedef enum enTipoDeOrdenacao
{
  CRESCENTE,
  DECRESCENTE,
  ALEATORIO,
} TipoDeOrdenacao;

typedef struct stRelatorio
{
  char *titulo;
  double tempo;
  int qtdFalhas;
} Relatorio;

Relatorio *testTimeCurso();
Relatorio **testTimeBuscaNotaDisciplina();
void testAll();
