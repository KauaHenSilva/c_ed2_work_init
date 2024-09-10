#pragma once

// -**Ordem : **Código da Disciplina
typedef struct stNodeDisciplina
{
  int codDisciplina;
  char *nomeDaDisciplina;
  int periodo;
  int cargaHoraria;

  struct stNodeDisciplina *esq;
  struct stNodeDisciplina *dir;
} NodeDisciplina;
