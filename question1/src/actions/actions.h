#pragma once

#include "../structs/struct_curso.h"
#include "../structs/struct_aluno.h"

// - Listar todos os alunos de um determinado curso.
void mostrarTodosOsAlunosDeUmCurso(NodeCurso *curso, ListAluno *alunos);

// - Listar todos os cursos cadastrados no campus.
void MostrarTodosOsCursosDoCampus(NodeCurso *cursos);

// - Listar todas as disciplinas de um determinado curso.
void mostrarTodasAsDisciplinasDeUmCurso(NodeCurso *curso);

// - Listar todas as disciplinas de um determinado período de um curso.
void mostrarDisciplinasDeUmPeriodoDeUmCurso(NodeCurso *curso, int periodo);

// - Listar todas as disciplinas nas quais um determinado aluno está matriculado.
void mostrarDisciplinasDeUmAluno(NodeMatricula *matriculasAluno, NodeDisciplina *disciplina);

// - Listar todas as notas de disciplinas de um determinado período para um determinado aluno.
void mostrarNotasDeUmAlunoPorPeriodo(NodeNota *raiz, int periodo);

// - Mostrar a nota de uma disciplina para um determinado aluno, incluindo o período e a carga horária da disciplina.
void mostrarNotaDeUmaDisciplina(NodeNota *raiz, NodeDisciplina *disciplina);

// - Mostrar o histórico de um determinado aluno, incluindo o nome do curso, as disciplinas e suas respectivas notas organizadas pelo período.
void imprimirHistoricoAluno(ListAluno *aluno, NodeCurso *curso);
