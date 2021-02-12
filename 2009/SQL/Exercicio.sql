
--1)	Obtenha a média de salário pago em cada departamento 
--(considere o código de cada departamento).

SELECT AVG(SALARIO), COD_DEPTO 
FROM FUNCIONARIO
GROUP BY COD_DEPTO;


--2)	Obtenha o código de cada projeto e a quantidade total de horas trabalhadas 
--pelos funcionários em cada um deles, em ordem decrescente do total de horas, 
--mas desde que o total de horas trabalhadas no projeto seja maior que 200.

SELECT COD_PROJ, SUM(HORAS_TRAB) HORAS_TRAB
FROM FUNC_PROJ
GROUP BY COD_PROJ
HAVING SUM(HORAS_TRAB) > 200
ORDER BY HORAS_TRAB DESC;

--3)	Obtenha o total gasto em salário em cada departamento 
--da empresa (considere somente o código do departamento).

SELECT SUM(SALARIO), COD_DEPTO 
FROM FUNCIONARIO
GROUP BY COD_DEPTO;

--4)	Obtenha, para cada funcionário (considere somente o código do funcionário), 
--a quantidade de horas trabalhadas nos projetos como um todo.

SELECT COD_FUNC, COD_PROJ, SUM(HORAS_TRAB)
FROM FUNC_PROJ
GROUP BY COD_FUNC, COD_PROJ
ORDER BY COD_FUNC, COD_PROJ;

--5)	Obtenha a quantidade de funcionários de cada departamento (considere somente o código do departamento).

SELECT COD_DEPTO, COUNT(*) 
FROM FUNCIONARIO
GROUP BY COD_DEPTO;

--6)	Obtenha, para cada projeto (considere somente o código do projeto), 
--a quantidade de funcionários que trabalharam em cada um deles, 
--mas desde que o número de funcionários por projeto seja superior a trás funcionários.

SELECT COD_PROJ , COUNT(*)
FROM FUNC_PROJ
GROUP BY COD_PROJ
HAVING COUNT(*) > 3;

