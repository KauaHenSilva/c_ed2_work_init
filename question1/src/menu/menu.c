#include <stdio.h>
#include <stdlib.h>

#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/curso_crud/curso_crud.h"
#include "../crud/disciplina_crud/disciplina_crud.h"
#include "../crud/matricula_crud/matricula_crud.h"
#include "../crud/nota_crud/nota_crud.h"

#include "../actions/actions.h"
#include "../validacoes/validacoes.h"

#include "menu.h"

void menu(int *opcao)
{
  printf("1 - Cadastrar Curso\n");
  printf("2 - Cadastrar Disciplina\n");
  printf("3 - Cadastrar Aluno\n");
  printf("4 - Cadastrar Matricula\n");
  printf("5 - Cadastrar Nota\n");
  printf("6 - Mostrar Todos os Cursos\n");
  printf("7 - Mostrar Todos os Alunos de um Curso\n");
  printf("8 - Mostrar Todas as Disciplinas de um Curso\n");
  printf("9 - Mostrar Disciplinas de um Período de um Curso\n");
  printf("10 - Mostrar Disciplinas de um Aluno\n");
  printf("11 - Mostrar Notas de um Aluno por Período\n");
  printf("12 - Sair\n");
  printf("Digite a opção desejada: ");
  scanf("%d", opcao);
  printf("--------------------------------------------------------------\n");
}

#if DEBUG_MODE
void initMenu(ListAluno *alunos, NodeCurso *cursos)
{
  int opcao = 0;

  while (opcao != 12)
  {
    menu(&opcao);

    switch (opcao)
    {
    case 1:
      printf("Cadastrar Curso\n");
      cadastrarCursos(&cursos);
      break;
    case 2:
      if (cursos)
      {
        printf("[DUBUG] curso escolhido vugo primeiro [id]: %d\n", cursos->curso.codigo);
        if (!cadastrarDisciplinas(cursos, (rand() % cursos->curso.quantidadeDePeriodo + 1)))
          printf("Erro ao cadastrar disciplina\n");
      }
      else
        printf("Nenhum curso cadastrado!\n");
      break;
    case 3:
      if (cursos)
      {
        printf("[DUBUG] curso escolhido vugo primeiro [id]: %d\n", cursos->curso.codigo);
        if (!cadastrarAlunos(&alunos, (cursos->curso).codigo))
          printf("Erro ao cadastrar aluno\n");
      }
      else
        printf("Nenhum curso cadastrado!\n");
      break;
    case 4:
      if (alunos && cursos)
      {
        printf("[DUBUG] aluno escolhido vugo primeiro [id]: %d\n", alunos->aluno.matricula);
        printf("[DUBUG] curso escolhido vugo primeiro [id]: %d\n", cursos->curso.codigo);
        printf("[DUBUG] disciplina escolhida vugo primeiro [id]: %d\n", cursos->curso.nodeDisciplina->disciplina.codDisciplina);

        if (!cadastrarMatriculas(alunos, cursos->curso.nodeDisciplina->disciplina.codDisciplina))
          printf("Erro ao cadastrar matricula\n");
      }

      else
        printf("Nenhum aluno ou curso cadastrado!\n");
      break;
    case 5:
      if (alunos && cursos && alunos->aluno.nodeMatricula)
      {
        printf("[DUBUG] curso escolhido vugo primeiro: %d\n", cursos->curso.codigo);
        printf("[DUBUG] disciplina escolhida vugo primeiro: %d\n", alunos->aluno.nodeMatricula->codDisciplina);

        if (!cadastrarNotas(
                alunos,
                (rand() % alunos->aluno.nodeMatricula->codDisciplina),
                (rand() % cursos->curso.quantidadeDePeriodo + 1)))
          printf("Erro ao cadastrar nota\n");
      }
      else
        printf("Nenhum aluno ou curso cadastrado, ou aluno não matriculado em nenhuma disciplina!\n");
      break;
    case 6:
      if (cursos)
        MostrarTodosOsCursosDoCampus(cursos);
      else
        printf("Nenhum curso cadastrado!\n");
      break;
    case 7:
      if (cursos && alunos)
      {
        printf("[DUBUG] curso escolhido vugo primeiro: %d\n", cursos->curso.codigo);
        mostrarTodosOsAlunosDeUmCurso(cursos, alunos);
      }
      else
        printf("Nenhum curso ou aluno cadastrado!\n");
      break;

    case 8:
      if (cursos)
      {
        printf("[DUBUG] curso escolhido vugo primeiro: %d\n", cursos->curso.codigo);
        mostrarTodasAsDisciplinasDeUmCurso(cursos);
      }
      else
        printf("Nenhum curso cadastrado!\n");
      break;
    case 9:
      if (cursos && cursos->curso.nodeDisciplina)
      {
        int periodo = cursos->curso.nodeDisciplina->disciplina.periodo;

        printf("[DUBUG] curso escolhido vugo primeiro [id]: %d\n", cursos->curso.codigo);
        printf("[DEBUG] periodo escolhido vugo primeiro: %d\n", periodo);
        mostrarDisciplinasDeUmPeriodoDeUmCurso(cursos, periodo);
      }
      else
        printf("Nenhum curso cadastrado, ou curso sem disciplinas!\n");
      break;
    case 10:
      if (alunos && cursos && alunos->aluno.nodeMatricula && cursos->curso.nodeDisciplina)
      {
        printf("[DUBUG] aluno escolhido vugo primeiro [id]: %d\n", alunos->aluno.matricula);
        mostrarDisciplinasDeUmAluno(alunos, cursos);
      }
      else
        printf("Nenhum curso ou aluno cadastrado, ou curso sem disciplinas, ou aluno não matriculado em nenhuma disciplina!\n");
      break;
    }
    printf("--------------------------------------------------------------\n");
  }
}
#else
void initMenu(ListAluno *alunos, NodeCurso *cursos)
{
  (void)alunos;
  int opcao = 0;
  int codigoDoCurso = 0;
  int periodo = 0;

  while (opcao != 12)
  {
    menu(&opcao);
    NodeCurso *cursoAtual = NULL;

    switch (opcao)
    {
    case 1:
      cadastrarCursos(&cursos);
      break;

    case 2:

      isCursoValido(&codigoDoCurso, cursos, &cursoAtual);

      isPeriodoValido(&periodo, cursos->curso.quantidadeDePeriodo);

      cadastrarDisciplinas(cursoAtual, periodo);
      break;

    default:
      printf("Opção inválida!\n");
      break;
    }
  }
}
#endif