#pragma once
#include <iostream> 
#include <cmath>    
#include <string> 

using namespace std;

class Informes{
		string _Informe; //informe cadastrado
		string _NomeAutor; //nome do usuario que criou o post
		int _idPost; //Verifica se eh topico ou informe
	public:
		void setIdPost(int id);
		void setNomeAutor(string nome);
		void setInforme(string informe);
		string getInforme() const; //metodo que retorna o informe
		string getAutor() const; //metodo que retorna o nome do usuario do informe
		int getIdPost() const;	//metodo que retorna o id do post
		Informes(void);
		~Informes(void);
};
