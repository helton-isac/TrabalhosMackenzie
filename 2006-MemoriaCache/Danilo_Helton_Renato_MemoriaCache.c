/*
******************************************************************************************
*** MACKENZIE ****************************************************************************
*********************** ORGANIZAÇÃO E ARQUITETURA DE COMPUTADORES ********* 4° Semestre **
******************************************************************************************
*** Nomes:                                            ************************************
***        Danilo Marques Ribeiro         3060233-5   ************************************
***		   Helton Isac Torres Galindo     3068645-8   ************************************
***        Renato Ribeiro Pedrosa         3062961-6   ************************************
******************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Descrição: MÉTODOS E FUNÇÕES
*/
int SimularCache(int intOptMap, int intCacheSize, int intConjSize, int intOptSub,float *ptrQtdAcesso,float *ptrQtdMiss,float *ptrQtdAcessoBytes,float *ptrQtdBytesEnviados, char* strFile);
int MenuInicial();
int Mapeamento();
int DefinirTamCache();
int AssociativoConjunto();
int PoliticaSubstituicao();
int RetornarErro();
void MapeamentoDireto_Result(float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados);
void MapeamentoAssociativo_Result(int intPolSubst, int intCacheSize, float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados);
void MapeamentoAssociativoConj_Result(int intPolSubst, int intConjSize, int intCacheSize, float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados);
void ResultadoSimulacao(float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados);

