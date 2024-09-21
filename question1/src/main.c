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

  printf("Mostrar todas as notas de um aluno de um periodo:\n");

  printf(" alunos periodo:\n");
  ListAluno *aluno;
  int MatAluno;

  int periodo;
  printf("Informe a matricula do aluno: \n");
  scanf("%d", &MatAluno);
  aluno = buscarAluno(alunos, MatAluno);

  printf("Informe o periodo: ");
  scanf("%d", &periodo);

  mostrarNotasDeUmAlunoPorPeriodo(alunos->aluno.nodeNota, periodo);


  //imprimir todas as notas de um aluno em uma disciplina
  //NodeNota *buscarNota(NodeNota *raiz, int codDisciplina)


  NodeCurso *curso;
  NodeDisciplina *disciplina;

  printf("Remover disciplina de um aluno:\n");

  
  int codDisciplina;

  printf("Informe a matricula do aluno: \n");
  scanf("%d", &MatAluno);
  aluno = buscarAluno(alunos, MatAluno);
  if (aluno != NULL)
  {
    printf("Informe o codigo da disciplina: \n");
    scanf("%d", &codDisciplina);

    alunos->aluno.nodeMatricula = removerMatricula(alunos->aluno.nodeMatricula, codDisciplina);
    printf("Disciplina removida com sucesso.\n");
  }

  int cadastro = cadastrarNotas(alunos, codDisciplina);
  if (cadastro == 0)
  {
    showAllAlunos(alunos);
  }
  

  showAllAlunos(alunos);

  printf("Remover disciplinas de um curso:\n");

  int codCurso;

  showAllCurso(cursos);

  printf("Digite o codigo do curso: ");
  scanf("%d", &codCurso);
  curso = buscarCurso(cursos, codCurso);

  printf("Digite o codigo da disciplina: ");
  scanf("%d", &codDisciplina);
  disciplina = buscarDisciplina(cursos->curso.nodeDisciplina, codDisciplina);
  int encontrou = VerificarAlunosMatriculados(alunos, codDisciplina);
  if (encontrou == 0)
  {

    if (disciplina)
    {
      curso->curso.nodeDisciplina = removerDisciplinaCurso(cursos->curso.nodeDisciplina, codDisciplina);
      printf("Disciplina removida com sucesso.\n");
    }
  }

  showAllCurso(cursos);

  freeAlunosList(alunos);
  freeNodeCursos(cursos);
  return 0;
}