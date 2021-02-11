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
#include <stdio.h> 
#include <winsock2.h> 
#include <windows.h> 
#define MAX 1000
#define PORT 6000

//Função Principal
int main() { 
    int		sock; 
    
	struct	sockaddr_in addrClient; 
    
	char	mensagem[MAX]; 
    
	WSADATA WinsockData; 

    WSAStartup(MAKEWORD(2,2), &WinsockData);
	//Criação do Socket
    sock = socket(AF_INET, SOCK_DGRAM, 17);
	//Verifica se o socket foi criado com sucesso
	if(sock < 0){
		printf("nao foi possivel criar o Socket \n");
		exit(1);
	}
    printf("Soquete criado com sucesso\n\n"); 
    //Configurando addrClient
    addrClient.sin_family = AF_INET; 
    addrClient.sin_port = htons(PORT); 
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    memset(&(addrClient.sin_zero), '\0', 8); 
    //Enviando mensagem
    for (;;){
        printf("Mensagem a ser enviada: ");
        scanf("%s",&mensagem);
        sendto(sock, mensagem, strlen(mensagem), 0, (struct sockaddr *)&addrClient, sizeof(struct sockaddr)); 
        printf("Mensagem enviada com sucesso\n\n"); 
        getchar();
    }
    WSACleanup(); 
    return 0;
} 







