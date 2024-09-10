#pragma once

#include <struct_disciplina.h>
#include <struct_curso.h>

// Auxs

NodeDisciplina *alocDisciplina();
void freeNodeDisciplina(NodeDisciplina *node);
void freeNodeDisciplinas(NodeDisciplina *node);
int prencherDisciplina(NodeDisciplina *node);
void showAllDisciplina(NodeDisciplina *disciplina);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de disciplinas em uma árvore de disciplinas de um curso.
// - O curso deve estar cadastrado.
// - O período da disciplina deve estar entre 1 e a quantidade máxima de períodos do curso.
// - A carga horária deve ser múltiplo de 15, variando entre 30 e 90.
void cadastrarDisciplinas(NodeCurso *curso);
