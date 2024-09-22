#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "crud/aluno_crud/aluno_crud.h"
#include "crud/curso_crud/curso_crud.h"
#include "crud/disciplina_crud/disciplina_crud.h"
#include "crud/matricula_crud/matricula_crud.h"
#include "crud/nota_crud/nota_crud.h"

#include "testes/testes.h"

#include "actions/actions.h"

int main()
{
  testAll();
  return 0;
}