#include "Posts.h"

#include <iostream> 
#include <cmath>    
#include <string> 

using namespace std;

Posts::Posts(void){
}

Posts::~Posts(void){
}

void ExibirPosts(int pid)
{
}

void Posts::CadastraInforme(string autor,int informe, int idpost){
	Informes obj1; 
	obj1.setNomeAutor(autor);
	obj1.setIdPost(0);
	obj1.setInforme(informe);
	_Usuarios.resize(_qtdposts);
	_Usuarios.push_back(obj1);
	_qtdposts++;
}

void Posts::CadastraTopicos(string n,int id){
	/*Blogueiros obj1; 
	obj1.setNome(n);
	obj1.setIdUsuario(id);
	_Usuarios.resize(_qtdusuarios);
	_Usuarios.push_back(obj1);
	_qtdusuarios++;*/
}