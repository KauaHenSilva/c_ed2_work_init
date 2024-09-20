#include <stdio.h>
#include <stdlib.h>

#include "crud/aluno_crud/aluno_crud.h"
#include "crud/curso_crud/curso_crud.h"
#include "crud/disciplina_crud/disciplina_crud.h"
#include "crud/matricula_crud/matricula_crud.h"
#include "crud/nota_crud/nota_crud.h"

#include "actions/actions.h"

void mainCadrastrarMatricula(ListAluno *aluno, NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    cadastrarMatriculas(aluno, disciplina->disciplina.codDisciplina);
    mainCadrastrarMatricula(aluno, disciplina->esq);
    mainCadrastrarMatricula(aluno, disciplina->dir);
  }
}

void mainCadrastrarAllMatriculaCurse(ListAluno *aluno, NodeCurso *curso)
{
  if (curso)
  {
    if (curso->curso.codigo == aluno->aluno.codigoDoCurso)
      mainCadrastrarMatricula(aluno, curso->curso.nodeDisciplina);
    mainCadrastrarAllMatriculaCurse(aluno, curso->esq);
    mainCadrastrarAllMatriculaCurse(aluno, curso->dir);
  }
}

int main()
{
  ListAluno *alunos = NULL;
  NodeCurso *cursos = NULL;

  for (int x = 0; x < 10; x++)
  {
    printf("Cadrastrando Cursos: \n\n");
    if (!cadastrarCursos(&cursos))
      printf("Erro ao cadastrar curso\n");
    printf("\n");
  }

  for (int x = 0; x < 10; x++)
  {
    printf("Cadrastrando Aluno: \n\n");
    // tem que fazer uma função para passar o curso desejado.
    cadastrarAlunos(&alunos, (cursos->curso).codigo);
    printf("\n");
  }

  for (int x = 0; x < 5; x++)
  {
    printf("Cadrastrando Disciplina: \n\n");
    // tem que fazer uma função para passar o curso desejado.
    if (!cadastrarDisciplinas(cursos))
      printf("Erro ao cadastrar disciplina\n");
    printf("\n");
  }

  printf("Cadrastrando Matricula: \n\n");
  mainCadrastrarAllMatriculaCurse(alunos, cursos);

  // for (int x = 0; x < 5; x++)
  // {
  //   printf("Cadrastrando Nota: \n\n");
  //   // tem que fazer uma função para passar o aluno e o codigo da disciplina desejado.
  //   if (!cadastrarNotas(alunos, (cursos->curso).nodeDisciplina->disciplina.codDisciplina))
  //     printf("Erro ao cadastrar nota\n");

  //   printf("\n");
  // }

  printf("Todos os campus cadastrados! \n\n");
  getchar();

  mostrarTodosOsAlunosDeUmCurso(cursos, alunos);

  printf("Testes de Raissa! \n\n");
  getchar();

  NodeCurso *curso;
  NodeDisciplina *disciplina;

  int codCurso;
  int codDisciplina;

  printf("Digite o codigo do curso: ");
  scanf("%d", &codCurso);
  curso = buscarCurso(cursos, codCurso);
  
  printf("Digite o codigo da disciplina: ");
  scanf("%d", &codDisciplina);
  disciplina = buscar_disciplina(cursos->curso.nodeDisciplina, codDisciplina);
  
  if (disciplina->esq == NULL && disciplina->dir == NULL)
  {
    curso->curso.nodeDisciplina = removerDisciplinaDeUmCurso(curso->curso.nodeDisciplina, codDisciplina);
    printf("Disciplina removida com sucesso.\n");
  }

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}