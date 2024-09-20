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
    // tem que fazer uma função para passar o curso desejado.
    cadastrarAlunos(&alunos, (cursos->curso).codigo);
    printf("\n");
  }

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Disciplina: \n\n");
    // tem que fazer uma função para passar o curso desejado.
    cadastrarDisciplinas(cursos);
    printf("\n");
  }

  for (int x = 0; x < 3; x++)
  {
    printf("Cadrastrando Matricula: \n\n");
    // tem que fazer uma função para passar o aluno e o codigo da disciplina desejado.
    cadastrarMatriculas(alunos, (cursos->curso).nodeDisciplina->disciplina.codDisciplina);
    printf("\n");
  }

  for (int x = 0; x < 2; x++)
  {
    printf("Cadrastrando Nota: \n\n");
    // tem que fazer uma função para passar o aluno e o codigo da disciplina desejado.
    cadastrarNotas(alunos, (cursos->curso).nodeDisciplina->disciplina.codDisciplina);
    printf("\n");
  }

  showAllAlunos(alunos);
  showAllCurso(cursos);

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}