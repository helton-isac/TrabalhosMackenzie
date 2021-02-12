
--EXTRA) NOME E SALARIO, DESDE QUE O SALARIO SEJA MAIOR QUE A MÉDIA
         SELECT NOME, SALARIO FROM EMPREGADOS
         WHERE SALARIO > (SELECT AVG(SALARIO) FROM EMPREGADOS);

--1) (utilize join e sub-select) Obtenha o nome da esposa do empregado de nome 'Jose'.

              SELECT D.NOME_DEP FROM DEPENDENTES D
              INNER JOIN EMPREGADOS E
                    ON E.COD_EMP = D.COD_EMP
              WHERE E.NOME LIKE 'Jose'
              AND D.GRAU_PARENTESCO LIKE 'Esposa';


              SELECT NOME_DEP FROM DEPENDENTES
              WHERE COD_EMP IN (SELECT COD_EMP FROM EMPREGADOS WHERE NOME LIKE 'Jose')
              AND GRAU_PARENTESCO LIKE 'Esposa';

--2) (utilize somente join) Obtenha o nome de cada empregado e o nome do seu respectivo supervisor.
     
     SELECT E1.NOME, E2.NOME 
     FROM EMPREGADOS E1
     INNER JOIN EMPREGADOS E2
           ON E2.COD_EMP = E1.COD_EMP_SUPERV;          
   
--3) (utilize join e sub-select) Obtenha o nome do supervisor do empregado Jose.

     SELECT E1.NOME, E2.NOME "NOME SUPERVISOR"
      FROM EMPREGADOS E1
      INNER JOIN EMPREGADOS E2 
            ON E2.COD_EMP = E1.COD_EMP_SUPERV
      WHERE E1.NOME LIKE 'Jose';

      SELECT E1.NOME, (SELECT E2.NOME FROM EMPREGADOS E2 WHERE E2.COD_EMP = E1.COD_EMP_SUPERV) "NOME SUPERVISOR"
      FROM EMPREGADOS E1
      WHERE E1.NOME LIKE 'Jose';

--4) (utilize join e sub-select) Obtenha a quantidade de empregados que a Ana supervisiona.
              
              --JOIN
              SELECT COUNT(E1.NOME)
              FROM EMPREGADOS E1
              INNER JOIN EMPREGADOS E2
                ON E2.COD_EMP = E1.COD_EMP_SUPERV
              WHERE E2.NOME LIKE 'Ana';  
              
              --SUB-SELECT
              SELECT COUNT(E1.COD_EMP)
              FROM EMPREGADOS E1
              WHERE E1.COD_EMP_SUPERV IN (SELECT E2.COD_EMP 
                                         FROM EMPREGADOS E2 
                                         WHERE E2.COD_EMP = E1.COD_EMP_SUPERV 
                                         AND E2.NOME LIKE 'Ana');
                    


--5) (utilize join e sub-select) Obtenha o nome das máquinas que o empregado João utilizou nos
--projetos ProdutoY ou Reorganização.

           SELECT M.NOME_MAQ 
           FROM EMPREGADOS E1
           INNER JOIN UTILIZA U
                ON U.COD_EMP = E1.COD_EMP
           INNER JOIN MAQUINAS M
                ON M.COD_MAQ = U.COD_MAQ
           INNER JOIN PROJETOS P
                 ON P.COD_PROJ = U.COD_PROJ
           WHERE E1.NOME LIKE 'Joao' AND (P.NOME_PROJ LIKE 'ProdutoY' OR P.NOME_PROJ LIKE 'Reorganizacao');      
           
           
           SELECT NOME_MAQ 
           FROM MAQUINAS 
           WHERE COD_MAQ IN (SELECT COD_MAQ 
                                FROM UTILIZA
                                WHERE COD_PROJ IN (SELECT P.COD_PROJ FROM PROJETOS P 
                                                  WHERE P.NOME_PROJ LIKE 'ProdutoY' OR P.NOME_PROJ LIKE 'Reorganizacao')
                                AND COD_EMP IN (SELECT COD_EMP FROM EMPREGADOS 
                                                WHERE NOME LIKE 'Joao'));       
           
           
--6) (utilize somente sub-select) Aumente em 20% o salário dos empregados do departamento de
--Pesquisa.

     SELECT (SALARIO*1.20) "AUMENTO" FROM EMPREGADOS E1
     WHERE COD_DEPTO IN (SELECT COD_DEPTO FROM DEPARTAMENTOS D 
                         WHERE D.NOME_DEPTO LIKE 'Pesquisa');
                         
                         
     UPDATE EMPREGADOS SET SALARIO = SALARIO*1.20 
     WHERE COD_DEPTO IN (SELECT COD_DEPTO FROM DEPARTAMENTOS D 
                         WHERE D.NOME_DEPTO LIKE 'Pesquisa');                   

--7) (utilize somente sub-select) Elimine todos os projetos e respectivas máquinas que a empregada
--Renata trabalhou. (TBL UTILIZA)
                      DELETE FROM UTILIZA 
                      WHERE COD_EMP IN (SELECT COD_EMP FROM EMPREGADOS
                                        WHERE NOME LIKE 'Renata');
                                        
                      SELECT * FROM UTILIZA
                      WHERE COD_EMP IN (SELECT COD_EMP FROM EMPREGADOS WHERE NOME LIKE 'Renata');
                      

