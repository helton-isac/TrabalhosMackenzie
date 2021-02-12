/****************************************************
LP1 ----------------------------------------- Noturno
Projeto DOOLP1 -------------------------- 1o.Sem.2007
Autor: <Helton Isac Galindo>
	   <Renato Ribeiro Pedrosa>
****************************************************/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string> 
#include <cstdlib>
#include "Blogueiros.h"
#include "Leitor.h"
#include "Seguranca.h"
#define MAX 1000

using namespace std;

int menu_principal(); //menu principal do DOOLP1
string menu_Logar(); // menu para digitar o nome do usuario para logar
int MenuPosts(int id); //menu do usuario logado, o layout muda de acordo com o usuario
void MenPosts(int id, string nome, Seguranca *Cadastros); //metodo que define o que vai ser feito no menu post
string menu_Comentar_Blogueiro(); //menu para escolher qual informe vai ser lido (por usuario)
void sprRecuperaDados(Seguranca *Cadastros);
void sprRecuperaDadosPosts(Seguranca *Cadastros);


//metodo que define o que vai ser feito no menu principal
int main(){
	Seguranca Cadastros;
	int menuEscolha, Logado;
	string n,nomeuser;

	sprRecuperaDados(&Cadastros);
	sprRecuperaDadosPosts(&Cadastros);
	for(;;)
	{
		menuEscolha = 0;
		while (menuEscolha == 0)
		{
			system("CLS");
			menuEscolha = menu_principal();
			cout << endl << endl;
		}
		switch (menuEscolha)
		{
			case 1: 
   				nomeuser = menu_Logar();
				Logado = Cadastros.LogarUsuario(nomeuser);
				if (Logado == 1 || Logado == 2)
					MenPosts(Logado, nomeuser,&Cadastros);
				break;
			case 2: 
					fflush(stdin);
					cout << "\tInsira um nome: ";
					getline(cin,n);
					if( n == "" ){
						cout << "\n\n\tLeitor Invalido" << endl;
						break;
					}
					if (Cadastros.LogarUsuario(n) != -1){
						cout << endl << "\n\n\tLeitor " << n << " previamente cadastrado. Entre com outro nome| " << endl;
						break;
					}
					Cadastros.CadastrarLeitor(n,2);
					cout << endl << "\n\n\tLeitor | " << n << " | cadastrado com sucesso " << endl;
					break;
			case 3: 
					fflush(stdin);
					cout << "\tInsira um nome: ";
					getline(cin,n);
					if( n == "" ){
						cout << "\n\n\tBlogueiro Invalido" << endl;
						break;
					}
					if (Cadastros.LogarUsuario(n) != -1){
						cout << endl << "\n\n\tBlogueiro " << n << " previamente cadastrado. Entre com outro nome| " << endl;
						break;
					}
					Cadastros.CadastrarBlogueiro(n,1);
					cout << "\n\n\tBlogueiro | " << n << " | cadastrado com sucesso\n";
					break;
			case 4:
				Cadastros.ExibirUsuarios(2);
				break;
			case 5:
				Cadastros.ExibirUsuarios(1);
				break;
			case 7:
                 fflush(stdin);
                 cout << "\tDigite o nome do usuario a ser excluido: ";
				 getline(cin,n);
				 //Cadastros.ExcluirBlogueiro(n);
				 cout << "\n\tBlogueiro | " << n << " | excluido com sucesso\n";
				 break;
			case 8:
                   system("Color 0A"); break;
            case 9:
                   system("Color 07"); break;
		}
		cout << endl << "\t";
		if (menuEscolha == 10) break;
		if (menuEscolha < 8 || menuEscolha > 9) system("PAUSE");
	}
	Cadastros.sprGravarDados();
	Cadastros.sprGravarDadosPosts();
	system("Pause");
	return 0;
}

int menu_principal(){
	int menuEscolha;

	cout << "\t*****************    DOOLP1    *****************" << endl;
	cout << "\t*   1  - Logar em DOOLP1                       *" << endl;
	cout << "\t*   2  - Cadastrar Leitor                      *" << endl;
	cout << "\t*   3  - Cadastrar Blogueiro                   *" << endl;
	cout << "\t*   4  - Ver Nomes Leitor                      *" << endl;
	cout << "\t*   5  - Ver Nomes Blogueiros                  *" << endl;
	cout << "\t*   6  - Excluir Leitor                        *" << endl;
	cout << "\t*   7  - Excluir Blogueiro                     *" << endl;
	cout << "\t*   8  - Cores do Matrix                       *" << endl;
	cout << "\t*   9  - Cores Normais                         *" << endl;
	cout << "\t*   10 - Sair                                  *" << endl;
	cout << "\t************************************************\n\n" << endl;
	cout << "\tO Que Deseja Fazer: " ;
	cin >> menuEscolha;
	if (menuEscolha < 1 || menuEscolha > 10){
		cout << "\n";
		cout << "\t************************************************" << endl;
		cout << "\t**************** OPCAO INVALIDA ****************" << endl;
		cout << "\t************************************************" << endl << "\n\t";
		system("PAUSE");
		return 0;
	}
	else
		return menuEscolha;
}

string menu_Logar(){
	string nome;
		fflush(stdin);
		system("CLS");
		cout << "\n\t********************** LOGAR **********************\n\n";
		cout << "\tDigite o nome do seu usuario: "; 
		getline(cin,nome);
		return nome;
}

