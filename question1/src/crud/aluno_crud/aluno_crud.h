#pragma once

#include <struct_aluno.h>
#include <struct_curso.h>

// Auxs

ListAluno *alocAluno();
int prencherAluno(ListAluno *aluno, NodeCurso *cursos);
void freeAlunosList(ListAluno *alunos);
void showAllAlunos(ListAluno *alunos);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de um aluno na lista.
// - Verificar se o código do curso já foi cadastrado na árvore de cursos.
int cadastrarAlunos(ListAluno **aluno, NodeCurso *cursos);
