#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../../core/curso/curso.h"
#include "../../../core/aluno/aluno.h"
#include "../../../core/disciplina/disciplina.h"
#include "../../../core/nota/nota.h"

#include "tempos.h"
#include "../auxTempo/aux.h"

#include "../tempoBuscaNota/tempos_busca_nota.h"
#include "../tempoInsercaode100Curso/tempos_insercao_de_1000_curso.h"
#include "../tempoInsercaode1curso/tempos_insercao_de_1_curso.h"

void testAllTempo()
{
  testTempoInsercao1Curso();
  testTempoInsercao1000Curso();
  testTempoBuscaNotaDisciplina();
}