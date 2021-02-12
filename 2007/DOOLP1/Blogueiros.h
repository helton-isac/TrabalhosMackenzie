#pragma once
#include "Leitor.h"
#include "Informes.h"
#include "Topicos.h"
#include <iostream> 
#include <cmath>    
#include <string>
#include <vector> 

using namespace std;

class Blogueiros: public Leitor{
		int _qtdposts;
	public:
		vector<Informes> _Posts; //guarda tanto informes quanto topicos
		void CadastraInforme(string autor,string informe, int idpost); //Metodo que cadastra o nome do usuario para um determinado informe
		void CadastraTopicos(string autor,string topico, int idpost); //Metodo que cadastra o nome do usuario para um determinado informe
		void ExibirPosts(string autor,int pid); //metodo para exibir os usuarios recebe um id para exibir blogueiros ou leitores
		int getQtdePosts();
		string getAutorPosts(int posicao);
		int getIdPosts(int posicao);
		string getPost(int posicao);
		friend ostream& operator<<(ostream&out,Informes Posts);
		 Blogueiros(void);
		~Blogueiros(void);
};
