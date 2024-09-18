#pragma once

#include "../../structs/struct_matricula.h"
#include "../../structs/struct_disciplina.h"
#include "../../structs/struct_nota.h"
#include "../../structs/struct_aluno.h"

void showAllNotas(NodeNota *raiz);

// - Permitir o cadastro de notas somente para disciplinas na árvore de matrícula.
// - Após o cadastro da nota, a disciplina deve ser removida da árvore de matrícula e adicionada à árvore de notas.
void cadastrarNotas(ListAluno *aluno);
