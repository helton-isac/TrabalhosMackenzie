/*********************************************
** Helton Isac Torres Galindo     3068645-8 **
** Renato Ribeiro Pedrosa         3062961-6 **
** 					                        **
** Programação Matematica - 5°N             **
*********************************************/
#include <cstdlib>
#include <iostream>
#define MAX 10
#define MAX_AUX 50

using namespace std;

void limpaTela();                  
void cabecalho_padrao();
void simplex(int qtd_VarDec, 
             float VarDec[],
			 int qtd_VarRest, 
             float VarRestri[][4], 
			 int *qtd_Solucoes, 
             float resultados[][MAX+2+3][MAX_AUX]);

void solucoesTipo(float resultados[][MAX+2+3][MAX_AUX], 
                  int qtd_VarRest, 
                  int qtd_VarDec, 
                  int qtd_Solucoes, 
                  int tipo);
                  
//Função principal
int main(){
    //Variaveis de controle
    int qtd_VarDec, 
        escolha, 
        qtd_VarRest, 
        i, j, qtd_Solucoes;
    float VarDec[3];
    float VarRestri[MAX][4];
    float resultados[MAX+1][MAX+2+3][MAX_AUX]={0};
    //Loop Infinito
    for(;;){
        do{
            cabecalho_padrao();          
            cout << endl << "\tBem vindo ao metodo Simplex" << endl;
            cout << endl << "\t                       Menu Principal" << endl;                                     
            cout << endl << "\t1 - Continuar";
            cout << endl << "\t2 - Abandonar";
            cout << endl << "\tFaca a sua escolha: ";
            cin >> escolha;
            if(escolha < 1 || escolha > 2){
                cout << endl;                            
                cout << "\tERRO: Opcao Invalida" << endl
                     << "\t      Tente novamente" << endl << endl << "\t";
                system("PAUSE");
                cout << endl;
            }
        }while(escolha < 1 || escolha > 2);          
        if(escolha == 2){
            break;
        }
        //Setando variaveis de controle como 0
        qtd_VarDec = qtd_VarRest = qtd_Solucoes = 0;
        //Setando as variaveis de decisão igual a 0
        for(i = 0;i < 2; i++){
            VarDec[i] = 0;
        }
        limpaTela();//Limpa o screen
        cabecalho_padrao();//Exibe o cabeçalho
        //Recebe as quantidade de Variaveis de decisão a serem utilizadas
        do{
           cout << endl << "Digite a quantidade de variaveis de decisao a serem utilizadas(1 - 3): ";
           cin >> qtd_VarDec;
           if(qtd_VarDec < 1 || qtd_VarDec > 3){
              cout << endl;                            
              cout << "ERRO: A quantidade devera ser um numero entre 1 e 3" << endl
                   << "      Tente novamente" << endl << endl << "\t";
              system("PAUSE");
              cout << endl;
           }
        }while(qtd_VarDec < 1 || qtd_VarDec > 3);
        //Recebe a quantidade de restrições a serem utilizadas
        do{
           cout << endl << "Digite a quantidade de restricoes a serem utilizadas: ";
           cin >> qtd_VarRest;
           if(qtd_VarRest < 0 || qtd_VarRest > MAX){
              cout << endl;
              cout << "ERRO: A quantidade devera ser um numero entre 0 e " << MAX << endl
                   << "      Tente novamente." << endl << endl << "\t";
              system("PAUSE");
              cout << endl;
           }             
        }while(qtd_VarRest < 0 || qtd_VarRest > MAX);
        //Exibe o cabeçalho
        cabecalho_padrao();
        //Recebe as variaveis de decisão da função objetivo                    
        cout << endl << "Insira "<< qtd_VarDec << " variaveis de decisao separando-as com Enter:" << endl;
        for(i = 0;i < qtd_VarDec;i++){
            cout << i + 1 << ": ";
            cin >> VarDec[i];
        }
        //Exibe o cabeçalho
        cabecalho_padrao();
        //Recebe as restrições
        cout << endl << "Insira "<< qtd_VarRest << " restricoes de acordo com o solicitado:" << endl << endl;
        for(i = 1; i <= qtd_VarRest;i++){
            for(j = 1; j <= qtd_VarDec; j++){
                 cout << j << " variavel de decisao da " << i << " restricao: ";
                 cin >> VarRestri[i-1][j];
            }
            cout <<  "Variavel Basica da " << i << " restricao: ";
            cin >> VarRestri[i][j];              
            cout << endl;
        }
        //Aplica o método Simplex
        simplex(qtd_VarDec,
		        VarDec,
		  	    qtd_VarRest,
				VarRestri,
				&qtd_Solucoes,
				resultados);
        do{
           do{
              cabecalho_padrao();           
              cout << endl << "\t                       Menu Resultado" << endl;                         
              cout << endl << "\t0 - Solucao Inicial";
              cout << endl << "\t1 - Solucao Otima";
              cout << endl << "\t2 - Todas as solucoes";
              cout << endl << "\t3 - Tabelas parciais";
              cout << endl << "\t4 - Reiniciar Metodo Simplex";
              cout << endl << "\t5 - Sair";                  
              cout << endl << "\tFaca a sua escolha: "; 
              cin >> escolha;
              if(escolha < 0 || escolha > 5){
                 cout << endl;                            
                 cout << "\tERRO: Opcao Invalida" << endl
                      << "\t      Tente novamente" << endl << endl << "\t";
                 system("PAUSE");
                 cout << endl;
              }                  
           }while(escolha < 0 || escolha > 5);
           //Define como agir de acordo com a opcao escolhida do usuario
		   if(escolha < 4){
                  solucoesTipo(resultados,qtd_VarRest,qtd_VarDec,qtd_Solucoes,escolha);
		   }
		   //Sai ou reinicia
		   if(escolha == 4 || escolha == 5){ 
              break;
		   }
        }while(escolha != 5);
		if(escolha == 5){
           break;        
        }   
    }
    return 0;
}
//Metodo Simplex
void simplex(int qtd_VarDec, 
             float VarDec[], 
			 int qtd_VarRest, 
             float VarRestri[][4], 
			 int *qtd_Solucoes, 
             float resultados[][MAX+2+3][MAX_AUX]){
                       
     int i,j,k,z,g,VarDecIn,VarOut,res,saida;
     int count1,count0,disponiveis[3]={0,0,0},SolOtima;
     float countAux;
	 res = saida = 1;
     //Gravando a solução inicial
	 for(i = 0;i < (qtd_VarRest + 1); i++){
		 resultados[i][0][0] = 0;
	 }
     resultados[0][0][0] = 1;
	 for(i = 1; i < (qtd_VarDec + 1); i++){
         resultados[0][i][0]=(VarDec[i - 1]) * -1;
	 }
     for(i = 1; i < (qtd_VarRest + 1); i++){
		 for(j = 1; j < (qtd_VarDec + 1); j++){
             resultados[i][j][0]=VarRestri[i - 1][j - 1];
		 }
		 for(k = 4; k < (qtd_VarRest + 4); k++){
             resultados[i][k][0]=0;
		 }
         resultados[i][i + 3][0] = 1;
         resultados[i][14][0] = VarRestri[i - 1][3];
     }
     while(saida != 0){
           SolOtima = 1;
           //Verificando quais variaveis de decisão são não básicas
           count1 = count0 = 0;
           for(z = 1; z < (qtd_VarDec + 1); z++){
               for(g = 0; g < (qtd_VarRest + 1); g++){
				   if(resultados[g][z][res-1]==1){
                      count1++;
				   }
				   if(resultados[g][z][res-1]==0){
                      count0++;
				   }
               }
			   if((count1 + count0) != (qtd_VarRest + 1)){
                  disponiveis[z - 1]=0;
			   }else {
				   disponiveis[z - 1]=1;           
			   }
           }     
           //Verificando qual variavel entra
           VarDecIn = 1;
           for(i = 0; i < qtd_VarDec; i++)
               if(VarDec[i] > VarDec[VarDecIn-1])
                  if(disponiveis[i] == 0)
                     VarDecIn = i + 1;
           //Verificando qual variavel saida
           countAux = resultados[1][14][res-1]/resultados[1][VarDecIn][res-1];
           VarOut = 1;
           for(j = 2; j < qtd_VarRest + 2; j++){
			   if(resultados[j][14][res - 1] / resultados[j][VarDecIn][res - 1] < 0){
				   if(((resultados[j][14][res - 1] / resultados[j][VarDecIn][res-1]) * -1) < countAux){
						VarOut = j;
				   }else{
						VarOut = VarOut;
				   }
			   }else if((resultados[j][14][res-1] / resultados[j][VarDecIn][res-1]) < countAux){
					VarOut = j;
			   }
           }
           //Alterando a linha pivô
           resultados[VarOut][0][res] = resultados[VarOut][0][res -1] / resultados[VarOut][VarDecIn][res -1];
		   for(i = 1; i < (qtd_VarDec + 1); i++){
               resultados[VarOut][i][res]=resultados[VarOut][i][res -1]/resultados[VarOut][VarDecIn][res -1];
		   }
		   for(i = 4; i < (qtd_VarRest + 4);i++){
               resultados[VarOut][i][res]=resultados[VarOut][i][res -1]/resultados[VarOut][VarDecIn][res- 1];
		   }
           resultados[VarOut][14][res] = resultados[VarOut][14][res - 1] / resultados[VarOut][VarDecIn][res-1];
           //Alterando demais linhas
           for(j = 0; j < (qtd_VarRest + 1); j++){
			   if(j!=VarOut){
                    resultados[j][0][res]=(resultados[VarOut][0][res-1] * resultados[j][VarDecIn][res - 1] * -1)+resultados[j][0][res-1];
					for(i = 1; i < qtd_VarDec + 1; i++){
                        resultados[j][i][res] = (resultados[VarOut][i][res] * resultados[j][VarDecIn][res - 1] * -1)+ resultados[j][i][res - 1];
					}
					for(i=4;i<qtd_VarRest+4;i++){
                        resultados[j][i][res]=(resultados[VarOut][i][res] * resultados[j][VarDecIn][res - 1] * -1)+resultados[j][i][res - 1];
					}
                    resultados[j][14][res]=(resultados[VarOut][14][res] * resultados[j][VarDecIn][res - 1] * -1)+resultados[j][14][res - 1];
               }
           }
           //Verificação da solução ótima
           for(j = 1;j < (MAX + 3); j++){
                count0 = count1 = 0;
				for(i = 0;i < (qtd_VarRest + 1); i++){
					if(resultados[i][j][res] == 1){
						count1++;
					}
					if(resultados[i][j][res] == 0){
						count0++;
					}
                }
				if((count1 + count0) != (qtd_VarRest + 1) && (resultados[0][j][res] < 0)){
                    SolOtima = 0;
				}
           }
           for(i = 1; i < qtd_VarDec + 1; i++)
                 if(resultados[0][i][res] < 0)
                    SolOtima = 0;
           if(SolOtima == 1)
              saida = 0;
           res++;
     }       
     *qtd_Solucoes = res;
}

