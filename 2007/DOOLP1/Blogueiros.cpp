#include "Blogueiros.h"
#include <iostream> 
#include <cmath>    
#include <string>
#include <vector>  


using namespace std;

Blogueiros::Blogueiros(void)
{
	_qtdposts = 0;
}

Blogueiros::~Blogueiros(void)
{
}


 
 void Blogueiros::ExibirPosts(string autor,int pid)
{
	int i;

		if (pid == 0)
		{
			if (_qtdposts == 0)
  				cout << "\n\t***  Nao existem informes Cadastrados  ***\n";
			else
    			cout << "\n\t*****************  INFORMES CADASTRADOS  *****************\n";
		}
    	else
		{
			if (_qtdposts == 0)
  				cout << "\n\t***  Nao existem topicos Cadastrados  ***\n";
		   else   	
    			cout << "\n\t*****************  INFORMES CADASTRADOS  *****************\n";
		}
		for (i=0;i<_qtdposts;i++)
     	{
			if (_Posts[i].getAutor() == autor){
				if(_Posts[i].getIdPost() == pid)
					//cout << "\n\t| " << _Posts[i].getAutor() << " : " << _Posts[i].getInforme() << " |\n\n";
					cout<<_Posts[i];
			}
		}
}

 ostream& operator<<(ostream &out, Informes Posts)
{
	out << "\n\t| " << Posts.getAutor() << " : " << Posts.getInforme() << " |\n\n";
	return out;
}

 void Blogueiros::CadastraInforme(string autor,string informe, int idpost){
	Informes obj1; 
	obj1.setNomeAutor(autor);
	obj1.setIdPost(0);
	obj1.setInforme(informe);
	_Posts.resize(_qtdposts);
	_Posts.push_back(obj1);
	_qtdposts++;
}

 void Blogueiros::CadastraTopicos(string autor,string topico, int idpost){
	Topicos obj1; 
	obj1.setNomeAutor(autor);
	obj1.setIdPost(idpost);
	obj1.setInforme(topico);
	_Posts.resize(_qtdposts);
	_Posts.push_back(obj1);
	_qtdposts++;
}

int Blogueiros::getQtdePosts()
 {
	return _qtdposts;
 }
string Blogueiros::getAutorPosts(int posicao)
 {
	return _Posts[posicao].getAutor();
 }

int Blogueiros::getIdPosts(int posicao)
 {
	return _Posts[posicao].getIdPost();
 }
string Blogueiros::getPost(int posicao)
 {
	return _Posts[posicao].getInforme();
 }

 		