/*
	Descrição: Método Principal
*/
int main(){
	int intOption;//.......................Armazena a opção do usuario
	int intAuxSimula;//....................Acompanha a simulação 
	int intAux, lintAux2;//................Inteiros Auxiliares
	int intOptMap = 0;//...................Opção de mapeamento
	int intCacheSize;//....................Tamanho definido para a cache
	int intConjSize = 0;//.................Tamanho Conjunto associativo
	int intConjSizeAux = 0;//..............Auxiliar Tamanho Conjunto associativo
	int intOptSub = 1;//...................Politica de Substituição
	int intOptSubAux = 1;//................Auxiliar para Politica de Substituição
	int intBest = 0;//.....................Define qual simulação teve o melhor desempenho
	int intMtzParametros[10][3];//.........MATRIZ = [0]-Mapeamento [1]-Política de Substituição [2]-Tamanho do conjunto
	char strFile[20]; //...................Conjuto de caracteres para armazenar o nome do arquivo 
	float fltPercentDesemp = 10;//.........Para comparar os resultados e chegar no melhor desempenho
	float fltPercentDesempAux;//...........Para comparar os resultados e chegar no melhor desempenho
	float fltVetSimula[4];//...............Guarda os resultados da simulação atual
	float fltMtzResultados[10][4];//.......Resultados [0]-Qtd de acessos [1]-Qtd miss [2]-bytes acessados [3]-bytes transmitidos

    do{
		intOption = MenuInicial();
		if (intOption == 1){
			intOptMap = Mapeamento();
			//Se não escolheu a Opção Sair
			if (intOptMap != 0){
                do{
    				//Define o tamanho da Cache
        			intCacheSize = DefinirTamCache();
        			if(intCacheSize < 2){
						printf("\n\tValor não pode ser menor que 2!!!\n");            
                    }
                }while(intCacheSize < 2);
				//Mapeamento direto não possui politica de Substituição (LRU, Random ou FIFO
    			if (intOptMap!=1){
    				intOptSub = PoliticaSubstituicao();
    				intOptSubAux = intOptSub;
    			}
				//Mapeamento associativo por conjunto
    			if (intOptMap == 3){
    				intConjSize = AssociativoConjunto();
    				intConjSizeAux++;
    			}
    			printf("\n\tInsira o caminho completo do arquivo Trace: ");
    			scanf("%s", &strFile);
                intAuxSimula = 0;
                do{
                    //Guarda resultados da simulação
    				lintAux2 = SimularCache(intOptMap, intCacheSize, intConjSize, intOptSub, &fltVetSimula[0], &fltVetSimula[1], &fltVetSimula[2], &fltVetSimula[3], strFile);
					if(lintAux2 == 0){
						break;
					}
                    intMtzParametros[intAuxSimula][0] = intOptMap;
                    intMtzParametros[intAuxSimula][1] = intOptSub;
                    intMtzParametros[intAuxSimula][2] = intConjSize;
					for(intAux=0;intAux<4;intAux++){
                        fltMtzResultados[intAuxSimula][intAux]=fltVetSimula[intAux];
					}
                    //Altera politica de subtituição para a próxima simulação   
					if(intOptSub==3){
						intOptSub=1;
					}else{
    					intOptSub++;
					}
                    //Altera o tipo de mapeamento para a próxima simulação
                    if(intOptSubAux == intOptSub || intOptMap == 1){                  
                        if(intOptMap == 3){
							if(intConjSizeAux == 2){
    							intOptMap = 1;
							}else{
                                intConjSize++;
								if (intConjSize == 3){
    								intConjSize = 1;
								}
                                intConjSizeAux++;
                            }
                        }else{
                            intOptMap++;
							if(intOptMap == 3){
    							intConjSize = intConjSizeAux = 1;
							}
							if(intOptMap == 2){
                                intOptSub--;
							}
                        }
                    }               
                    intAuxSimula++;
                }while(intAuxSimula < 10);
				if(lintAux2 == 0){
					break;
				}
                //Gerando a tabela de Resultados
                for(intAux = 0; intAux < 10; intAux++){
					if(intMtzParametros[intAux][0] == 1){
    					MapeamentoDireto_Result(fltMtzResultados[intAux][0],fltMtzResultados[intAux][1],fltMtzResultados[intAux][2],fltMtzResultados[intAux][3]);
					}
					if(intMtzParametros[intAux][0] == 2){
                        MapeamentoAssociativo_Result(intMtzParametros[intAux][1],intCacheSize,fltMtzResultados[intAux][0],fltMtzResultados[intAux][1],fltMtzResultados[intAux][2],fltMtzResultados[intAux][3]);
					}
					if(intMtzParametros[intAux][0] == 3){
                        MapeamentoAssociativoConj_Result(intMtzParametros[intAux][1],intMtzParametros[intAux][2],intCacheSize,fltMtzResultados[intAux][0],fltMtzResultados[intAux][1],fltMtzResultados[intAux][2],fltMtzResultados[intAux][3]);
					}
                    //Verifica quem obteve o melhor desempenho
                    fltPercentDesempAux = (fltMtzResultados[intAux][1]/fltMtzResultados[intAux][0])+(1-(fltMtzResultados[intAux][2]/fltMtzResultados[intAux][3]));
                    if(fltPercentDesempAux < fltPercentDesemp){
                        fltPercentDesemp = fltPercentDesempAux;
    					intBest = intAux;
                    }   
                }
				//Exibe o melhor desempenho
                printf("\n\t\a");
                printf("\n\t---------------------------------------------------------------"); 
                printf("\n\t*********************  MELHOR DESEMPENHO  *********************");
				if(intMtzParametros[intBest][0] == 1){
    				MapeamentoDireto_Result(fltMtzResultados[intBest][0],fltMtzResultados[intBest][1],fltMtzResultados[intBest][2],fltMtzResultados[intBest][3]);
				}
				if(intMtzParametros[intBest][0] == 2){
    				MapeamentoAssociativo_Result(intMtzParametros[intBest][1],intCacheSize,fltMtzResultados[intBest][0],fltMtzResultados[intBest][1],fltMtzResultados[intBest][2],fltMtzResultados[intBest][3]);
				}
				if(intMtzParametros[intBest][0] == 3){
    				MapeamentoAssociativoConj_Result(intMtzParametros[intBest][1],intMtzParametros[intBest][2],intCacheSize,fltMtzResultados[intBest][0],fltMtzResultados[intBest][1],fltMtzResultados[intBest][2],fltMtzResultados[intBest][3]);
				}
                printf("\n\t");
                system("PAUSE");
    		}
        }
	}while(intOption != 0);
	return 0;
} 
/*
	Descrição: Simula as atividades de uma memoria cache
*/
int SimularCache(int intOptMap, int intCacheSize, int intConjSize, int intOptSub, float *ptrQtdAcesso, float *ptrQtdMiss, float *ptrQtdAcessoBytes, float *ptrQtdBytesEnviados, char* strFile){
	int lintAux1;//Verificam se o valor já estava na cache virtual
	int lintAux2;//Verificam se o valor já estava na cache virtual
	int lintAux3;//Verificam se o valor já estava na cache virtual
	int lintAux4;//Verificam se o valor já estava na cache virtual
	int lintAux5;//Verificam se o valor já estava na cache virtual
	int lintAux6;//Verificam se o valor já estava na cache virtual
	int lintCount;//Contador para o lado For
    int lintConjAux1;//Quando for LRU e FIFO em associativo por conjunto
	int lintConjAux2;//Quando for LRU e FIFO em associativo por conjunto
	int lintConjAux3;//Quando for LRU e FIFO em associativo por conjunto
	int lintConjAux4;//Quando for LRU e FIFO em associativo por conjunto
    int intMtzVirtualCache[intCacheSize];//Cache Virtual
    char chrLastChar;//Ultimo caractere lido.
    float lfltQtdAcesso;//Contador do número de caracteres. 
    float lfltAuxCount;//Auxiliar do controle de Bytes
	float fltQtdBytesEnviados;//Qtd Bytes Enviados
	float fltQtdAcessoBytes;//Qtd Bytes Acessados
    float fltQtdMiss = 0;//Quantidade de misses
	FILE *fileTrace;//Aponta para o arquivo Trace. 

	lintAux2 = 1000;
	lintAux6 = 0;
	lintConjAux1 = lintConjAux2 = lintConjAux3 = lintConjAux4 = 0;
    fltQtdAcessoBytes = 0;//zerar os bytes acessados
    fltQtdBytesEnviados = 0;//zerar os bytes transmitidos
    lfltQtdAcesso = 0; //zerar a quantidade de acessos(n° de linhas)
	for(lintCount = 0;lintCount < intCacheSize; lintCount++){
		intMtzVirtualCache[lintCount]=0;
	}
    //Verifica se abriu o arquivo
    if((fileTrace = fopen(strFile, "r")) == NULL){
		return RetornarErro();
	}
	//Inicializa o Rand
	srand(time(NULL));
	chrLastChar = getc(fileTrace);//Lê o primeiro caractere do texto.
	//Enquanto tiver caracteres na linha
	while (!feof(fileTrace)) { 
		//Se sim, o próximo caractere será a quantidade de bytes
		if(chrLastChar == ' '){
            lfltQtdAcesso++; 
            lfltAuxCount = getc(fileTrace); 
			lfltAuxCount = lfltAuxCount - 48;
            fltQtdAcessoBytes = fltQtdAcessoBytes + lfltAuxCount;
            //Mapeamento Direto
			if (intOptMap == 1){
				lintAux3 = lintAux1 / intCacheSize;
                lintAux3 = lintAux3 * intCacheSize;
                lintAux3 = lintAux1 - lintAux3;//Término do calculo da posição onde se encontra (endereço mod quantidade de posições)
                if(intMtzVirtualCache[lintAux3] != lintAux1){
					fltQtdMiss++;
                    fltQtdBytesEnviados = fltQtdBytesEnviados + (lfltAuxCount * 4);//Novo bloco será inserido nesta posição
                    intMtzVirtualCache[lintAux3] = lintAux1;//Substituição dos valores caso sejam diferentes
                }
                else fltQtdBytesEnviados = fltQtdBytesEnviados + lfltAuxCount;//Soma a quantidade de bytes transmitidos
            }
			//Mapeamento Associativo
            if(intOptMap == 2){
				lintAux3 = lintAux4 = 0;
				for(lintCount = 0; lintCount < intCacheSize; lintCount++){
					if(intMtzVirtualCache[lintCount] == lintAux1){//Valor encontrado
						lintAux3 = 1;
                        fltQtdBytesEnviados = fltQtdBytesEnviados + lfltAuxCount;//Soma a quantidade de bytes transmitidos
						if(lintCount == lintAux6 && intOptSub == 3){//utilizado para a politica de LRU
							lintAux6++;//lintAux6 á definir que será substituido
						}
						if(lintAux6 == intCacheSize && intOptSub == 3){//utilizado para a politica de LRU
							lintAux6 = 0;   
						}
                    }
				}
				if(lintAux3 == 0){
					fltQtdMiss++;
					fltQtdBytesEnviados = fltQtdBytesEnviados + (lfltAuxCount * 4);//Novo bloco será inserido nesta posição
					for(lintCount = 0;lintCount < intCacheSize; lintCount++)
						if(intMtzVirtualCache[lintCount] == 0){//Novo bloco vazio onde será inserido o novo valor
							intMtzVirtualCache[lintCount] = lintAux1;
							lintAux4 = 1;
							break;   
						}
					//Aplica a Politica selecionada
					if(lintAux4 == 0){
						if(intOptSub == 1)//Randomica
							intMtzVirtualCache[rand() % intCacheSize] = lintAux1;
						if(intOptSub == 2){//F.I.F.O.
							intMtzVirtualCache[lintAux6] = lintAux1;//lintAux6 define quem será substituido
							lintAux6++;
							if(lintAux6 >= intCacheSize)
								lintAux6 = 0;
						}
						if(intOptSub == 3)//LRU
							intMtzVirtualCache[lintAux6] = lintAux1;//lintAux6 define quem será substituido
					}
				}
			}
			//Mapeamento Associativo por conjunto
            if(intOptMap == 3){
				lintAux4 = lintAux5 = 0;
				lintAux3 = lintAux1 / intConjSize;
				lintAux3 = lintAux3 * intConjSize;
				lintAux3 = lintAux1 - lintAux3;//Término do calculo da posição onde se encontra (endereço mod quantidade de posições)
				//Procura o bloco em está o valor procurado
				for(lintCount = lintAux3 * (intCacheSize / intConjSize); lintCount < (1 + lintAux3) * (intCacheSize / intConjSize); lintCount++){
					if (intMtzVirtualCache[lintCount]==lintAux1){//Valor encontrado
						lintAux4=1;
					}
				}
				fltQtdBytesEnviados = fltQtdBytesEnviados + lfltAuxCount;//Soma a quantidade de bytes transmitidos
				if(lintAux4 == 0){ 
					fltQtdMiss++;
					//Novo bloco será inserido nesta posição
					fltQtdBytesEnviados = fltQtdBytesEnviados + (lfltAuxCount * 4);
					for(lintCount = lintAux3 * (intCacheSize / intConjSize); lintCount < (1 + lintAux3) * (intCacheSize / intConjSize); lintCount++){
						//Novo bloco vazio deste conjunto onde será inserido o novo valor   
						if(intMtzVirtualCache[lintCount] == 0){
							intMtzVirtualCache[lintCount] = lintAux1;
							lintAux5 = 1;
							break;
						}
					}
					//Aplica a politica selecionada
					if(lintAux5 == 0){
						if(intOptSub == 1){//Randomico
							intMtzVirtualCache[(lintAux3 * (intCacheSize / intConjSize)) + (rand() % ((1 + lintAux3) * (intCacheSize / intConjSize)))] = lintAux1;
						}
						//Politica FIFO
						if(intOptSub == 2){
							//Para 2 way
							if(intConjSize == 1){
								if(lintAux3 * (intCacheSize / intConjSize) == 0){
									//lintConjAux1 será o "ponteiro" do primeiro bloco
									intMtzVirtualCache[lintConjAux1] = lintAux1;
									lintConjAux1++;
									if(lintConjAux1 >= intCacheSize){
										lintConjAux1 = 0;
									}
								}else{
									//lintConjAux2 será o "ponteiro" do segundo bloco
									intMtzVirtualCache[lintConjAux2] = lintAux1;
									lintConjAux2++;
									if(lintConjAux2 >= intCacheSize){
										lintConjAux2=0;
									}
								}
							//Para 4 way
							}else{
								if(lintAux3 * (intCacheSize / intConjSize) == 0){
									//lintConjAux1 será o "ponteiro" do primeiro bloco
									intMtzVirtualCache[lintConjAux1] = lintAux1;
									lintConjAux1++;
									if(lintConjAux1 >= intCacheSize){
										lintConjAux1=0;
									}
								}else if(lintAux3 * (intCacheSize / intConjSize) == 1 * intCacheSize / 4){
										//lintConjAux2 será o "ponteiro" do segundo bloco	
										intMtzVirtualCache[lintConjAux2] = lintAux1;
										lintConjAux2++;
										if(lintConjAux2 >= intCacheSize)
											lintConjAux2 = 0;
                                }else if(lintAux3 * (intCacheSize / intConjSize) == 2 * intCacheSize / 4) {
										//lintConjAux3 será o "ponteiro" do terceiro bloco	
										intMtzVirtualCache[lintConjAux3] = lintAux1;
										lintConjAux3++;
										if (lintConjAux3 >= intCacheSize){
											lintConjAux3=0;
										}
                                }else{
									//lintConjAux4 será o "ponteiro" do quarto bloco
									intMtzVirtualCache[lintConjAux4] = lintAux1;
                                    lintConjAux4++;
									if(lintConjAux4 >= intCacheSize){
										lintConjAux4=0;
									}
                                }
							}
						}
						//Politica LRU
						if(intOptSub == 3){
							//Para 2 way
							if(intConjSize == 1){
								if(lintAux3 * (intCacheSize / intConjSize) == 0){
									intMtzVirtualCache[lintConjAux1] = lintAux1;//lintConjAux1 será o "ponteiro" do primeiro bloco
									lintConjAux1++;
									if(lintConjAux1 >= intCacheSize){
										lintConjAux1 = 0;
									}
								}else{
									intMtzVirtualCache[lintConjAux2] = lintAux1;//lintConjAux2 será o "ponteiro" do segundo bloco
									lintConjAux2++;
									if(lintConjAux2 >= intCacheSize){
										lintConjAux2=0;
									}
								}
							//Para 4 way
							}else{
								if(lintAux3 * (intCacheSize / intConjSize) == 0){
									//lintConjAux1 será o "ponteiro" do primeiro bloco
									intMtzVirtualCache[lintConjAux1] = lintAux1;
                                    lintConjAux1++;	
									if(lintConjAux1>=intCacheSize){
										lintConjAux1=0;
									}
								}else if(lintAux3 * (intCacheSize / intConjSize) == 1 * intCacheSize / 4){
										//lintConjAux2 será o "ponteiro" do segundo bloco	
										intMtzVirtualCache[lintConjAux2] = lintAux1;
										lintConjAux2++;
										if (lintConjAux2>=intCacheSize)
											lintConjAux2=0;
                                }
                                else if(lintAux3 * (intCacheSize / intConjSize) == 2 * intCacheSize / 4){
										//lintConjAux3 será o "ponteiro" do terceiro bloco	
										intMtzVirtualCache[lintConjAux3] = lintAux1;
                                        lintConjAux3++;
										if(lintConjAux3 >= intCacheSize){
											lintConjAux3=0;
										}
                                }else{
									//lintConjAux4 será o "ponteiro" do quarto bloco
									intMtzVirtualCache[lintConjAux4] = lintAux1;
                                    lintConjAux4++;
									if(lintConjAux4 >= intCacheSize){
										lintConjAux4=0;
									}
                                }
							}
						}
					}
				}
			}
		//Procura o valor
        }else{
            lintAux1 = getc(fileTrace);
            lintAux1 = (lintAux1-48) * lintAux2;
            lintAux2 = lintAux2 / 10;
			if(lintAux2 == 0){
				lintAux2 = 1000;
			}
        }
        chrLastChar = getc(fileTrace);   
	}
    fclose(fileTrace);
    //Elaborar retorno
    *ptrQtdAcesso = lfltQtdAcesso;
    *ptrQtdMiss = fltQtdMiss;
    *ptrQtdAcessoBytes = fltQtdAcessoBytes;
    *ptrQtdBytesEnviados = fltQtdBytesEnviados;
    return 1;
}

