#pragma once

#include "../../structs/struct_aluno.h"
#include "../../structs/info/struct_curso.h"

// Auxs

void freeAlunosList(ListAluno *alunos);
void showAllAlunos(ListAluno *alunos);
void showAluno(ListAluno *aluno);
int searchAluno(ListAluno *aluno, int code, ListAluno **result);
int inserctionAluno(ListAluno **AlunoRaiz, Aluno newValue);

// ---------------------------------------------------------------------------------------

/**
 * - Verificar se o código do curso já foi cadastrado na árvore de cursos.
 * - Permitir o cadastro de um aluno na lista.
 *
 * @brief Cadastra um novo aluno na lista de alunos.
 *
 * Esta função aloca memória para um novo aluno, preenche os dados do aluno
 * com base nos cursos disponíveis e insere o aluno na lista de alunos.
 *
 * @param alunos Ponteiro para a lista de alunos.
 * @param cursos Ponteiro para a lista de cursos.
 * @return Retorna 1 se o aluno foi cadastrado com sucesso, caso contrário,
 * retorna 0.
 */
int cadastrarAlunos(ListAluno **alunos, Arvore *arvoreCursos);
