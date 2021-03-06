CREATE TABLE TB_FONTES_INFORMACAO (
  COD_FONTE INTEGER  NOT NULL ,
  DES_FONTE VARCHAR(250) NOT NULL,
  CONSTRAINT "PK_TB_FONTES_INFORMACAO" PRIMARY KEY ("COD_FONTE"));

CREATE TABLE TB_GRUPO_NOTICIA (
  COD_GRUPO_NOTICIA INTEGER  NOT NULL ,
  DES_GRUPO_NOTICIA VARCHAR(60) NULL,
  CONSTRAINT "PK_TB_GRUPO_NOTICIA" PRIMARY KEY ("COD_GRUPO_NOTICIA"));

CREATE TABLE TB_EDITOR (
  COD_EDITOR INTEGER  NOT NULL ,
  DES_NOME VARCHAR(30) NOT NULL,
  DES_EMAIL VARCHAR(255) NOT NULL,
  ACESSO INTEGER NOT NULL,
  CONSTRAINT "PK_TB_EDITOR" PRIMARY KEY ("COD_EDITOR"));

CREATE TABLE TB_ASSINANTE (
  COD_MATRICULA INTEGER  NOT NULL ,
  DES_NOME VARCHAR(30) NOT NULL,
  DES_EMAIL VARCHAR(255) NOT NULL,
  ACESSO INTEGER NOT NULL,
  CONSTRAINT "PK_TB_ASSINANTE" PRIMARY KEY ("COD_MATRICULA"));

CREATE TABLE TB_ASSINANTE_GRUPO_NOTICIA (
  COD_GRUPO_NOTICIA INTEGER  NOT NULL,
  COD_MATRICULA INTEGER  NOT NULL,
  CONSTRAINT "FK01_TB_GRUPO_NOT" FOREIGN KEY ("COD_GRUPO_NOTICIA")
    REFERENCES TB_GRUPO_NOTICIA("COD_GRUPO_NOTICIA"),
  CONSTRAINT "FK02_TB_ASSINANTE" FOREIGN KEY ("COD_MATRICULA")
    REFERENCES TB_ASSINANTE("COD_MATRICULA"));

CREATE TABLE TB_INFORMACAO_NOTICIA (
  COD_INFORMACAO INTEGER  NOT NULL,
  COD_GRUPO_NOTICIA INTEGER  NULL,
  COD_FONTE INTEGER  NOT NULL,
  COD_EDITOR INTEGER  NULL,
  DES_INFORMACAO_NOTICIA VARCHAR(250) NOT NULL,
  DAT_VALIDADE DATE NULL,
  DAT_ENTRADA DATE NULL,
  CONSTRAINT "PK_TB_INFORMACAO_NOTICIA" PRIMARY KEY("COD_INFORMACAO"),
  CONSTRAINT "FK01_TB_EDITOR" FOREIGN KEY("COD_EDITOR")
    REFERENCES TB_EDITOR ("COD_EDITOR"),
  CONSTRAINT "FK02_TB_FONTES" FOREIGN KEY ("COD_FONTE")
    REFERENCES TB_FONTES_INFORMACAO ("COD_FONTE"),
  CONSTRAINT "FK03_TB_GRUPO_NOTICIA" FOREIGN KEY ("COD_GRUPO_NOTICIA")
    REFERENCES TB_GRUPO_NOTICIA ("COD_GRUPO_NOTICIA"));

CREATE TABLE TB_INFORMACAO_SATISFACAO (
  COD_INFORMACAO INTEGER  NOT NULL,
  NOTA_INFORMACAO INTEGER  NOT NULL,
  INFO_UTIL INTEGER NOT NULL,
  COD_MATRICULA INTEGER  NOT NULL,	
  CONSTRAINT "FK01_TB_INFORMACAO_NOTICIA" FOREIGN KEY ("COD_INFORMACAO")
    REFERENCES TB_INFORMACAO_NOTICIA ("COD_INFORMACAO")),
  CONSTRAINT "FK02_TB_ASSINANTE3" FOREIGN KEY ("COD_MATRICULA")
    REFERENCES TB_ASSINANTE("COD_MATRICULA"));

CREATE TABLE TB_INFO_STATUS (
  COD_INFORMACAO INTEGER  NOT NULL,
  NUM_STATUS INTEGER NOT NULL ,
  CONSTRAINT "FK01_TB_INFORMACAO_NOTICIA2" FOREIGN KEY("COD_INFORMACAO")
    REFERENCES TB_INFORMACAO_NOTICIA("COD_INFORMACAO"));

INSERT INTO TB_FONTES_INFORMACAO (COD_FONTE, DES_FONTE) VALUES (1, 'Email Secretaria')
INSERT INTO TB_FONTES_INFORMACAO (COD_FONTE, DES_FONTE) VALUES (2, 'Reitor')
INSERT INTO TB_FONTES_INFORMACAO (COD_FONTE, DES_FONTE) VALUES (3, 'Secretaria')
INSERT INTO TB_FONTES_INFORMACAO (COD_FONTE, DES_FONTE) VALUES (4, 'Correio')
INSERT INTO TB_FONTES_INFORMACAO (COD_FONTE, DES_FONTE) VALUES (5, 'Email Professores')

INSERT INTO TB_GRUPO_NOTICIA (COD_GRUPO_NOTICIA,DES_GRUPO_NOTICIA) VALUES (1,'Emprego');
INSERT INTO TB_GRUPO_NOTICIA (COD_GRUPO_NOTICIA,DES_GRUPO_NOTICIA) VALUES (2,'Palestras');
INSERT INTO TB_GRUPO_NOTICIA (COD_GRUPO_NOTICIA,DES_GRUPO_NOTICIA) VALUES (3,'Noticias da Faculdade');
INSERT INTO TB_GRUPO_NOTICIA (COD_GRUPO_NOTICIA,DES_GRUPO_NOTICIA) VALUES (4,'Cursos');
INSERT INTO TB_GRUPO_NOTICIA (COD_GRUPO_NOTICIA,DES_GRUPO_NOTICIA) VALUES (5,'Mural de Recados');

