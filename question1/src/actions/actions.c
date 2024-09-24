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

// static void showAllNotasByPeriod(NodeNota *nota, NodeDisciplina *disciplina, int periodo)
// {
//   if (disciplina)
//   {
//     if (disciplina->disciplina.periodo == periodo)
//       showNota(nota);

//     showAllNotasByPeriod(nota, disciplina->esq, periodo);
//     showAllNotasByPeriod(nota, disciplina->dir, periodo);
//   }
// }

// void mostrarNotasDeUmAlunoPorPeriodo(ListAluno *aluno, NodeCurso *curso, int periodo)
// {
//   if (curso)
//   {
//     if (aluno->aluno.codigoDoCurso == curso->curso.codigo)
//       showAllNotasByPeriod(aluno->aluno.nodeNota, curso->curso.nodeDisciplina, periodo);

//     mostrarNotasDeUmAlunoPorPeriodo(aluno, curso->esq, periodo);
//     mostrarNotasDeUmAlunoPorPeriodo(aluno, curso->dir, periodo);
//   }
// }

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

void disciplinasPorNotaOuMatricula(NodeDisciplina *disciplinas, NodeNota *notas, NodeMatricula *matriculas)
{
  if (disciplinas)
  {
    NodeNota *nota = NULL;
    NodeMatricula *matricula = NULL;

    if ((nota = buscarNotas(notas, disciplinas->disciplina.codDisciplina)) ||
        (matricula = buscarMatriculas(matriculas, disciplinas->disciplina.codDisciplina)))
    {
      if (nota)
      {
        printf("Essa disciplina com o id %d já foi paga!\n", disciplinas->disciplina.codDisciplina);
        showDisciplina(disciplinas);
      }
      else
        showDisciplina(disciplinas);
    }

    disciplinasPorNotaOuMatricula(disciplinas->esq, notas, matriculas);
    disciplinasPorNotaOuMatricula(disciplinas->dir, notas, matriculas);
  }
}

void imprimirHistoricoAluno(ListAluno *aluno, NodeCurso *cursos)
{
  NodeCurso *curso = buscarCurso(cursos, aluno->aluno.codigoDoCurso);
  printf("- Nome do curso: %s\n", curso->curso.nomeDoCurso);

  printf("- disciplinas:\n");
  disciplinasPorNotaOuMatricula(
      curso->curso.nodeDisciplina,
      aluno->aluno.nodeNota, aluno->aluno.nodeMatricula);

  printf("- Notas por periodo:\n");
  for (int i = 1; i <= curso->curso.quantidadeDePeriodo; i++)
  {
    printf("- Notas do aluno %d no periodo %d: \n", aluno->aluno.matricula, i);
    mostrarNotasDeUmAlunoPorPeriodo(aluno->aluno.nodeNota, i);
  }
}
