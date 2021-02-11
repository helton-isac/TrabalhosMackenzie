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
#define MAX 1000
#define PORTA_LOCAL 6000

//Função Principal
int main() {
	int		sock, 
			serverSock, 
			verificaMsgCli, 
			tamAddrCli;
	
	struct	sockaddr_in addrClient, 
			addrServer;
	
	char	mensagen[MAX];

	WSADATA wsaData;
        
	WSAStartup(MAKEWORD(2,1), &wsaData);
  	
	//Criação do Socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	//Verifica se o socket foi criado com sucesso
	if(sock < 0){
		printf("valor de sock: %d",sock);
		printf("nao foi possivel abrir o Socket \n");
		exit(1);
	}
	printf("Socket %d criado com sucesso.\n",sock);

	//Seleciona o tipo de protocolo ,a porta e define que irá aceitar conexões de qualquer endereço
	//Adicionando a Porta Local
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORTA_LOCAL);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	//Liga o socket a uma porta de servico
	serverSock = bind (sock, (struct sockaddr *) &addrServer,sizeof(addrServer));
	//Se ocorrer erro exibe msg e abandona o programa
	if(serverSock < 0){
		printf("Erro - Adicionando a porta local %d\n", PORTA_LOCAL);
		exit(1);
	}
	printf("Aguardando Mensagens na porta UDP%u\n", PORTA_LOCAL);

	//Loop infinito do servidor aguardando mensagens
	for(;;){
		//Inicializa o buffer
		memset(mensagen,0x0, MAX);
		//Recebendo Mensagen
		tamAddrCli = sizeof(addrClient);
		//Verificando se pode receber mensagens
		verificaMsgCli = recvfrom(sock, mensagen, MAX, 0,(struct sockaddr *) &addrClient, &tamAddrCli);
		//Se receber dados invalidos exibe msg e continua
		if(verificaMsgCli < 0){
			printf("não pode receber dados\n");
			continue;
		}
		//Exibindo a Mensagen recebida
		printf("De: %s: UDP%u : %s \n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), mensagen);
	}
	//Fechando o socket
	closesocket(sock);	
	WSACleanup();
	return 0;
}