//Interfaces------------------------------------------------------------------------------------------------------------------------
/*
	Descrição: Menu Inicial do Programa
*/
int MenuInicial(){
    int intOption;
    system("CLS");
    printf("\n\t**********SIMULADOR DE MEMORIA CACHE**********\n\n");    
    printf("\t1 - Iniciar Simulacao\n");
    printf("\t0 - Sair\n\n"); 	
    printf("\tEscolha uma opcao: ");
    scanf("%d", &intOption);
    return intOption;
}

/*
	Descrição: Menu que permite escolher entre os diversos tipos de mapeamento
*/
int Mapeamento(){
    int intOption;
    system("CLS");
    printf("\n\t**********SIMULADOR DE MEMORIA CACHE**********\n");    
    printf("\n\t                MAPEAMENTO\n\n");
    printf("\t1 - Mapeamento Direto\n");
    printf("\t2 - Mapeamento Associativo\n"); 
    printf("\t3 - Mapeamento Associativo por Conjunto\n");
    printf("\t0 - Sair\n\n"); 	
    printf("\tEscolha uma opcao: ");
    scanf("%d", &intOption);
    return intOption;
}

/*
	Descrição: Permite definir um tamanho para a cahe que sera simulada
*/
int DefinirTamCache(){
    int tam;
    printf("\n\tDefina um tamanho para Cache em Kb: ");
    scanf("%d", &tam);
    return tam;
}

