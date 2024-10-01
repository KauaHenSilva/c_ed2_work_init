# Programa de Cadastro e Histórico de Alunos

## Estruturas de Dados

1. **Lista de Alunos**
    - **Matrícula do Aluno**
    - **Nome do Aluno**
    - **Código do Curso**
    - **Árvore de Notas**
    - **Árvore de Matrícula**
    - **Ordem:** Alfabética por Nome do Aluno

2. **Árvore de Curso**
    - **Código do Curso**
    - **Nome do Curso**
    - **Quantidade de Períodos**
    - **Árvore de Disciplinas**
    - **Ordem:** Código do Curso

3. **Árvore de Disciplinas**
    - **Código da Disciplina**
    - **Nome da Disciplina**
    - **Período**
    - **Carga Horária**
    - **Ordem:** Código da Disciplina

4. **Árvore de Notas**
    - **Código da Disciplina**
    - **Semestre Cursado**
    - **Nota Final Obtida pelo Aluno**
    - **Ordem:** Código da Disciplina

5. **Árvore de Matrícula**
    - **Código da Disciplina**
    - **Ordem:** Código da Disciplina

## Funcionalidades

1. **Cadastrar Alunos**
    - Permitir o cadastro de um aluno na lista.
    - Verificar se o código do curso já foi cadastrado na árvore de cursos.

2. **Cadastrar Cursos**
    - Permitir o cadastro de um curso na árvore de curso.
    - Não é necessário cadastrar disciplinas no momento do cadastro do curso.

3. **Cadastrar Disciplinas**
    - Permitir o cadastro de disciplinas em uma árvore de disciplinas de um curso.
    - O curso deve estar cadastrado.
    - O período da disciplina deve estar entre 1 e a quantidade máxima de períodos do curso.
    - A carga horária deve ser múltiplo de 15, variando entre 30 e 90.

4. **Cadastrar Matrículas**
    - Permitir o cadastro de uma matrícula.
    - A matrícula deve ser organizada e conter somente um código de disciplina do curso do aluno.

5. **Cadastrar Notas**
    - Permitir o cadastro de notas somente para disciplinas na árvore de matrícula.
    - Após o cadastro da nota, a disciplina deve ser removida da árvore de matrícula e adicionada à árvore de notas.

6. **Mostrar Todos os Alunos de um Curso**
    - Listar todos os alunos de um determinado curso.

7. **Mostrar Todos os Cursos do Campus**
    - Listar todos os cursos cadastrados no campus.

8. **Mostrar Todas as Disciplinas de um Curso**
    - Listar todas as disciplinas de um determinado curso.

9. **Mostrar Disciplinas de um Período de um Curso**
    - Listar todas as disciplinas de um determinado período de um curso.

10. **Mostrar Disciplinas de um Aluno**
    - Listar todas as disciplinas nas quais um determinado aluno está matriculado.

11. **Mostrar Notas de um Aluno por Período**
    - Listar todas as notas de disciplinas de um determinado período para um determinado aluno.

12. **Mostrar Nota de uma Disciplina**
    - Mostrar a nota de uma disciplina para um determinado aluno, incluindo o período e a carga horária da disciplina.

13. **Remover Disciplina de um Curso**
    - Permitir a remoção de uma disciplina de um curso, desde que nenhum aluno esteja matriculado nela.

14. **Remover Disciplina da Árvore de Matrícula**
    - Permitir a remoção de uma disciplina da árvore de matrícula de um determinado aluno.

15. **Mostrar Histórico de um Aluno**
    - Mostrar o histórico de um determinado aluno, incluindo o nome do curso, as disciplinas e suas respectivas notas organizadas pelo período.
