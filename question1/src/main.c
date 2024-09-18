#include <stdio.h>

#include "crud/aluno_crud/aluno_crud.h"
#include "crud/curso_crud/curso_crud.h"
#include "crud/disciplina_crud/disciplina_crud.h"
#include "crud/matricula_crud/matricula_crud.h"
#include "crud/nota_crud/nota_crud.h"

int main()
{
  ListAluno *alunos = NULL;
  NodeCurso *cursos = NULL;

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Cursos: \n\n");
    cadastrarCursos(&cursos);
    printf("\n");
  }

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Aluno: \n\n");
    cadastrarAlunos(&alunos, cursos);
    printf("\n");
  }

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Disciplina: \n\n");
    cadastrarDisciplinas(cursos);
    printf("\n");
  }

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Matricula: \n\n");
    cadastrarMatriculas(alunos, cursos->nodeDisciplina);
    printf("\n");
  }

  for (int x = 0; x < 2; x++)
  {
    printf("Cadrastrando Nota: \n\n");
    cadastrarNotas(alunos);
    printf("\n");
  }

  showAllAlunos(alunos);
  showAllCurso(cursos);

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}