/*
	Descrição: Exibe um Menu para escolher o tipo de mapeamento associativo por conjunto
*/
int AssociativoConjunto(){
    int intOption;
    system("CLS");
    printf("\n\t**********SIMULADOR DE MEMORIA CACHE**********\n"); 
    printf("\n\t      MAPEAMENTO ASSOCIATIVO POR CONJUNTO\n\n");
	printf("\t1 - 2 way\n");
    printf("\t2 - 4 way\n\n"); 
	printf("\tEscolha uma opcao: ");
    scanf("%d", &intOption);
    return intOption;
}

/*
	Descrição: Exibe um Menu para escolher a Politica de Substituição
*/
int PoliticaSubstituicao(){
    int intOption;
    system("CLS");
    printf("\n\t**********SIMULADOR DE MEMORIA CACHE**********\n"); 
    printf("\n\t           POLITICA DE SUBSTITUICAO\n\n");
	printf("\t1 - Substituicao Randomica\n");
    printf("\t2 - Substituicao FIFO\n"); 
	printf("\t3 - Substituicao LRU\n\n"); 
	printf("\tEscolha uma opcao: ");
    scanf("%d", &intOption);
    return intOption;
}

/*
	Descrição: Exibe um erro na Tela e fecha o Programa
*/
int RetornarErro(){
	printf("\n\tErro: Arquivo Invalido!!!\n\n\t");
	system("pause");
	return 0;    
}

