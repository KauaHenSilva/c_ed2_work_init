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
void cadastrarMatriculas(ListAluno *aluno, NodeDisciplina *raizDisciplina);

// - Permitir a remoção de uma disciplina da árvore de matrícula de um determinado aluno.
void removerDisciplinaDaArvoreDeMatricula(NodeMatricula **matricula, int codDisciplina);

NodeMatricula* removerMatricula(NodeMatricula *raiz, int codDisciplina);