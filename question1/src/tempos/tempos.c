#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../crud/curso_crud/curso_crud.h"
#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/disciplina_crud/disciplina_crud.h"
#include "../crud/nota_crud/nota_crud.h"

#include "tempos.h"
#include "aux.h"

#include "tempos_busca_nota.h"
#include "tempos_insercao_curso.h"

void testAll()
{
  testTempoCurso();
  testTempoBuscaNotaDisciplina();
}