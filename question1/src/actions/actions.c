#include "actions.h"
#include <stdio.h>

#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/curso_crud/curso_crud.h"
#include "../crud/disciplina_crud/disciplina_crud.h"
#include "../crud/nota_crud/nota_crud.h"
#include "../crud/matricula_crud/matricula_crud.h"

void mostrarTodosOsAlunosDeUmCurso(NodeCurso *curso, ListAluno *alunos)
{
  if (alunos)
  {
    if (curso->curso.codigo == alunos->aluno.codigoDoCurso)
      showAluno(alunos);
    mostrarTodosOsAlunosDeUmCurso(curso, alunos->prox);
  }
}

void MostrarTodosOsCursosDoCampus(NodeCurso *cursos)
{
  showAllCurso(cursos);
}

void mostrarTodasAsDisciplinasDeUmCurso(NodeCurso *curso)
{
  showAllDisciplina(curso->curso.nodeDisciplina);
}

static void showAllDisciplinaByPeriod(NodeDisciplina *disciplina, int periodo)
{
  if (disciplina)
  {
    if (disciplina->disciplina.periodo == periodo)
      showDisciplina(disciplina);
    showAllDisciplinaByPeriod(disciplina->esq, periodo);
    showAllDisciplinaByPeriod(disciplina->dir, periodo);
  }
}

void mostrarDisciplinasDeUmPeriodoDeUmCurso(NodeCurso *curso, int periodo)
{
  showAllDisciplinaByPeriod(curso->curso.nodeDisciplina, periodo);
}

void showRelacaoMatriculaCurso(NodeCurso *curso, ListAluno *alunos)
{
  if (alunos)
  {
    if (curso->curso.codigo == alunos->aluno.codigoDoCurso)
      showAllMatriculas(alunos->aluno.nodeMatricula);
    showRelacaoMatriculaCurso(curso, alunos->prox);
  }
}

void mostrarDisciplinasDeUmAluno(NodeMatricula *matriculasAluno, NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    if (matriculasAluno->codDisciplina == disciplina->disciplina.codDisciplina)
      showDisciplina(disciplina);

    mostrarDisciplinasDeUmAluno(matriculasAluno, disciplina->esq);
    mostrarDisciplinasDeUmAluno(matriculasAluno, disciplina->dir);
  }
}

void mostrarNotasDeUmAlunoPorPeriodo(NodeNota *raiz, int periodo)
{
  if (raiz)
  {
    if (raiz->nota.semestreCursado == periodo)
      showNota(raiz);
    mostrarNotasDeUmAlunoPorPeriodo(raiz->esq, periodo);
    mostrarNotasDeUmAlunoPorPeriodo(raiz->dir, periodo);
  }
}

void mostrarNotaDeUmaDisciplina(NodeNota *raiz, NodeDisciplina *disciplina)
{
  if (raiz)
  {
    if (raiz->nota.codDisciplina == disciplina->disciplina.codDisciplina)
      showNota(raiz);
    mostrarNotaDeUmaDisciplina(raiz->esq, disciplina);
    mostrarNotaDeUmaDisciplina(raiz->dir, disciplina);
  }
}

void imprimirHistoricoAluno(ListAluno *aluno, NodeCurso *cursos)
{
  NodeCurso *curso;

  if (searchCourse(cursos, aluno->aluno.codigoDoCurso, &curso))
    printf("- Nome do curso: %s\n", curso->curso.nomeDoCurso);
  else
    printf("- Curso não encontrado!\n");

  printf("- disciplinas:\n");
  showAllDisciplina(curso->curso.nodeDisciplina);

  printf("- Notas por periodo:\n");
  for (int i = 1; i <= curso->curso.quantidadeDePeriodo; i++)
  {
    printf("- Notas do aluno %d no periodo %d: \n", aluno->aluno.matricula, i);
    mostrarNotasDeUmAlunoPorPeriodo(aluno->aluno.nodeNota, i);
  }
}
