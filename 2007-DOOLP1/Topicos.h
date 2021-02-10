#pragma once
#include <iostream> 
#include <cmath>    
#include <string>
#include <vector>  
#include "Informes.h"

using namespace std;

class Topicos: public Informes{
	//int _qtdComentarios;
	public:
		//vector<Comentarios> _Comentarios; //Post cadastrado
		//void CadastraComentario(string autor,string informe); //Metodo que cadastra o nome do usuario para um determinado informe
		//void ExibirComentarios(int pid); //metodo para exibir os usuarios recebe um id para exibir blogueiros ou leitores
		Topicos(void);
		~Topicos(void);
};
