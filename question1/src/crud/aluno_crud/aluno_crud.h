#pragma once

#include "../../structs/struct_aluno.h"
#include "../../structs/struct_curso.h"

// Auxs

/**
 * @brief Libera recursivamente uma lista encadeada de alunos.
 *
 * Esta função recebe um ponteiro para o início de uma lista encadeada de alunos
 * e libera recursivamente cada nó da lista. Ela garante que toda a memória
 * alocada para a lista seja devidamente desalocada.
 *
 * @param alunos Ponteiro para o início da lista encadeada de alunos.
 */
void freeAlunosList(ListAluno *alunos);

/**
 * @brief Exibe todos os alunos na lista.
 *
 * Esta função percorre recursivamente a lista de alunos e exibe cada aluno.
 *
 * @param alunos Ponteiro para a lista de alunos.
 */
void showAllAlunos(ListAluno *alunos);

// ---------------------------------------------------------------------------------------

/**
 * - Verificar se o código do curso já foi cadastrado na árvore de cursos.
 * 
 * - Permitir o cadastro de um aluno na lista.
 * 
 * @brief Cadastra um novo aluno na lista de alunos.
 *
 * Esta função aloca memória para um novo aluno, preenche os dados do aluno
 * com base nos cursos disponíveis e insere o aluno na lista de alunos.
 *
 * @param alunos Ponteiro para a lista de alunos.
 * @param cursos Ponteiro para a lista de cursos.
 * @return Retorna 1 se o aluno foi cadastrado com sucesso, caso contrário, retorna 0.
 */
int cadastrarAlunos(ListAluno **alunos, int codigoCurso);
