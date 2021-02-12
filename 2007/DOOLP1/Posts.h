#pragma once
#include "Informes.h"
#include "Topicos.h"
#include <vector> 
#include <iostream>
#include <cstdlib>


using namespace std;

class Posts{
		int _qtdposts;
	public:
		vector<Informes> _Posts; //guarda tanto informes quanto topicos
		void CadastraInforme(string autor,string informe, int idpost); //Metodo que cadastra o nome do usuario para um determinado informe
		void CadastraTopicos(string autor,string informe, int idpost); //Metodo que cadastra o nome do usuario para um determinado informe
		void ExibirPosts(int pid); //metodo para exibir os usuarios recebe um id para exibir blogueiros ou leitores
		Posts(void);
		~Posts(void);
};
