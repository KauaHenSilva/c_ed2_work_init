#include <stdio.h>
#include <stdlib.h>

#include "core/aluno/aluno.h"
#include "core/curso/curso.h"
#include "core/disciplina/disciplina.h"
#include "core/matricula/matricula.h"
#include "core/nota/nota.h"
#include "core/buscas/buscas.h"
#include "arvoreBB/arvore_bb.h"

#include "utils/menu/menu.h"
#include "utils/tempos/mainTempo/tempos.h"

int main()
{
  ListAluno *listAlunos = NULL;
  Arvore *arvoreCursos = NULL;

  initMenu(listAlunos, arvoreCursos);

  testAllTempo();

  freeAlunosList(listAlunos);
  freeTree(arvoreCursos, freeNodeCurso);
  return 0;
}