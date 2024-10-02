#pragma once

#include "../../structs/arvore_bb.h"

// Auxs

void showCurso(Info info);
void freeNodeCurso(Info info);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de um curso na árvore de curso.
// - Não é necessário cadastrar disciplinas no momento do cadastro do curso.
int cadastrarCursos(Arvore **arvoreCurso);
