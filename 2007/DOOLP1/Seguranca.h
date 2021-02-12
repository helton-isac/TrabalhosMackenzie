#pragma once
#include "Blogueiros.h"
#include "Leitor.h"
#include <vector> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Seguranca{
	int _qtdusuarios;
public:
	vector<Leitor*> _Usuarios;
	void CadastrarLeitor(string n,int id); //metodo que cadastra os leitores
	void sprGravarDados();
	void sprGravarDadosPosts();
	void CadastrarBlogueiro(string n,int id); //metodo que cadastra os blogueiros
	void ExibirUsuarios(int pid); //metodo para exibir os usuarios recebe um id para exibir blogueiros ou leitores
	int LogarUsuario(string nomeuser); //metodo para verificar se o usuario existe e para saber o tipo de usuario 
	friend ostream& operator<<(ostream&out,Leitor Usuarios);
	Seguranca(void);
	~Seguranca(void);
};
