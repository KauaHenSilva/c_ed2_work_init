#include <stdio.h>

#include <aluno_crud.h>
#include <curso_crud.h>
#include <disciplina_crud.h>

#include <utils.h>

int main()
{
  ListAluno *alunos = NULL;
  NodeCurso *cursos = NULL;

  cadastrarCursos(&cursos);
  cadastrarAlunos(&alunos, cursos);

  cadastrarCursos(&cursos);
  cadastrarAlunos(&alunos, cursos);

  cadastrarCursos(&cursos);
  cadastrarAlunos(&alunos, cursos);

  cadastrarDisciplinas(cursos);
  cadastrarDisciplinas(cursos);
  cadastrarDisciplinas(cursos);

  showAllAlunos(alunos);
  showAllCurso(cursos);

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}