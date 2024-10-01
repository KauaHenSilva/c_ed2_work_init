#pragma once

#include "../../structs/info/struct_curso.h"
#include "../../structs/struct_aluno.h"

// - Listar todos os alunos de um determinado curso.
void mostrarTodosOsAlunosDeUmCurso(Arvore *arvoreCurso, ListAluno *alunos);

// - Listar todos os cursos cadastrados no campus.
void MostrarTodosOsCursosDoCampus(Arvore *arvoreCurso);

// - Listar todas as disciplinas de um determinado curso.
void mostrarTodasAsDisciplinasDeUmCurso(Arvore *arvoreCurso);

// - Listar todas as disciplinas de um determinado período de um curso.
void mostrarDisciplinasDeUmPeriodoDeUmCurso(Arvore *arvoreCurso, int periodo);

// - Listar todas as disciplinas nas quais um determinado aluno está matriculado.
void mostrarDisciplinasDeUmAluno(Arvore *raizMatriculasAluno, Arvore *raizDisciplina);

// - Listar todas as notas de disciplinas de um determinado período para um determinado aluno.
void mostrarNotasDeUmAlunoPorPeriodo(Arvore *raizNota, int periodo);

// - Mostrar a nota de uma disciplina para um determinado aluno, incluindo o período e a carga horária da disciplina.
void mostrarNotaDeUmaDisciplina(Arvore *raizDisciplinaAtual, Arvore *raizNota);

// - Mostrar o histórico de um determinado aluno, incluindo o nome do curso, as disciplinas e suas respectivas notas organizadas pelo período.
void imprimirHistoricoAluno(ListAluno *aluno, Arvore *raizCursos);
