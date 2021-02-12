
SELECT * FROM FUNCIONARIO;
SELECT * FROM PROJETO;
SELECT * FROM FUNC_PROJ;
SELECT * FROM Departamento;

--1) Obtenha o nome do departamento que o funcionário 'Mario Souza' trabalha.

SELECT D.NOME_DEPTO 
FROM DEPARTAMENTO D 
   JOIN FUNCIONARIO F 
        ON F.COD_DEPTO = D.COD_DEPTO
WHERE F.NOME_FUNC LIKE 'Mario Souza'

--2) Obtenha os nomes dos departamentos, em ordem crescente, que possuem funcionários com
--salário<1500.

SELECT D.NOME_DEPTO 
FROM DEPARTAMENTO D 
   JOIN FUNCIONARIO F 
        ON F.COD_DEPTO = D.COD_DEPTO
WHERE F.SALARIO < 1500
ORDER BY D.NOME_DEPTO DESC;

--3) Obtenha o nome dos funcionários que trabalham no projeto de código 1001.

SELECT F.NOME_FUNC 
FROM FUNC_PROJ FP
  INNER JOIN FUNCIONARIO F
     ON F.COD_FUNC = FP.COD_FUNC
WHERE FP.COD_PROJ = 1001;     

--4) Obtenha o nome dos projetos que a funcionária 'Maria Castro' trabalhou.

SELECT  P.NOME_PROJ
FROM FUNC_PROJ FP
  INNER JOIN FUNCIONARIO F
     ON F.COD_FUNC = FP.COD_FUNC
  INNER JOIN PROJETO P 
     ON P.COD_PROJ = FP.COD_PROJ      
WHERE F.NOME_FUNC LIKE 'Maria Castro';  

--5) Obtenha, sem repetição e em ordem decrescente de salário, o nome e salário dos funcionários que
--trabalharam mais de 100 horas no projeto 'Sistema B'.

SELECT  F.NOME_FUNC, F.SALARIO
FROM FUNC_PROJ FP
  INNER JOIN FUNCIONARIO F
     ON F.COD_FUNC = FP.COD_FUNC
  INNER JOIN PROJETO P 
     ON P.COD_PROJ = FP.COD_PROJ      
WHERE FP.HORAS_TRAB > 100 AND P.NOME_PROJ LIKE 'SistemaB'
ORDER BY F.SALARIO DESC;

--6) Obtenha, sem repetição, o nome e duração dos projetos onde houve a participação dos funcionários do
--departamento de 'Marketing'.

SELECT DISTINCT  P.NOME_PROJ, P.DURACAO
FROM FUNC_PROJ FP
  INNER JOIN FUNCIONARIO F
     ON F.COD_FUNC = FP.COD_FUNC
  INNER JOIN PROJETO P 
     ON P.COD_PROJ = FP.COD_PROJ      
  INNER JOIN DEPARTAMENTO D
     ON D.COD_DEPTO = F.COD_DEPTO      
WHERE D.NOME_DEPTO LIKE 'Marketing';

--7) Obtenha o nome de cada departamento e a quantidade de funcionários de cada um deles.

SELECT D.NOME_DEPTO, COUNT(F.COD_FUNC) "QTD FUNCIONARIO"
FROM DEPARTAMENTO D
     INNER JOIN FUNCIONARIO F
           ON F.COD_DEPTO = D.COD_DEPTO
GROUP BY D.NOME_DEPTO;           

--8) Obtenha o nome de cada departamento e a média de salário paga em cada um.

SELECT D.NOME_DEPTO, AVG(F.SALARIO) "MEDIA SALARIO"
FROM DEPARTAMENTO D
     INNER JOIN FUNCIONARIO F
           ON F.COD_DEPTO = D.COD_DEPTO
GROUP BY D.NOME_DEPTO;  

--9) Obtenha o nome de cada departamento e o maior salário pago em cada departamento, mas desde que
--esse salário seja >= 1500 (selecione em ordem decrescente de salário).

SELECT D.NOME_DEPTO, MAX(F.SALARIO) "SALARIO MAX"
FROM DEPARTAMENTO D
     INNER JOIN FUNCIONARIO F
           ON F.COD_DEPTO = D.COD_DEPTO        
GROUP BY D.NOME_DEPTO
HAVING MAX(F.SALARIO) >= 1500
ORDER BY MAX(F.SALARIO);  

--10) Obtenha o nome de cada projeto e a quantidade total de horas trabalhadas pelos funcionários em cada um
--deles, em ordem decrescente do total de horas, mas desde que o total de horas trabalhadas no projeto seja maior
--que 200.

SELECT P.NOME_PROJ, SUM(FP.HORAS_TRAB) "TOTAL HORAS"
FROM PROJETO P
 INNER JOIN FUNC_PROJ FP
  ON FP.COD_PROJ = P.COD_PROJ
GROUP BY P.NOME_PROJ
HAVING SUM(FP.HORAS_TRAB) > 200
ORDER BY SUM(FP.HORAS_TRAB) DESC;       

--11) Obtenha o nome de cada funcionário e a quantidade de projetos que cada um trabalhou.

SELECT F.NOME_FUNC, COUNT(FP.COD_PROJ) "QTD PROJETO"
FROM FUNCIONARIO F
 INNER JOIN FUNC_PROJ FP
   ON F.COD_FUNC = FP.COD_FUNC
GROUP BY F.NOME_FUNC;   

--12) Obtenha o nome de cada projeto e a quantidade de funcionários que trabalharam em cada um deles, mas
--desde que o número de funcionários por projeto seja superior a três funcionários.

SELECT P.NOME_PROJ, COUNT(F.COD_FUNC) "QTD FUNCIONARIO"
FROM FUNCIONARIO F
 INNER JOIN FUNC_PROJ FP
   ON F.COD_FUNC = FP.COD_FUNC
 INNER JOIN PROJETO P
   ON P.COD_PROJ = FP.COD_PROJ        
GROUP BY P.NOME_PROJ
HAVING COUNT(F.COD_FUNC) > 3;   