/*
	Descrição: Exibe informações sobre o mapeamento Direto
*/
void MapeamentoDireto_Result(float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados){
	printf("\n\t---------------------------------------------------------------"); 
	printf("\n\tMapeamento: Direto\n\n");
	ResultadoSimulacao(fltQtdAcesso,fltQtdMiss,fltQtdAcessoBytes,fltQtdBytesEnviados);  
}

/*
	Descrição: Exibe informações sobre do mapeamento associativo
*/
void MapeamentoAssociativo_Result(int intPolSubst, int intCacheSize, float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados){
	char *lstrAux;   
	if(intPolSubst==1){
		lstrAux = "Randomico";
	}else if(intPolSubst==2){
		lstrAux = "F.I.F.O.";
	}else{ 
		lstrAux = "LRU";
	}
	printf("\n\t---------------------------------------------------------------"); 
	printf("\n\tMapeamento: Associativo\n");
	printf("\n\tPolitica de substituicao: %s\n\n", lstrAux);
	ResultadoSimulacao(fltQtdAcesso,fltQtdMiss,fltQtdAcessoBytes,fltQtdBytesEnviados); 
}

/*
	Descrição: Exibe informações sobre do mapeamento associativo com Conjunto
*/
void MapeamentoAssociativoConj_Result(int intPolSubst, int intConjSize, int intCacheSize, float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados){
	char *lstrAux;
	char *tam_conj_char;
	if (intConjSize==1){
		tam_conj_char="2 - Way";
    }else{
		tam_conj_char="4 - Way";
    }
	if(intPolSubst==1){
		lstrAux= "Randomico";
    }else if(intPolSubst == 2){
		lstrAux = "F.I.F.O.";
    }else{
		lstrAux = "L.R.U.";
    }
    printf("\n\t---------------------------------------------------------------"); 
	printf("\n\tTipo de Mapeamento................: Associativo por Conjunto\n");
	printf("\n\tPolitica de substituicao..........: %s", lstrAux);
	printf("\n\tTamanho do conjunto...............: %s\n\n", tam_conj_char);
	ResultadoSimulacao(fltQtdAcesso,fltQtdMiss,fltQtdAcessoBytes,fltQtdBytesEnviados);
}

/*
	Descrição: Tabela que exibe um resumo das tarefas realizadas
*/
void ResultadoSimulacao(float fltQtdAcesso, float fltQtdMiss, float fltQtdAcessoBytes, float fltQtdBytesEnviados){
	//Porcentagem de Miss
	float fltTxMiss = fltQtdMiss / fltQtdAcesso;
	//Porcentagem de Transferencias com sucesso
    float fltEfic = fltQtdAcessoBytes / fltQtdBytesEnviados;
	printf("\tQuantidade de Acessos.............: %.0f\n", fltQtdAcesso);     
	printf("\tQuantidade de Misses..............: %.0f\n", fltQtdMiss);     
	printf("\tQuantidade de bytes Acessados.....: %.0f\n", fltQtdAcessoBytes);     
	printf("\tQuantidade de bytes Transmitidos..: %.0f\n", fltQtdBytesEnviados);     
	printf("\tPorcentagem de Miss...............: %.2f\n", fltTxMiss);     
	printf("\tPorcentagem na Transferencia......: %.2f\n", fltEfic);     
}           
