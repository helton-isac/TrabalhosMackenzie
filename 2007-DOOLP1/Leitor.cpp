#include "Leitor.h"
#include <iostream> 
#include <cmath>    
#include <string> 

using namespace std;

void Leitor::setNome(string n){
	Leitor::_nome = n;
}

Leitor::Leitor(void){
	Leitor::_nome = "0";
	Leitor::_Idusuario = 0;
}

Leitor::~Leitor(void){
}

string Leitor::getNome() const{
		return Leitor::_nome;
}
int Leitor::GetIdUsuario() const{
		return Leitor::_Idusuario;
}

void Leitor::setIdUsuario(int id){
	Leitor::_Idusuario = id;
}
