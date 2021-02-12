#pragma once
#include <iostream> 
#include <cmath>    
#include <string> 

using namespace std;

class Leitor{
	string _nome;
	int _Idusuario;
	string _comentario;
	string _dono;
public:
	void Comentar(string); //metodo para comentar um informe
	void Ler(); //metodo para ler um informe
	void setNome(string n); //metodo que cadastra o nome do usuario
	void setIdUsuario(int id); //metodo que cadastra o usuario que comentou o informe
	int GetIdUsuario() const;
	virtual void CadastraInforme(string autor,string informe, int idpost){}; //Metodo que cadastra o nome do usuario para um determinado informe
	virtual void CadastraTopicos(string autor,string topico, int idpost){}; //Metodo que cadastra o nome do usuario para um determinado informe
	virtual void ExibirPosts(string autor,int pid){}; //metodo para exibir os usuarios recebe um id para exibir blogueiros ou leitores
	virtual int getQtdePosts(){return 0;};
	virtual	string getAutorPosts(int posicao){return "";};
	virtual	int getIdPosts(int posicao){return 0;};
	virtual	string getPost(int posicao){return "";};
	void setUsuario(string n); //metodo que cadastra o usuario que comentou o informe
	string getNome() const; //metodo que retorna o nome do usuario
	Leitor(void);
	~Leitor(void);
};