//Seleciona um modo para exibir os relatorios
void solucoesTipo(float resultados[][MAX+2+3][MAX_AUX], 
				  int qtd_VarRest, 
				  int qtd_VarDec, 
				  int qtd_Solucoes, 
				  int tipo){
     int i, 
         j, 
         k;
     int countAux, 
         count1, 
         count0;
     countAux = count1 = count0 = 0;

	 switch(tipo){
		case 0:
			cabecalho_padrao();
			cout << endl << "\t***Solucao Inicial***" << endl << endl;
			cout << "\tVariaveis basicas:" << endl;
			for(j = 1; j < (MAX + 3); j++){
				count0 = count1 = 0;
				for(i = 0; i < qtd_VarRest + 1;i++){
					if(resultados[i][j][0] == 1){
						countAux = i;
						count1++;
					}
					if(resultados[i][j][0] == 0){
						count0++;
					}
				}
				if((count1 == 1) && (count0 == qtd_VarRest)){
					if(j >= 4){
						cout << "\tF" << j - 3 << " = " << resultados[countAux][14][0] << endl;
					}else{
						cout << "\tX" << j <<" = " << resultados[countAux][14][0] << endl;
					}
				}
			}
			cout << endl << "\tVariaveis nao basicas:" << endl; 
			for(j = 1; j < (MAX + 3); j++){
				count0 = count1 = 0;
				for(i = 0; i < qtd_VarRest + 1; i++){
					if(resultados[i][j][0] == 1){
						countAux = i;
						count1++;
					}
					if(resultados[i][j][0] == 0){
						count0++;
					}
				}
				if(count1 + count0 != qtd_VarRest + 1){
					if(j >= 4){
						cout << "\tF" << j - 3 << " = 0" << endl;
					}else{
						cout << "\tX" << j << " = 0" << endl;
					}
				}
			}
			cout << endl << "\tZ = " << resultados[0][14][0] << endl << endl << "\t"; 
			system("PAUSE");
			break;
		case 1:
			cabecalho_padrao();
			cout << endl << "\t***Solucao Otima***" << endl << endl;
			cout << "\tVariaveis basicas:" << endl;
			for(j = 1; j < (MAX + 3);j++){
				count0 = count1 = 0;
				for(i = 0; i < qtd_VarRest + 1; i++){
					if(resultados[i][j][qtd_Solucoes-1] == 1){
						countAux=i;
						count1++;
					}
					if(resultados[i][j][qtd_Solucoes-1]==0){
						count0++;
					}
				}
				if(count1==1 && count0==qtd_VarRest){
					if(j >= 4){
						cout << "\tF" << j - 3 << " = " << resultados[countAux][14][qtd_Solucoes-1] << endl;
					}else{
						cout << "\tX" << j << " = " << resultados[countAux][14][qtd_Solucoes-1] << endl;
					}
				}
			}
			cout << "\tVariaveis nao basicas:\n"; 
			for(j = 1; j < (MAX + 3); j++){
				count0 = count1 = 0;
				for(i = 0; i < (qtd_VarRest + 1); i++){
					if(resultados[i][j][qtd_Solucoes-1] == 1){
						countAux=i;
						count1++;
					}
					if(resultados[i][j][qtd_Solucoes-1] == 0){
						count0++;
					}
				}
				if(count1+count0!=qtd_VarRest+1){
					if(j>=4){
						cout << "\tF"<<j-3<<" = 0"<<"\n";
					}else{
						cout << "\tX"<<j<<" = 0"<<"\n";
					}
				}
			}
			cout << endl << "\tZ = " << resultados[0][14][qtd_Solucoes-1] << endl << endl << "\t";  
			system("PAUSE");
			break;             
		case 2:
			cabecalho_padrao();
			cout << endl << "\t***Todas Solucoes***" << endl << endl;
			for(k = 0; k < qtd_Solucoes; k++){
				cout << endl << "\tSolucao " << k + 1 << ": " << endl << endl;
				cout << "\tVariaveis basicas:" << endl;
				for(j = 1; j < (MAX + 3); j++){
					count0 = count1 = 0;
					for(i = 0 ; i < qtd_VarRest + 1;i++){
						if(resultados[i][j][k] == 1){
							countAux = i;
							count1++;
						}
						if(resultados[i][j][k]==0){
							count0++;
						}
					}
					if((count1 == 1) && (count0 == qtd_VarRest)){
						if(j >= 4){
							cout << "\tF" << j - 3 << " = " << resultados[countAux][14][k] << endl;
						}else{
							cout << "\tX" << j << " = " << resultados[countAux][14][k] << endl;
						}
					}
				}
				cout << endl << "\tVariaveis nao basicas:" << endl;
				for(j = 1; j < MAX + 2 + 3 - 2; j++){
					count0 = count1 = 0;
					for(i = 0; i < qtd_VarRest + 1; i++){
						if(resultados[i][j][k] == 1){
							countAux = i;
							count1++;
						}
						if(resultados[i][j][k] == 0){
							count0++;
						}
					}
					if((count1 + count0) != (qtd_VarRest + 1)){
						if(j >= 4){
							cout << "\tF" << j - 3 << " = 0" << "\n";
						}else{
							cout << "\tX" << j << " = 0" << "\n";
						}
					}
				}
				cout << endl << "\tZ = " << resultados[0][14][k] << endl <<  endl << "\t";
				system("PAUSE");
			} 
			break;
		case 3:
			cabecalho_padrao();
			cout << endl << "\t***Solucoes Parciais***" << endl << endl;
			for(k = 0; k < qtd_Solucoes; k++){
				cout << endl << "\t" << k + 1 << " Solucao: " << endl << endl;
				//cabeçalho Tabela
				cout << "\t";
				for(j = 0; j < qtd_VarDec + 1; j++){
				      cout << "X" << j + 1 << "    | ";
				}
				for(j = 4; j < qtd_VarRest + 4; j++){
				      cout << "F" << j + 1 << "    | ";
				}				
                cout << "b" << endl;
				
				for(i = 0; i < qtd_VarRest + 1; i++){
					cout << "\t";
					for(j = 0; j < qtd_VarDec + 1; j++){
						cout << resultados[i][j][k] << "    | ";
					}
					for(j = 4; j < qtd_VarRest + 4; j++){
						cout << resultados[i][j][k] << "    | ";
					}
					cout << resultados[i][14][k] << "    | ";
					cout << endl ;
				}
                cout << endl << "\t";
				system("PAUSE");
				cout << endl << endl;
			}
			break;
		default: 
			break;
	}
}
//Funcao para limpar o screen
void limpaTela(){
     system("CLS");
     cout << endl;
}
//Cabecalho padrao do programa
void cabecalho_padrao(){
    limpaTela();
    cout << "\t __________________________________________________________" << endl;
    cout << "\t|                                                          |" << endl;
    cout << "\t|                      METODO SIMPLEX                      |" << endl;
    cout << "\t|                                          Helton - Renato |" << endl;
    cout << "\t|__________________________________________________________|" << endl;
    cout << endl;
}

