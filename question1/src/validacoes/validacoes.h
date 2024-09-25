#pragma once

#include "../structs/struct_curso.h"
#include "../structs/struct_aluno.h"


int getPeriodoValido(int *periodo, int quantidadeDePeriodo);
int getCursoValido(int *codigoDoCurso, NodeCurso *cursos, NodeCurso **atual);
int getAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual);
int getDisciplinaValida(int *codigoDoCurso, NodeDisciplina *nodeDisciplina, NodeDisciplina **disciplinaAtual);
int getMatriculaValida(int *codigoDoCurso, NodeMatricula *nodeMatricula, NodeMatricula **matriculaAtual);
int boolAlunoInDisciplina(ListAluno *aluno, int disciplina);
