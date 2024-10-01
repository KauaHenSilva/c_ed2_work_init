#pragma once

#include "../../arvoreBB/arvore_bb.h"
#include "../../structs/struct_aluno.h"

// auxs

void showMatricula(Info info);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de uma matrícula.
// - A matrícula deve ser organizada e conter somente um código de disciplina do curso do aluno.
int cadastrarMatriculas(ListAluno *aluno, int idDisciplina);
