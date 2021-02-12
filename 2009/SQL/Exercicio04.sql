--1) Retorne o nome dos cursos do instituto de 'Ciencias Exatas'.

SELECT C.NOME_CURSO 
FROM CURSO C
INNER JOIN INSTITUTO I 
ON I.COD_INSTITUTO = C.COD_INSTITUTO
WHERE I.NOME_INSTITUTO LIKE 'Ciencias Exatas';


--2) Retorne a idade máxima e a idade mínima dos alunos do curso de 'Ciencia da Computacao'.

SELECT MIN(IDADE) "IDADE MINIMA", MAX(IDADE) "IDADE MAXIMA" 
FROM ALUNO A
INNER JOIN CURSO C
ON A.COD_CURSO = C.COD_CURSO
WHERE C.NOME_CURSO LIKE 'Ciencia da Computacao';

--3) Retorne o nome de cada curso e a idade média dos alunos de cada um desses cursos, em ordem
--crescente do nome do curso.

SELECT C.NOME_CURSO, AVG(IDADE) "MEDIA IDADE" 
FROM ALUNO A
INNER JOIN CURSO C
ON A.COD_CURSO = C.COD_CURSO
GROUP BY C.NOME_CURSO
ORDER BY C.NOME_CURSO;

--4) Retorne o nome das disciplinas pertencentes ao instituto de 'Ciencias Exatas'.

SELECT D.NOME_DISCIPLINA
FROM INSTITUTO I
INNER JOIN CURSO C
ON C.COD_INSTITUTO = I.COD_INSTITUTO
INNER JOIN DISCIPLINA D
ON D.COD_CURSO = C.COD_CURSO
WHERE I.NOME_INSTITUTO LIKE 'Ciencias Exatas';

--5) Retorne o nome das disciplinas que o aluno 'Rodrigo' cursou.

SELECT D.NOME_DISCIPLINA
FROM ALUNO A
INNER JOIN ALUNO_DISC AD
ON AD.MATRICULA = A.MATRICULA
INNER JOIN DISCIPLINA D
ON D.COD_DISCIPLINA = AD.COD_DISCIPLINA
WHERE A.NOME_ALUNO LIKE 'Rodrigo';

--6) Retorne o nome de cada professor e a quantidade de disciplinas que cada um ministra, mas somente para
--os professores que ministram mais que uma disciplina.

SELECT P.NOME_PROFESSOR, COUNT(PD.COD_DISCIPLINA) "QTD DISCIPLINA"
FROM PROFESSOR P
INNER JOIN PROF_DISC PD
ON PD.COD_PROFESSOR = P.COD_PROFESSOR
GROUP BY P.NOME_PROFESSOR
HAVING COUNT(PD.COD_DISCIPLINA) > 1;

--7) Retorne o nome dos alunos que cursaram as disciplinas de Banco de Dados I ou Banco de Dados II.

SELECT A.NOME_ALUNO "NOME ALUNO"
FROM ALUNO A
INNER JOIN ALUNO_DISC AD
ON AD.MATRICULA = A.MATRICULA
INNER JOIN DISCIPLINA D
ON D.COD_DISCIPLINA = AD.COD_DISCIPLINA
WHERE D.NOME_DISCIPLINA LIKE 'Banco de Dados I' OR
D.NOME_DISCIPLINA LIKE 'Banco de Dados II';


--8) Retorne o dia da semana que o professor João ministra a disciplina de Engenharia de Software II.

SELECT PD.DIA_SEMANA
FROM PROFESSOR P
INNER JOIN PROF_DISC PD
ON PD.COD_PROFESSOR = P.COD_PROFESSOR
INNER JOIN DISCIPLINA D
ON D.COD_DISCIPLINA = PD.COD_DISCIPLINA
WHERE D.NOME_DISCIPLINA LIKE 'Engenharia de Software II'
AND P.NOME_PROFESSOR LIKE 'Joao';

--9) Retorne o nome dos professores que orientam alunos e, para cada professor orientador, a quantidade de
--alunos que eles orienta.

SELECT P.NOME_PROFESSOR, COUNT(A.MATRICULA) "QTD ALUNOS"
FROM PROFESSOR P
INNER JOIN ALUNO A
ON A.COD_PROFESSOR_ORIENTADOR = P.COD_PROFESSOR
GROUP BY P.NOME_PROFESSOR;


--10) Retorne o nome das disciplinas, o nome do professor de cada uma delas e o dia da semana que cada uma
--é ministrada.


SELECT D.NOME_DISCIPLINA, P.NOME_PROFESSOR, PD.DIA_SEMANA
FROM DISCIPLINA D
INNER JOIN PROF_DISC PD
ON PD.COD_DISCIPLINA = D.COD_DISCIPLINA
INNER JOIN PROFESSOR P
ON P.COD_PROFESSOR = PD.COD_PROFESSOR
ORDER BY P.NOME_PROFESSOR, D.NOME_DISCIPLINA;
