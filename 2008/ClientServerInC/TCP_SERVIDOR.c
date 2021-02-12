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
int cria_socket(int pPorta);
//Recebe mensagem do cliente
int recebe_cliente(int filedes);
//Envia uma mensagem para um cliente
int envia_cliente(int filedes, char *mensagem);
//Exibe uma mensagem e abandona o programa em caso de erro
void abandonar_programa(char *mensagem);

//Função principal
int main(){
	int		sock, 
			sockCli;

	struct	sockaddr_in addrCli;

	size_t	sizeCliente;

	WSADATA wsaData;

	//Verifica se ocorreu algum erro na hora se "startar" o serviço
	if(WSAStartup(MAKEWORD(1,1),&wsaData)) {
		fputs("Erro no WAStartup\n",stderr);
	}

	printf("Criando o socket\n");
	/* Cria um socket para receber o contato inicial com um cliente */
	sock = cria_socket(PORTA_LOCAL);
	printf("Socket criado com sucesso\n");
	printf("Socket: %d\n\n",sock);
	
	//Aceita conexao, cria um socket para realizar comunição com o cliente e fica aguardando
	sizeCliente = sizeof(addrCli);
	sockCli = accept(sock, (struct sockaddr *)&addrCli, &sizeCliente);
	
	//Se não conseguiu realizar a conexão
	if(sockCli < 0){
		abandonar_programa("Erro na conexão");
	}
	//Exibe msg se não ocorreu erro
	printf(stderr, "Conexao realizada com %s, handle=%d\n", inet_ntoa(addrCli.sin_addr), sockCli);

	//Loop de comunicação com o cliente
	while(recebe_cliente(sockCli) >= 0){
		envia_cliente(sockCli, "Mensagem recebida com sucesso.");
	}

	//Fecha a conexão com o Client
	close(sockCli);
	return 0;
}

//Cria e retorna o socket para uma determinada porta
int cria_socket(int pPorta){
	int		sock, 
			sockBind;
	struct	sockaddr_in strSock;
	
	//Cria o socket
	sock = socket(PF_INET, SOCK_STREAM, 0);
	//Se não conseguiu criar o socket exibe a mensagem e sai do programa
	if(sock < 0){
		abandonar_programa("Não foi possível criar o socket");
	}

	//Seleciona o tipo de protocolo ,a porta e define que irá aceitar conexões de qualquer endereço
	strSock.sin_family = AF_INET;
	strSock.sin_port = htons(pPorta);
	strSock.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//Liga o socket a uma porta de servico
	sockBind = bind(sock, (struct sockaddr *)&strSock, sizeof(strSock));
	if(sockBind < 0){
		abandonar_programa("Não foi possível realizar o bind");
	} 
	
	//Libera para atender conexoes na porta */
	if(listen(sock,1) < 0){
		abandonar_programa("socket");
	}
	//Retorna o Socket criado
	return sock;
}

//Realiza a comunicação com o cliente
int envia_cliente(int filedes, char *mensagem){
	int qtdBytes; 
	qtdBytes = send(filedes, mensagem, strlen(mensagem) + 1, 0);
	if(qtdBytes < 0){
		abandonar_programa("Erro ao enviar mensagem");
	}
	return qtdBytes;
}

//Recebe mensagem do cliente
int recebe_cliente(int filedes){
	char buffer[MAX]; 
	int qtdBytes;
	qtdBytes = recv(filedes, buffer, MAX-1,0);
	if(qtdBytes < 0){
		abandonar_programa("Erro ao receber Mensagem");
	}
	if(qtdBytes == 0){
		return -1;
	}
	printf("Mensagem recebida: %s\n", buffer);
	return qtdBytes;
}

//Exibe a Mensagem e abandona o programa
void abandonar_programa(char *mensagem){
	perror(mensagem);
	exit(EXIT_FAILURE);
}

