#include "actions.h"

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

static void showDisciplinaAndCurso(NodeMatricula *matricula, NodeDisciplina *disciplina)
{
  if (disciplina)
  {
    if (matricula->codDisciplina == disciplina->disciplina.codDisciplina)
      showDisciplina(disciplina);

    showDisciplinaAndCurso(matricula, disciplina->esq);
    showDisciplinaAndCurso(matricula, disciplina->dir);
  }
}

void mostrarDisciplinasDeUmAluno(ListAluno *aluno, NodeCurso *curso)
{
  if (aluno)
  {
    if (aluno->aluno.codigoDoCurso == curso->curso.codigo)
      showDisciplinaAndCurso(aluno->aluno.nodeMatricula, curso->curso.nodeDisciplina);

    mostrarDisciplinasDeUmAluno(aluno, curso->esq);
    mostrarDisciplinasDeUmAluno(aluno, curso->dir);
  }
}

static void showAllNotasByPeriod(NodeNota *nota, NodeDisciplina *disciplina, int periodo)
{
  if (nota)
  {
    if (disciplina->disciplina.periodo == periodo)
      showNota(nota);

    showAllNotasByPeriod(nota, disciplina->esq, periodo);
    showAllNotasByPeriod(nota, disciplina->dir, periodo);
  }
}

void mostrarNotasDeUmAlunoPorPeriodo(ListAluno *aluno, NodeCurso *curso, int periodo)
{
  if (aluno)
  {
    if(aluno->aluno.codigoDoCurso == curso->curso.codigo)
      showAllNotasByPeriod(aluno->aluno.nodeNota, curso->curso.nodeDisciplina, periodo);

    mostrarNotasDeUmAlunoPorPeriodo(aluno, curso->esq, periodo);
    mostrarNotasDeUmAlunoPorPeriodo(aluno, curso->dir, periodo);
  }
}
