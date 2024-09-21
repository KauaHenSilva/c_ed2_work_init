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

void mainCadrastrarNota(ListAluno *aluno, NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    cadastrarNotas(aluno, disciplina->disciplina.codDisciplina);
    mainCadrastrarNota(aluno, disciplina->esq);
    mainCadrastrarNota(aluno, disciplina->dir);
  }
}

void mainCadrastrarAllNotaCurse(ListAluno *aluno, NodeCurso *curso)
{
  if (curso)
  {
    if (curso->curso.codigo == aluno->aluno.codigoDoCurso)
      mainCadrastrarNota(aluno, curso->curso.nodeDisciplina);
    mainCadrastrarAllNotaCurse(aluno, curso->esq);
    mainCadrastrarAllNotaCurse(aluno, curso->dir);
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
    cadastrarAlunos(&alunos, (cursos->curso).codigo);
    printf("\n");
  }

  // Cadrastrando 5 disciplinas para o curso 1
  for (int x = 0; x < 5; x++)
  {
    printf("Cadrastrando Disciplina: \n\n");
    if (!cadastrarDisciplinas(cursos, (rand() % cursos->curso.quantidadeDePeriodo + 1)))
      printf("Erro ao cadastrar disciplina\n");
    printf("\n");
  }

  // Cadrastrando aluno 1 em todas as disciplinas do curso 1
  printf("Cadrastrando todas as Matricula do curso do aluno 1: \n\n");
  mainCadrastrarAllMatriculaCurse(alunos, cursos);

  // Cadrastrando todas as Notas do curso do aluno 1
  printf("Cadrastrando todas as Notas do curso do aluno 1: \n\n");
  mainCadrastrarAllNotaCurse(alunos, cursos);

  printf("Todos os campus cadastrados! \n\n");
  getchar();

  printf("Mostar todos alunos de um curso: \n\n");
  printf("Curso: %d\n", cursos->curso.codigo);
  mostrarTodosOsAlunosDeUmCurso(cursos, alunos);

  getchar();

  printf("Mostar todos cursos do campus: \n\n");
  MostrarTodosOsCursosDoCampus(cursos);

  getchar();

  printf("Mostar todas disciplinas de um curso: \n\n");
  printf("Curso: %d\n", cursos->curso.codigo);
  mostrarTodasAsDisciplinasDeUmCurso(cursos);

  getchar();

  printf("Mostar todas disciplinas de um periodo de um curso: \n\n");
  printf("Curso: %d\n", cursos->curso.codigo);
  printf("Periodo: %d\n", cursos->curso.nodeDisciplina->disciplina.periodo);
  mostrarDisciplinasDeUmPeriodoDeUmCurso(cursos, cursos->curso.nodeDisciplina->disciplina.periodo);

  getchar();

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