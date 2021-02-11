/***********************************************
** Helton Isac Torres Galindo ***** 3068645-8 **
** Renato Ribeiro Pedrosa ********* 3062961-9 **
** Ciência da Computação ***************** 6N **
************ Redes de Computadores *************
***********************************************/

//Para compilar no Dev-C++ importe biblioteca abaixo
//C:/Dev-Cpp/lib/libwsock32.a

//Para compilar no Visual Studio 2005 descomente a linha abaixo
//#pragma comment(lib, "wsock32.lib")//-----------------------
//----------------------------------------------------------
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#define PORTA_LOCAL 5555
#define MAX 1000

//Cria um Socket associado a uma porta
int cria_socket(const char *host, int pPorta);
//Aguarda uma resposta do servidor
int aguardaResp(int sock, int time);
//Envia uma mensagem ao cliente
int enviaMsg(int sock, char *mensagem);
//Exibe uma mensagem e abandona o programa em caso de erro
void abandonar_programa(char *mensagem);

//Função principal
int main(int argc, char **argv){
	int		sock, 
			nbytes;

	char	*host;

	char	buffer[MAX];

	WSADATA wsaData;

	//Verifica se ocorreu algum erro na hora se "startar" o serviço
	if(WSAStartup(MAKEWORD(1,1),&wsaData)) {
		fputs("Erro no WAStartup\n",stderr);
	}

	//Se recuperou o nome da linha de comando
	if(argc > 1){
		//Host = linha de comando
		host = argv[1];
	}else{
		//Host = localhost
		host = "localhost";
	}
	//Cria o socket
	sock = cria_socket(host, PORTA_LOCAL);
	
	do{
		printf("Mensagem a ser enviada ou apenas ENTER para sair: ");
		fgets(buffer, MAX, stdin);
		if(*buffer < ' '){
			abandonar_programa("Saindo do Programa");
		}
		//Envia uma mensagem para o servidor
		enviaMsg(sock, buffer);
		//Aguarda a Resposta
		if(aguardaResp(sock,10) == 0){
			abandonar_programa("Não obteve resposta");
		}
		//Verifica a resposta
		nbytes = recv(sock, buffer, MAX, 0);
		if(nbytes < 0){
			abandonar_programa("Erro na resposta");
		}
		//Exibe a resposta do servidor
		printf("Resposta do Servidor: %s\n\n", buffer);
	}while(1);
	closesocket(sock);
	return 0;
}

//Cria um Socket associado a uma porta
int cria_socket(const char *host, int pPorta){
	int		sock;

	struct hostent	*infHost;

	struct sockaddr_in	strSock;

	//Cria o socket
	sock = socket(PF_INET, SOCK_STREAM, 0);
	//Se não conseguiu criar o socket exibe a mensagem e sai do programa
	if(sock < 0){
		abandonar_programa("Não foi possível criar o socket");
	}

	//Seleciona o tipo de protocolo e configura a porta
	strSock.sin_family=AF_INET;
	strSock.sin_port=htons(pPorta);
	
	//solicita informações utilizando o nome do Host
	infHost = gethostbyname(host);
	//Se recebeu Nulo como informação
	if(infHost==NULL){
		abandonar_programa("Host fora do padrão");
	}
	//Seleciona o Ip do Host
	strSock.sin_addr = *(struct in_addr *)infHost->h_addr;
	//Realiza a conexão com o Host
	if(connect(sock, (struct sockaddr *)&strSock, sizeof(strSock)) < 0){
		abandonar_programa("Connect (client)");
	}
	return sock;
}

//Aguarda uma resposta do servidor
int aguardaResp(int sock, int time){
	struct timeval timeout;

	fd_set sock_fd_set;

	int intReturn;

	timeout.tv_sec = time;
	timeout.tv_usec = 0;
	FD_ZERO(&sock_fd_set);
	FD_SET(sock,&sock_fd_set);
	if(time>0){
		intReturn = select(FD_SETSIZE, &sock_fd_set, NULL, NULL, &timeout);
	}else{
		intReturn = select(FD_SETSIZE, &sock_fd_set, NULL, NULL, NULL);
	}
	if(intReturn < 0){
		abandonar_programa("select");
	}
	return intReturn;
}

//Envia uma mensagem ao cliente
int enviaMsg(int sock, char *mensagem){
	int intReturn;
	intReturn = send(sock, mensagem, strlen(mensagem) + 1, 0);
	if(intReturn < 0){
		abandonar_programa("Erro ao enviar mensagem");
	}
	return intReturn;
}

//Exibe a Mensagem e abandona o programa
void abandonar_programa(char *mensagem){
	perror(mensagem);
	exit(EXIT_FAILURE);
}

