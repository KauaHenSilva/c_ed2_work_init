#pragma once

#include "../structs/struct_curso.h"
#include "../structs/struct_aluno.h"

void isPeriodoValido(int *periodo, int quantidadeDePeriodo);
void isCursoValido(int *codigoDoCurso, NodeCurso *cursos, NodeCurso **atual);
void isAlunoValido(int *matricula, ListAluno *alunos, ListAluno **atual);