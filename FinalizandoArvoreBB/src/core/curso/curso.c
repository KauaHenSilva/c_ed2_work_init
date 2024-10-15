#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curso.h"
#include "../disciplina/disciplina.h"
#include "../aluno/aluno.h"

#include "../../utils/get/get.h"

#include "../../arvoreBB/arvore_bb.h"

/**
 * @brief Libera a memória alocada para um nó de curso e suas disciplinas associadas.
 *
 * Esta função libera a memória associada a um curso, incluindo o nome do curso
 * e a árvore de disciplinas vinculada a ele. Finalmente, libera a memória do
 * próprio nó de curso.
 *
 * @param node Ponteiro para o nó de curso a ser liberado.
 */
void freeNodeCurso(Info info)
{
  if (info.curso.nomeDoCurso)
    free(info.curso.nomeDoCurso);

  freeTree(info.curso.arvoreDisciplinas, NULL);
}

/**
 * @brief Preenche os dados de um curso com base nas entradas do usuário.
 *
 * Solicita ao usuário o código do curso, a quantidade de períodos e o nome do
 * curso, preenchendo os campos correspondentes na estrutura `NodeCurso`.
 * Se o usuário inserir dados inválidos ou optar por sair, a função retorna uma
 * falha.
 *
 * @param node Ponteiro para o curso a ser preenchido.
 * @return Retorna 1 se o preenchimento foi bem-sucedido, 0 caso contrário.
 */
static void prencherCurso(Curso *curso)
{
  getInt(&curso->codigo, "Digite o codigo do curso: ");
  getInt(&curso->quantidadeDePeriodo, "Digite a quantidade de periodo do curso: ");
  getString(&curso->nomeDoCurso, "Digite o nome do curso: ");
}

/**
 * @brief Exibe as informações de um curso.
 *
 * Mostra o código, o nome e todas as disciplinas associadas a um curso.
 * Usa a função `showAllDisciplina` para exibir a árvore de disciplinas do curso.
 *
 * @param curso Ponteiro para o curso a ser exibido.
 */
void showCurso(Info info)
{
  printf("Curso: \n");
  printf("\tid: %d\n", info.curso.codigo);
  printf("\tNome: %s", info.curso.nomeDoCurso);
  printf("\tQuantidade de periodo: %d\n", info.curso.quantidadeDePeriodo);
  showTree(info.curso.arvoreDisciplinas, showDisciplina);
}

/**
 * @brief Cadastra um novo curso e o insere na árvore de cursos.
 *
 * A função aloca memória para um novo curso, preenche suas informações
 * chamando `prencherCurso` e o insere na árvore binária de cursos através de
 * `inserctionCurso`. Se houver falha durante o preenchimento do curso, a memória
 * alocada é liberada.
 *
 * @param nodeCurso Ponteiro para o ponteiro da árvore de cursos.
 * @return Retorna 1 se o curso foi cadastrado com sucesso, 0 caso contrário.
 */
int cadastrarCursos(Arvore **arvoreCurso)
{
  int confirm = 1;

  Arvore *newTree;
  alocTree(&newTree);
  prencherCurso(&newTree->info.curso);

  if (!insertTree(arvoreCurso, newTree))
  {
    freeTree(newTree, freeNodeCurso);
    confirm = 0;
  }

  return confirm;
}
