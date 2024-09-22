#pragma once

#include "../../structs/struct_curso.h"
#include "../../structs/struct_disciplina.h"

// Auxs

void freeNodeDisciplinas(NodeDisciplina *raiz);
void showAllDisciplina(NodeDisciplina *disciplina);
void buscarDisciplina(NodeDisciplina *raiz, int codigo, NodeDisciplina **result);
void showDisciplina(NodeDisciplina *disciplina);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de disciplinas em uma árvore de disciplinas de um curso.
// - O curso deve estar cadastrado.
// - O período da disciplina deve estar entre 1 e a quantidade máxima de períodos do curso.
// - A carga horária deve ser múltiplo de 15, variando entre 30 e 90.
int cadastrarDisciplinas(NodeCurso *curso, int periodo);

int removerDisciplina(NodeDisciplina **raiz, int codDisciplina);

