#pragma once

#include "../../structs/struct_curso.h"

// Auxs

void freeNodeCursos(NodeCurso *node);
void showAllCurso(NodeCurso *curso);
void isCurseOpen(NodeCurso *curso, int id, int *bool);
void search_course(NodeCurso *raiz, int code, NodeCurso *result);
int inserctionCurso(NodeCurso **raiz, NodeCurso *node);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de um curso na árvore de curso.
// - Não é necessário cadastrar disciplinas no momento do cadastro do curso.
int cadastrarCursos(NodeCurso **nodeCurso);

NodeCurso *buscarCurso(NodeCurso *curso, int codigo);

// - Permitir a remoção de uma disciplina de um curso, desde que nenhum aluno esteja matriculado nela.
