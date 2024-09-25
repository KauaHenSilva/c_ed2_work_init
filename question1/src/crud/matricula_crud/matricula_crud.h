#pragma once

#include "../../structs/struct_matricula.h"
#include "../../structs/struct_aluno.h"
#include "../../structs/struct_disciplina.h"

// auxs

void freeNodeMatriculas(NodeMatricula *raiz);
void showAllMatriculas(NodeMatricula *raiz);
void search_matricula(NodeMatricula *raiz, int code, NodeMatricula **result);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de uma matrícula.
// - A matrícula deve ser organizada e conter somente um código de disciplina do curso do aluno.
int cadastrarMatriculas(ListAluno *aluno, int idDisciplina);

// - Permitir a remoção de uma disciplina da árvore de matrícula de um determinado aluno.

NodeMatricula *buscarMatriculas(NodeMatricula *raiz, int codDisciplina);
int ehFolha(NodeMatricula *raiz);
NodeMatricula *soUmFilho(NodeMatricula *raiz);
NodeMatricula *menorFilho(NodeMatricula *raiz);
int removerMatricula(NodeMatricula **raiz, int codDisciplina);

int VerificarAlunosMatriculados(ListAluno *aluno, int disciplina);
ListAluno *buscarAluno(ListAluno *alunos, int matricula);
