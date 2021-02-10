#include "Informes.h"
#include <iostream> 
#include <cmath>    
#include <string> 

using namespace std;

void Informes::setNomeAutor(string nome){
	Informes::_NomeAutor = nome;
}
void Informes::setInforme(string informe){
	Informes::_Informe = informe;
}
void Informes::setIdPost(int id){
	Informes::_idPost = id;
}

Informes::Informes(void){
	Informes::_NomeAutor = "";
	Informes::_idPost = 0;
	Informes::_Informe = "";
}

Informes::~Informes(void){
}

string Informes::getAutor() const{
		return Informes::_NomeAutor;
}
int Informes::getIdPost() const{
		return Informes::_idPost;
}

string Informes::getInforme() const{
	return Informes::_Informe;
}
