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
  Relatorio *relatorioCurso = testTempoCurso();
  Relatorio **relatorioBuscaNota = testTempoBuscaNotaDisciplina();

  printf("\n\n");
  for (int i = 0; i < 3; i++)
    showRelatorio(&relatorioCurso[i]);

  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      showRelatorio(&relatorioBuscaNota[i][j]);
    printf("\n\n");
  }

  free(relatorioCurso);

  for (int i = 0; i < 3; i++)
    free(relatorioBuscaNota[i]);
  free(relatorioBuscaNota);
}