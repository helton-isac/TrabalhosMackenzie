select * from instituto;
select * from curso;
select * from disciplina;
select * from professor;
select * from aluno;
select * from aluno_disc;
select * from prof_disc;

--1) Retorne o nome de todos os cursos e o nome das disciplinas de cada curso, mesmo que o curso não tenha
--disciplina cadastrada ainda.
select c.nome_curso, d.nome_disciplina
from curso c
left join disciplina d
on c.cod_curso = d.cod_curso;

--2) Retorne o nome de todos os professores (mesmo daqueles que não orientam) e, para cada professor orientador,
--a quantidade de alunos que eles orientam.
select p.nome_professor, count(a.nome_aluno)
from professor p
left join aluno a
on p.cod_professor = a.cod_professor_orientador
group by p.nome_professor;

--3) Retorne o nome de todos os professores da universidade (mesmo aqueles que não estão ministrando
--disciplinas), e os nomes das disciplinas que eles ministram.
select p.nome_professor, d.nome_disciplina
from professor p
left join prof_disc pd
on p.cod_professor = pd.cod_professor
left join disciplina d
on pd.cod_disciplina = d.cod_disciplina;

--4) Retorne o nome de todos os alunos da universidade (mesmo daqueles que ainda não finalizaram nenhuma
--disciplina), os nomes das disciplinas e as notas de cada uma das disciplinas que os alunos cursaram, em ordem
--crescente de nota.
select a.nome_aluno, d.nome_disciplina, ad.nota
from aluno a
left join aluno_disc ad
on a.matricula = ad.matricula
left join disciplina d
on ad.cod_disciplina = d.cod_disciplina
order by ad.nota;

--5) Retorne o nome de todos os alunos (mesmo daqueles que ainda não finalizaram nenhuma disciplina) e, para
--cada aluno, a quantidade de disciplinas cursadas.
select a.nome_aluno, count(ad.matricula)
from aluno a
left join aluno_disc ad
on a.matricula = ad.matricula
group by a.nome_aluno;

--6) Retorne o nome de todos os cursos (mesmo daqueles que não tenham disciplinas cadastradas) e a quantidade
--de disciplinas de cada curso.
select c.nome_curso, count(cod_disciplina)
from curso c
left join disciplina d
on c.cod_curso = d.cod_curso
group by c.nome_curso;

--7) Retorne o nome de todos os alunos (mesmo daqueles que ainda não finalizaram nenhuma disciplina) e, para
--cada aluno, a sua média (considerando todas as disciplinas cursadas).
select a.nome_aluno, avg(ad.nota)
from aluno a
left join aluno_disc ad
on a.matricula = ad.matricula
group by a.nome_aluno;

--8) Retorne o nome de todos os institutos da universidade (mesmo aqueles que não tem cursos nem disciplinas
--cadastrados), e os nomes das disciplina destes institutos, em ordem crescente do nome do instituto.
select i.nome_instituto, d.nome_disciplina
from instituto i
left join curso c
on i.cod_instituto = c.cod_instituto
left join disciplina d
on c.cod_curso = d.cod_curso
order by i.nome_instituto;