INSERT INTO TB_EDITOR (COD_EDITOR ,DES_NOME,DES_EMAIL,ACESSO) VALUES (1,'RAFAEL BASTOS','cqc@cqc.com.br',1);
INSERT INTO TB_EDITOR (COD_EDITOR ,DES_NOME,DES_EMAIL,ACESSO) VALUES (2,'RODRIGO SPOOL','roro@gmail.com',1);
INSERT INTO TB_EDITOR (COD_EDITOR ,DES_NOME,DES_EMAIL,ACESSO) VALUES (3,'DANIEL AVELAR','daniela@execplan.com.br',0);

INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30686458,'HELTON ISAC','helton_isac@ig.com.br',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30625634,'RENATO PEDROSA','renato@uol.com.br',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (36254879,'DIOGO DONIZETHE','diogo@aol.com.br',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30253264,'DOUGLAS SURICATE','douglas@hotmail.com',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30645896,'HUGO AMBROZINI','strubilaudotex@ig.com.br',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30698756,'DANILO MARQUES','danilo@yahoo.com.br',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30536985,'DUNIA SATI','dunia@bol.com.br',0);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30623652,'JULIANA SANDOW','juliana@gmail.com',0);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (32536251,'ROSANA PRIGNOLATO','rosana@hotmail.com',1);
INSERT INTO TB_ASSINANTE (COD_MATRICULA ,DES_NOME,DES_EMAIL,ACESSO) VALUES (30369854,'RICARDO JAF…','rick@ig.com.br',1);

INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (1, 30686458);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (1, 36254879);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (2, 30686458);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (2, 36254879);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (2, 32536251);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (3, 30645896);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (3, 32536251);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (3, 30625634);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (4, 30698756);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (4, 30645896);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (4, 30253264);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (5, 30686458);
INSERT INTO TB_ASSINANTE_GRUPO_NOTICIA (COD_GRUPO_NOTICIA, COD_MATRICULA) VALUES (5, 30253264);

INSERT INTO TB_INFORMACAO_NOTICIA (COD_INFORMACAO, COD_GRUPO_NOTICIA, COD_FONTE, COD_EDITOR, DES_INFORMACAO_NOTICIA, DAT_VALIDADE, DAT_ENTRADA) VALUES (1, 1, 2, 1, 'Vaga para professor de Teoria de Grafos, necess·rio boa did·tica e conhecimento!', TO_DATE('29/07/09', 'DD/MM/RR'), TO_DATE('19/05/09', 'DD/MM/RR'));
INSERT INTO TB_INFORMACAO_NOTICIA (COD_INFORMACAO, COD_GRUPO_NOTICIA, COD_FONTE, COD_EDITOR, DES_INFORMACAO_NOTICIA, DAT_VALIDADE, DAT_ENTRADA) VALUES (2, 4, 3, 2, 'Curso de gerenciamento de atividades escolares. No dia 23/05/09, administrada por Clint Eastwood no auditÛrio Rui Barbosa.', TO_DATE('23/05/09', 'DD/MM/RR'), TO_DATE('19/05/09', 'DD/MM/RR'));
INSERT INTO TB_INFORMACAO_NOTICIA (COD_INFORMACAO, COD_GRUPO_NOTICIA, COD_FONTE, COD_EDITOR, DES_INFORMACAO_NOTICIA, DAT_VALIDADE, DAT_ENTRADA) VALUES (3, 5, 1, 2, 'N„o haver· expediente no dia 27/06/09', TO_DATE('27/06/09', 'DD/MM/RR'), TO_DATE('19/05/09', 'DD/MM/RR'));
INSERT INTO TB_INFORMACAO_NOTICIA (COD_INFORMACAO, COD_GRUPO_NOTICIA, COD_FONTE, COD_EDITOR, DES_INFORMACAO_NOTICIA, DAT_VALIDADE, DAT_ENTRADA) VALUES (5, 5, 1, 2, 'N„o haver· expediente no dia 01/05/09', TO_DATE('01/05/09', 'DD/MM/RR'), TO_DATE('20/04/09', 'DD/MM/RR'));
INSERT INTO TB_INFORMACAO_NOTICIA (COD_INFORMACAO, COD_FONTE, DES_INFORMACAO_NOTICIA, DAT_ENTRADA) VALUES (4, 4, 'ManutenÁ„o do banco de dados!', TO_DATE('20/05/09', 'DD/MM/RR'));

INSERT INTO TB_INFORMACAO_SATISFACAO (COD_INFORMACAO, NOTA_INFORMACAO, INFO_UTIL, COD_MATRICULA) VALUES (1, 10, 1, 30686458);

INSERT INTO TB_INFO_STATUS (COD_INFORMACAO, NUM_STATUS) VALUES (1, '2')
INSERT INTO TB_INFO_STATUS (COD_INFORMACAO, NUM_STATUS) VALUES (2, '2')
INSERT INTO TB_INFO_STATUS (COD_INFORMACAO, NUM_STATUS) VALUES (3, '2')
INSERT INTO TB_INFO_STATUS (COD_INFORMACAO, NUM_STATUS) VALUES (4, '1')
INSERT INTO TB_INFO_STATUS (COD_INFORMACAO, NUM_STATUS) VALUES (5, '3')


