#include "aux.h"
#include "tempos_busca_nota.h"

#include "../crud/aluno_crud/aluno_crud.h"
#include "../crud/nota_crud/nota_crud.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void defNotaTime(NodeNota *notas, int idx, int value)
{
  notas[idx].nota.codDisciplina = value;
  notas[idx].nota.semestreCursado = value;
  notas[idx].nota.notaFinal = value;
  notas[idx].dir = NULL;
  notas[idx].esq = NULL;
}

static void defNotaType(NodeNota *notas, TipoDeOrdenacao type)
{
  int vet[QTDNOTASTESTADOS];

  switch (type)
  {
  case CRESCENTE:
    vetIntCrescente(vet, QTDNOTASTESTADOS);
    break;
  case DECRESCENTE:
    vetIntDecrescente(vet, QTDNOTASTESTADOS);
    break;
  case ALEATORIO:
    vetIntAleatorioSemRepeticao(vet, QTDNOTASTESTADOS);
    break;
  }

  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    defNotaTime(notas, i, vet[i]);
}

static Relatorio tempBuscaNota(ListAluno Aluno, NodeNota *nodeNota, char *titulo)
{
  NodeNota *temp = Aluno.aluno.nodeNota;
  double Tempos[QTDTESTES];

  clock_t inicio, fim;

  for (int i = 0; i < QTDTESTES; i++)
  {
    clock_t tempo = 0;

    for (int x = 0; x < QTDNOTASTESTADOS; x++)
    {

      inicio = clock();
      buscar_nota(temp, nodeNota[x].nota.codDisciplina, NULL);
      fim = clock();

      tempo += (fim - inicio);
    }

    Tempos[i] = ((double)tempo) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f - ", Tempos[i]);
    printf("Titulo: %s", titulo);
  }

  double somaTempo = 0;
  for (int i = 0; i < QTDTESTES; i++)
    somaTempo += Tempos[i];

  Relatorio relatorio;
  relatorio.titulo = titulo;
  relatorio.tempo = somaTempo / QTDTESTES;
  relatorio.quantidadeDeElementos = QTDNOTASTESTADOS;

  return relatorio;
}

static Relatorio *bateriaDeTestes(ListAluno aluno, char **titulo)
{
  NodeNota notasParaBuscar[QTDNOTASTESTADOS];
  Relatorio *relatorio = (Relatorio *)malloc(3 * sizeof(Relatorio));

  defNotaType(notasParaBuscar, CRESCENTE);
  relatorio[0] = tempBuscaNota(aluno, notasParaBuscar, titulo[0]);

  defNotaType(notasParaBuscar, DECRESCENTE);
  relatorio[1] = tempBuscaNota(aluno, notasParaBuscar, titulo[1]);

  defNotaType(notasParaBuscar, ALEATORIO);
  relatorio[2] = tempBuscaNota(aluno, notasParaBuscar, titulo[2]);

  return relatorio;
}

static void defCursoEAluno(ListAluno *aluno, NodeCurso *curso)
{
  curso->curso.codigo = 1;
  curso->curso.nomeDoCurso = "Curso";
  curso->curso.quantidadeDePeriodo = 1;
  curso->curso.nodeDisciplina = NULL;
  curso->dir = NULL;
  curso->esq = NULL;

  aluno->aluno.codigoDoCurso = curso->curso.codigo;
  aluno->aluno.nome = "Aluno";
  aluno->aluno.nodeMatricula = NULL;
  aluno->aluno.nodeNota = NULL;
  aluno->prox = NULL;
}

static void alocRelatorio(Relatorio ***relatorio, int qtd)
{
  *relatorio = (Relatorio **)malloc((size_t)qtd * sizeof(Relatorio *));
}

static void adicionarNotasAoAluno(ListAluno *aluno, NodeNota *notas)
{
  for (int i = 0; i < QTDNOTASTESTADOS; i++)
    inserctionNota(&aluno->aluno.nodeNota, &notas[i]);
}

static void testeComPossibilidadesDeNotas(ListAluno aluno, Relatorio **relatorioBusca)
{
  NodeNota notas[QTDNOTASTESTADOS];

  defNotaType(notas, CRESCENTE);
  adicionarNotasAoAluno(&aluno, notas);
  char *titulosTestes1[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas cressente )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas cressente )\n",
      "tempo de busca de nota aleatório ( Lista de notas cressente )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas cressente )\n",
  };
  relatorioBusca[0] = bateriaDeTestes(aluno, titulosTestes1);

  defNotaType(notas, DECRESCENTE);
  adicionarNotasAoAluno(&aluno, notas);
  char *titulosTestes2[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas decressente )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas decressente )\n",
      "tempo de busca de nota aleatório ( Lista de notas decressente )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas decressente )\n",
  };
  relatorioBusca[1] = bateriaDeTestes(aluno, titulosTestes2);

  defNotaType(notas, ALEATORIO);
  adicionarNotasAoAluno(&aluno, notas);
  char *titulosTestes3[4] = {
      "tempo de busca de nota em ordem crescente ( Lista de notas aleatório )\n",
      "tempo de busca de nota em ordem decrescente ( Lista de notas aleatório )\n",
      "tempo de busca de nota aleatório ( Lista de notas aleatório )\n",
      "tempo de busca de nota aleatório que não se repetem ( Lista de notas aleatório )\n",
  };
  relatorioBusca[2] = bateriaDeTestes(aluno, titulosTestes3);
}

Relatorio **testTempoBuscaNotaDisciplina()
{
  srand((unsigned)time(NULL));

  NodeCurso curso;
  ListAluno aluno;
  Relatorio **relatorioBusca;

  defCursoEAluno(&aluno, &curso);
  alocRelatorio(&relatorioBusca, 3);

  testeComPossibilidadesDeNotas(aluno, relatorioBusca);
  return relatorioBusca;
}
