#pragma once

typedef struct Disciplina
{
  int codDisciplina;
  char *nomeDaDisciplina;
  int periodo;
  int cargaHoraria;
} Disciplina;

// - Ordem: Código da Disciplina
// - Free: node, nomeDaDisciplina.
typedef struct stNodeDisciplina
{
  Disciplina disciplina;
  struct stNodeDisciplina *esq;
  struct stNodeDisciplina *dir;
} NodeDisciplina;
