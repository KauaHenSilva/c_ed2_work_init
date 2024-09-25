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
  printf("0 - Sair\n");
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
  printf("12 - Mostrar Nota de uma Disciplina [falta implementar]\n");
  printf("13 - Remover Disciplina de um Curso\n");
  printf("14 - Remover Disciplina da Árvore de Matrícula\n");
  printf("15 - Mostrar Histórico de um Aluno [falta implementar]\n");
  printf("Digite a opção desejada: ");
  scanf("%d", opcao);
  printf("--------------------------------------------------------------\n");
}

void initMenu(ListAluno *alunos, NodeCurso *cursos)
{
  (void)alunos;
  int opcao = -1;

  while (opcao != 0)
  {
    menu(&opcao);

    NodeCurso *cursoAtual = NULL;
    NodeDisciplina *disciplinaAtual = NULL;
    NodeMatricula *matriculaAtual = NULL;
    ListAluno *alunoAtual = NULL;

    int codCurso = 0;
    int codDisciplina = 0;
    int codMatricula = 0;
    int codAluno = 0;
    int periodo = 0;

    switch (opcao)
    {
    case 0:
      break;

    case 1:
      if (!cadastrarCursos(&cursos))
        printf("Erro ao cadastrar curso\n");
      break;

    case 2:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!getPeriodoValido(&periodo, cursoAtual->curso.quantidadeDePeriodo))
        printf("Erro ao achar periodo valido\n");
      else if (!cadastrarDisciplinas(cursoAtual, periodo))
        printf("Erro ao cadastrar disciplina\n");
      break;

    case 3:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!cadastrarAlunos(&alunos, cursoAtual->curso.codigo))
        printf("Erro ao cadastrar aluno\n");
      break;

    case 4:
      if (!alunos || !cursos)
        printf("Nenhum aluno ou curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!cursoAtual->curso.nodeDisciplina)
        printf("Curso sem disciplinas\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Erro ao achar aluno valido\n");
      else if (!getDisciplinaValida(&codDisciplina, cursoAtual->curso.nodeDisciplina, &disciplinaAtual))
        printf("Erro ao achar disciplina valida\n");
      else if (!cadastrarMatriculas(alunoAtual, disciplinaAtual->disciplina.codDisciplina))
        printf("Erro ao cadastrar matricula\n");
      break;

    case 5:

      if (!alunos || !cursos)
        printf("Nenhum aluno ou curso cadastrado.\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!cursoAtual->curso.nodeDisciplina)
        printf("Curso sem disciplinas\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Erro ao achar aluno valido\n");
      else if (!getDisciplinaValida(&codDisciplina, cursoAtual->curso.nodeDisciplina, &disciplinaAtual))
        printf("Erro ao achar disciplina valida\n");
      else if (!cadastrarNotas(
                   alunos,
                   codDisciplina,
                   cursoAtual->curso.nodeDisciplina->disciplina.periodo))
        printf("Erro ao cadastrar nota\n");
      break;

    case 6:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else
        MostrarTodosOsCursosDoCampus(cursos);
      break;

    case 7:
      if (!cursos || !alunos)
        printf("Nenhum curso ou aluno cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else
        mostrarTodosOsAlunosDeUmCurso(cursoAtual, alunos);
      break;

    case 8:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else
        mostrarTodasAsDisciplinasDeUmCurso(cursoAtual);
      break;

    case 9:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!getPeriodoValido(&periodo, cursoAtual->curso.quantidadeDePeriodo))
        printf("Erro ao achar periodo valido\n");
      else
        mostrarDisciplinasDeUmPeriodoDeUmCurso(cursoAtual, periodo);
      break;

    case 10:
      if (!alunos && !cursos)
        printf("Nenhum curso ou aluno cadastrado!\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("sem aluno valido\n");
      else if (!alunoAtual->aluno.nodeMatricula)
        printf("Aluno sem matriculas\n");
      else if (!(cursoAtual = buscarCurso(cursos, alunoAtual->aluno.codigoDoCurso)))
        printf("sem curso valido\n");
      else if (!cursoAtual->curso.nodeDisciplina)
        printf("Curso sem disciplinas\n");
      else
        mostrarDisciplinasDeUmAluno(alunoAtual->aluno.nodeMatricula, cursoAtual->curso.nodeDisciplina);
      break;

    case 11:
      if (!alunos || !cursos)
        printf("Nenhum aluno ou curso cadastrado\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("sem aluno valido\n");
      else if (!alunoAtual->aluno.nodeNota)
        printf("Aluno sem notas\n");
      else if (!(cursoAtual = buscarCurso(cursos, alunoAtual->aluno.codigoDoCurso)))
        printf("sem curso valido\n");
      else if (!getPeriodoValido(&periodo, cursoAtual->curso.quantidadeDePeriodo))
        printf("sem periodo valido\n");
      else
        mostrarNotasDeUmAlunoPorPeriodo(alunoAtual->aluno.nodeNota, periodo);
      break;

    case 12:
      // Mostrar a nota de uma disciplina de um determinado aluno,
      // mostrando o período e a carga horária da disciplina.
      if (!cursos || !alunos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("sem curso valido\n");
      else if (!cursoAtual->curso.nodeDisciplina)
        printf("Curso sem disciplinas\n");
      else if (!getDisciplinaValida(&codDisciplina, cursoAtual->curso.nodeDisciplina, &disciplinaAtual))
        printf("Erro ao achar disciplina valida\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("sem aluno valido\n");
      else if (!alunoAtual->aluno.nodeNota)
        printf("Aluno sem notas\n");
      else
        mostrarNotaDeUmaDisciplina(alunoAtual->aluno.nodeNota, disciplinaAtual);
      break;

    case 13:
      if (!cursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, cursos, &cursoAtual))
        printf("Erro ao achar curso valido\n");
      else if (!cursoAtual->curso.nodeDisciplina)
        printf("Curso sem disciplinas\n");
      else if (!getDisciplinaValida(&codDisciplina, cursoAtual->curso.nodeDisciplina, &disciplinaAtual))
        printf("Erro ao achar disciplina valida\n");
      else if (!removerDisciplina(&cursoAtual->curso.nodeDisciplina, codDisciplina))
        printf("Falta retornar um valor que diz que a disciplina foi removida\n");
      break;

    case 14:
      if (!alunos)
        printf("Nenhum aluno cadastrado!\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Erro ao achar aluno valido\n");
      else if (!alunoAtual->aluno.nodeMatricula)
        printf("Aluno sem matriculas\n");
      else if (!getMatriculaValida(&codMatricula, alunoAtual->aluno.nodeMatricula, &matriculaAtual))
        printf("Erro ao achar matricula valida\n");
      else if (!removerMatricula(&alunoAtual->aluno.nodeMatricula, codMatricula))
        printf("Falta retornar um valor que diz que a disciplina foi removida\n");
      break;

    case 15:
      if (!alunos || !cursos)
        printf("Nenhum aluno ou curso cadastrado\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("sem aluno valido\n");
      else
        imprimirHistoricoAluno(alunoAtual, cursos);
      break;

    default:
      printf("Opção inválida!\n");
      break;
    }
    printf("--------------------------------------------------------------\n");
  }
}