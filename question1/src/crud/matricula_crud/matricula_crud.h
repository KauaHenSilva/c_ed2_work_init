#pragma once

#include <struct_matricula.h>
#include <struct_aluno.h>
#include <struct_disciplina.h>

// auxs

void freeNodeMatriculas(NodeMatricula *raiz);
void showAllMatriculas(NodeMatricula *raiz);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de uma matrícula.
// - A matrícula deve ser organizada e conter somente um código de disciplina do curso do aluno.
void cadastrarMatriculas(ListAluno *aluno, NodeDisciplina *raizDisciplina);

// - Permitir a remoção de uma disciplina da árvore de matrícula de um determinado aluno.
void removerDisciplinaDaArvoreDeMatricula();