#pragma once

#include "../structs/arvore_avl.h"

int insertTree(Arvore **raiz, Arvore *new);
int removerNodeArvore(Arvore **raiz, Info remove);
int searchNodeTree(Arvore *raiz, Info info, Arvore **result);
void freeTree(Arvore *raiz, void (*freeInfo)(Info));
void showTree(Arvore *raiz, void (*showInfo)(Info));
void alocTree(Arvore **raiz);