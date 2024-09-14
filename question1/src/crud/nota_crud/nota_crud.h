#pragma once

#include <struct_matricula.h>
#include <struct_disciplina.h>
#include <struct_nota.h>
#include <struct_aluno.h>

void showAllNotas(NodeNota *raiz);

// - Permitir o cadastro de notas somente para disciplinas na árvore de matrícula.
// - Após o cadastro da nota, a disciplina deve ser removida da árvore de matrícula e adicionada à árvore de notas.
void cadastrarNotas(ListAluno *aluno);