int MenuPosts(int id){
	int menuEscolha;
	for(;;){
		cout << "\t********************** DOOLP1 **********************\n\n";
		cout << "\t1 - Ler Topicos / Informes " << endl;
		cout << "\t2 - Comentar Topicos " << endl;
	    cout << "\t3 - Excluir Comentarios " << endl;
		if (id == 1){
			cout << "\t4 - Publicar Informe " << endl;
			cout << "\t5 - Excluir Informe " << endl;
			cout << "\t6 - Logout " << endl;
			cout << "\tO Que Deseja Fazer: " ;
			cin >> menuEscolha;
			if (menuEscolha < 1 || menuEscolha > 6) return 0;
			if (menuEscolha == 6) return -1;
		}
		else{
			cout << "\t4 - Logout " << endl;
			cout << "\tO Que Deseja Fazer: " ;
			cin >> menuEscolha;
			if (menuEscolha < 1 || menuEscolha > 4) return 0;
			if (menuEscolha == 4) return -1;
			}
		return menuEscolha;
	}
}

void MenPosts(int id, string nome,Seguranca *Cadastros){
	int menuEscolha;
	string n;
	int idinf;

	for(;;){
		menuEscolha = 0;
		while (menuEscolha == 0){
			system("CLS");
			menuEscolha = MenuPosts(id);
			if (menuEscolha == -1) break;
		}
		switch (menuEscolha){
			case 1:
				n = menu_Comentar_Blogueiro();
				if (Cadastros->LogarUsuario(n) == -1)
					cout << endl << "\n\n\tBlogueiro " << n << " nao cadastrado. Entre com outro nome| \n" << endl;
				else
					Cadastros->_Usuarios[0]->ExibirPosts(n,0);
				system("PAUSE");
				break;
			case 2: 
				break;
			case 3: 
				break;
			case 4:
				cout << "\n\n\tCadastre um Informe: ";
				fflush(stdin);
				getline(cin,n);
				Cadastros->_Usuarios[0]->CadastraInforme(nome,n,0);
				cout << endl << "\n\tInforme | " << n << " | cadastrado com sucesso\n\t";
				system("PAUSE");
				break;
			case 5:
					fflush(stdin);
					cout << "\tDigite o Id do informe a ser excluido: ";
					cin >> idinf;
					//Cadastros->vetBlogueiros[0].ExcluirInforme(idinf);
					cout << "\n\tInforme | " << idinf << " | excluido com sucesso\n\t";
					system("PAUSE");
					break;
		}
		cout << "\n\t";
		if (menuEscolha == -1) break;
	}
}

string menu_Comentar_Blogueiro(){
    	string nome;
		fflush(stdin);
		system("CLS");
		cout << "\n\n\tDigite o nome do Blogueiro a ser consultado: "; 
		getline(cin,nome);
		return nome;
}


void sprRecuperaDados(Seguranca *Cadastros)
{
	char string_aux[MAX];
	//instrução para criar um arquivo pra nao dar erro
	ofstream UserIn;
	UserIn.open("USUARIOS.txt", ios::app);
	UserIn.close();
	
	ifstream UserOut("USUARIOS.txt", ios::in);
	if(!UserOut){
		cerr << "\n\tO arquivo nao pode ser aberto\n\t"
			 << "O Programa sera encerrado!!!\n\n\t";
		system ("PAUSE");
		exit(1); 
	}
	if (!UserOut.eof()){
		do{
			UserOut.getline(string_aux, MAX-1, '\n');
			if(string_aux[0] == '\0') break;
			if(string_aux[0] == '1'){
				UserOut.getline(string_aux, MAX-1, '\n');
				Cadastros->CadastrarBlogueiro(string_aux,1);
			}
			else{
				UserOut.getline(string_aux, MAX-1, '\n');
				Cadastros->CadastrarBlogueiro(string_aux,2);
			}
		}while (!UserOut.eof());
	}
	UserOut.close();
}

void sprRecuperaDadosPosts(Seguranca *Cadastros)
{
	char string_aux[MAX];
	char autor[MAX];
	char post[MAX];
	//instrução para criar um arquivo pra nao dar erro
	ofstream UserIn;
	UserIn.open("POSTS.txt", ios::app);
	UserIn.close();
	
	ifstream UserOut("POSTS.txt", ios::in);
	if(!UserOut){
		cerr << "\n\tO arquivo nao pode ser aberto\n\t"
			 << "O Programa sera encerrado!!!\n\n\t";
		system ("PAUSE");
		exit(1); 
	}
	if (!UserOut.eof()){
		do{
			UserOut.getline(string_aux, MAX-1, '\n');
			if(string_aux[0] == '\0') break;
			if(string_aux[0] == '0'){
				UserOut.getline(autor, MAX-1, '\n');
				UserOut.getline(post, MAX-1, '\n');
				Cadastros->_Usuarios[0]->CadastraInforme(autor,post,0);
			}
			else{
				UserOut.getline(autor, MAX-1, '\n');
				UserOut.getline(post, MAX-1, '\n');
				Cadastros->_Usuarios[0]->CadastraInforme(autor,post,1);
			}
		}while (!UserOut.eof());
	}
	UserOut.close();
}