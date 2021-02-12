/*********************************************
** Helton Isac Torres Galindo     3068645-8 **
** Renato Ribeiro Pedrosa         3062961-6 **
** 					                        **
** Sistemas Operacionais - 5°N              **
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define _MAX_ 101 /* define o tamanho maximo das strings */

char *trim_left(char *szSource);
char *trim_right(char *szSource);
char *trim(char *szSource);
void split(char *strToSplit, char *strArr[], char *strSeparator, int nArr);
char *strrepl(char *orgstr, char *oldstr, char *newstr);

int main(int argc, char *argv[])
{
	char comm[_MAX_]; /* comando e parametros */
	char *commSplit[_MAX_]; /* comando e parametros, o primeiro indice representa o comando e os outros os parametros */
	char commNoParam[_MAX_]; /* comando sem parametros */
	char *comercial; /* caractere para verificar se termina com & */
	int execBackgr; /* executar este comando em background? */

	char user[_MAX_]; /* usuario */
	char Diretorio_Atual[_MAX_]; /* diretorio atual */
	char home[_MAX_]; /* home do usuario */

	pid_t pidFork;

	int indice; /* indice utilizado em for */
	int retornoExec; /* resposta do exec */
	int retornoChdir; /* resposta do chdir */

	strcpy(user, getenv("USER")); /* le o usuario */
	getcwd(Diretorio_Atual, _MAX_); /* le o diretorio atual */
	strcpy(home, getenv("HOME")); /* le o home do usuario */

	while(1)
	{
		printf("[%s:%s]# ", user, Diretorio_Atual); /* imprime o prompt (Usuario:Diretorio) */
		fgets(comm, _MAX_, stdin); /* le o comando e parametros */
		strcpy(comm, trim(comm)); /* remove espacos e quebras de linha excedentes na esquerda e direita */

		comercial = comm + strlen(comm) - 1; /* localiza o ultimo caractere da string */
		if(*comercial == '&')
		{
			execBackgr = 1; /* comando em segundo plano */
			*comercial-- = '\0';
		}
		else
		{
			execBackgr = 0; /* comando em primeiro plano */
		}

		split(comm, commSplit, " ", _MAX_); /* separa o comando e os parametros em um vetor */

		strcpy(commNoParam, commSplit[0]); /* copia o comando somente para commNoParam */

		if(strlen(commNoParam) < 1) /* Nenhum comando digitado */
		{
			continue;
		}
		else if(strcmp(commNoParam, "exit") == 0)
		{
			exit(0);
		}
		else if(strcmp(commNoParam, "cd") == 0) /* mudar o diretorio */
		{
			if(commSplit[1] == NULL || strlen(commSplit[1]) < 1 || strcmp(commSplit[1], "~") == 0)
			{
				retornoChdir = chdir(home); /* mudar para home */
			}
			else
			{
				retornoChdir = chdir(commSplit[1]);
			}
			if(retornoChdir == -1)
			{
				printf("Caminho Inválido %s\n", commSplit[1]);
			}
			getcwd(Diretorio_Atual, _MAX_); /* atualiza o diretorio atual */
			continue;
		}
		else
		{
			pidFork = fork(); /* cria uma copia do processo atual */
			if(pidFork > 0) /* PAI */
			{
				if(execBackgr == 1) /* comando em segundo plano */
				{
					printf("PID filho: %d\n", pidFork);
				}
				else if(execBackgr == 0) /* espera o comando em primeiro plano */
				{
					waitpid(pidFork, NULL, WUNTRACED); /* espera ate que o processo do filho pare de executar */
				}
			}
			else /* filho */
			{
				sleep(1);
				retornoExec = execvp(commNoParam, commSplit); /* executa o comando com os parametros especificados */
				if(retornoExec == -1)
				{
					printf("%s: Aruivo/Diretorio Inválido\n", commNoParam);
				}
				exit(0);
			}
		}
	}

	return 0;
}

char *trim_left(char *szSource)
{
	char *pszBOS = 0;
	pszBOS = szSource;

	while(*pszBOS == ' ' || *pszBOS == '\n')
	{
		*pszBOS++;
	}

	return pszBOS;
}

char *trim_right(char *szSource)
{
	char *pszEOS = 0;
	pszEOS = szSource + strlen(szSource) - 1;

	while(pszEOS >= szSource && (*pszEOS == ' ' || *pszEOS == '\n'))
	{
		*pszEOS-- = '\0';
	}

	return szSource;
}

char *trim(char *szSource)
{
	return trim_left(trim_right(szSource));
}

void split(char *strToSplit, char *strArr[], char *strSeparator, int nArr)
{
	int i = 0;
	char *pch;
	char *strToSplitCpy;
	strcpy(strToSplitCpy, strToSplit);

	pch = strtok(strToSplitCpy, strSeparator);
	for(i = 0; i < nArr; i++)
	{
		strArr[i] = pch;
		pch = strtok(NULL, strSeparator);
	}
}

char *strrepl(char *orgstr, char *oldstr, char *newstr)
{
	int oldlen, newlen;
	char *s, *p;
	s = orgstr;
	while(s != NULL)
	{
		p = strstr(s, oldstr);
		if(p == NULL)
		{
			return orgstr;
		}
		oldlen = strlen(oldstr);
		newlen = strlen(newstr);
		orgstr = (char*)realloc(orgstr, strlen(orgstr)-oldlen+newlen+1);
		if (orgstr == NULL)
		{
			return NULL;
		}
		memmove(p + newlen, p + oldlen, strlen(p + oldlen) + 1);
		memcpy(p, newstr, newlen);
		s = p + newlen;
	}
	return orgstr;
}
