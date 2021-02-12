#include "Seguranca.h"

#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cmath>    
#include <cstdlib>
#include <string> 
#define MAX 1000

using namespace std;

void Seguranca::CadastrarLeitor(string n,int id){
	Leitor obj1; 
	obj1.setNome(n);
	obj1.setIdUsuario(id);
	_Usuarios.resize(_qtdusuarios);
	_Usuarios.push_back(&obj1);
	_qtdusuarios++;
}

void Seguranca::CadastrarBlogueiro(string n,int id){
	Blogueiros *obj1 = new Blogueiros; 
	obj1->setNome(n);
	obj1->setIdUsuario(id);
	_Usuarios.resize(_qtdusuarios);
	_Usuarios.push_back(obj1);
	_qtdusuarios++;
}

//void Seguranca::CadastrarUsuario(string n,int id){
//	Leitor *obj1 = new Leitor;
//	if (id == 1)
//	{
//		obj1 = new Blogueiros;
//	}
//	else
//	{
//		obj1 = new Leitor;
//	}
//	obj1->setNome(n);
//	obj1->setId(_qtdusuarios);
//	obj1->setIdUsuario(id);
//	_Usuarios.push_back(obj1);
//	_qtdusuarios++;
//}

//void Seguranca::ExcluirBlogueiro(string nome){
//	int i;
//	if (_qtdBlogueiro == 0) return; 
//
//	if (vetBlogueiros[_qtdBlogueiro-1].getNome() == nome)
//		_qtdBlogueiro--;
//	else
//	{
//		for (i=0;i<_qtdBlogueiro;i++)
//		{
//			if (vetBlogueiros[i].getNome() == nome){
//				for (i=i;i<_qtdBlogueiro-1;i++)
//				{
//					vetBlogueiros[i] = vetBlogueiros[i+1];
//					_qtdBlogueiro--;
//				}
//				break;
//			}
//		}
//	}
//}

//void Seguranca::ExcluirLeitor(string nome){
//	int i;
//
//	if (_qtdLeitor == 0) return;
//	
//	if (vetLeitor[_qtdLeitor-1].getNome() == nome)
//		_qtdLeitor--;
//	else
//	{
//		for (i=0;i<_qtdLeitor;i++)
//		{
//			if (vetLeitor[i].getNome() == nome){
//				for (i=i;i<_qtdLeitor-1;i++)
//				{
//					vetLeitor[i] = vetLeitor[i+1];
//					_qtdLeitor--;
//				}
//				break;
//			}
//		}
//	}
//}



Seguranca::Seguranca(void)
{
	_qtdusuarios = 0;
}

Seguranca::~Seguranca(void)
{
	_Usuarios.~vector();

}


void Seguranca::ExibirUsuarios(int pid)
{
	int i;

		if (pid == 1)
		{
			if (_qtdusuarios == 0)
  				cout << "\n\t***  Nao existem Blogueiros Cadastrados  ***\n";
			else
    			cout << "\n\t*****************  BLOGUEIROS CADASTRADOS  *****************\n";
		}
    	else
		{
			if (_qtdusuarios == 0)
  				cout << "\n\t***  Nao existem Leitores Cadastrados  ***\n";
		   else   	
    			cout << "\n\t*****************  LEITORES CADASTRADOS  *****************\n";
		}
		for (i=0;i<_qtdusuarios;i++)
     	{
			if (_Usuarios[i]->GetIdUsuario() == pid){
      			//cout << "\n\t| " << _Usuarios[i]->getNome() << " |\n\n";
				cout<<*_Usuarios[i];
			}
		}
}

ostream& operator<<(ostream &out, Leitor Usuarios)
{
	out << "\n\t| " << Usuarios.getNome() << " |\n\n";
	return out;
}

int Seguranca::LogarUsuario(string nomeuser)
{
	int i;
	for (i=0;i<_qtdusuarios;i++)
	{
		if (nomeuser == _Usuarios[i]->getNome())
			return _Usuarios[i]->GetIdUsuario();
	}
	return -1;
}


void Seguranca::sprGravarDados()
{
	string n;
	int id;
	int  i;
	ofstream UserIn;
	//Abre para escrita. OBS Sobrepoe tudo cada vez que abre.
	UserIn.open("USUARIOS.txt", ios::out);

	//Se der erro Sai do programa
	if(!UserIn){
		cerr << "\n\tO arquivo nao pode ser aberto\n\t"
			 << "O Programa sera encerrado!!!\n\n\t";
		system ("PAUSE");
		exit(1); 
	}
	//Condição para continuar
	for (i=0; i<_qtdusuarios; i++){
		id = _Usuarios[i]->GetIdUsuario();
		UserIn << id << endl;
		n = _Usuarios[i]->getNome();
		UserIn << n << endl;
	}
	//Fecha o Arquivo
	UserIn.close();
}

void Seguranca::sprGravarDadosPosts()
{
	string n;
	int id;
	int  i,z;
	ofstream UserIn;
	//Abre para escrita. OBS Sobrepoe tudo cada vez que abre.
	UserIn.open("POSTS.txt", ios::out);

	//Se der erro Sai do programa
	if(!UserIn){
		cerr << "\n\tO arquivo nao pode ser aberto\n\t"
			 << "O Programa sera encerrado!!!\n\n\t";
		system ("PAUSE");
		exit(1); 
	}
	//Condição para continuar
	for (i=0; i<_Usuarios[0]->getQtdePosts(); i++){
		id = _Usuarios[i]->getIdPosts(i);
		UserIn << id << endl;
		n = _Usuarios[i]->getAutorPosts(i);
		UserIn << n << endl;
		n = _Usuarios[i]->getPost(i);
		UserIn << n << endl;
	}
	//Fecha o Arquivo
	UserIn.close();
}
