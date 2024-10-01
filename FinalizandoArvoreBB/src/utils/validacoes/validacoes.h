#pragma once

#include "../../structs/info/struct_curso.h"
#include "../../structs/struct_aluno.h"

typedef enum
{
    PRIMEIRO_ARGUMENTO_MENOR = 1,
    PRIMEIRO_ARGUMENTO_MAIOR = -1,
    PRIMEIRO_ARGUMENTO_IGUAL = 0
} NomeCmp;

NomeCmp myStrCmp(char *texto1, char *texto2);

int getPeriodoValido(int *periodo, int quantidadeDePeriodo);
int getCursoValido(int *codigoDoCurso, Arvore *raizCursos, Arvore **raizAtual);
int getAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual);
int boolAlunoInDisciplina(ListAluno *aluno, int disciplina);

int getDisciplinaValida(
    int *codigoDoCurso, Arvore *raizDisciplina, Arvore **raizDisciplinaAtual);
int getMatriculaValida(
    int *codigoDoCurso, Arvore *raizMatricula, Arvore **raizMatriculaAtual);