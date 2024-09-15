#pragma once

// - Ordem: Código da Disciplina
// - Free: node, nomeDaDisciplina.
typedef struct stNodeDisciplina
{
  int codDisciplina;
  char *nomeDaDisciplina;
  int periodo;
  int cargaHoraria;

  struct stNodeDisciplina *esq;
  struct stNodeDisciplina *dir;
} NodeDisciplina;
