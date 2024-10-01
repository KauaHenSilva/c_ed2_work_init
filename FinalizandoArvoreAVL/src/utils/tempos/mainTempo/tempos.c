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
#include "../tempoInsercaoCurso/tempos_insercao_curso.h"

void testAllTempo()
{
  testTempoCurso();
  testTempoBuscaNotaDisciplina();
}