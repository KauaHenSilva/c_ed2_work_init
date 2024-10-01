#pragma once

#include "../../arvoreAVL/arvore_avl.h"
#include "../../structs/struct_aluno.h"

void showNota(Info info);

// - Permitir o cadastro de notas somente para disciplinas na árvore de matrícula.
// - Após o cadastro da nota, a disciplina deve ser removida da árvore de matrícula e adicionada à árvore de notas.
int cadastrarNotas(ListAluno *aluno, int codDisciplina, int semestreCursado);
