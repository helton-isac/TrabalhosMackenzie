#include <cstdlib>
#include <iostream>

#define MAX 10
#define MAX2 50
#define MAX3 100

void cabecalho_parametrizacao();
void calcsimplex(int qtd_decisao, int qtd_restricao, int *qtd_solucoes, float var_decisoes[], float rest_variavel[][4], float resultados[][MAX+2+3][MAX2]);
void calcinteiros(float solucao_otima_simplex[2], int qtd_decisao, int qtd_restricao, int *qtd_solucoes2, float var_decisoes[3], float rest_variavel[][4], float resultados2[][3]);
void calcularinteiros(float solucao_atual[], int verifmenori, int auxverif, int rest_carregadas, float restricoes_carregadas[][3], int qtd_restricao, float var_decisoes[], float rest_variavel[][4], float result_temp[], int *sai_temp);
void exibisolucao(float resultados[][MAX+2+3][MAX2], int qtd_restricao, int qtd_decisao, int qtd_solucoes, int tipo);
void exibisolucao2(float resultados2[][3], int qtd_decisao, int qtd_solucoes2, int tipo);

using namespace std;

int main(int argc, char *argv[])
{
    int qtd_decisao, aux, escolha, qtd_restricao, i, j, qtd_solucoes, qtd_solucoes2, qtdzero, qtdum;
    float var_decisoes[3];
    float rest_variavel[MAX][4];
    float resultados[MAX+1][MAX+2+3][MAX2]={0};
    float resultados2[MAX2][3]={0};
    float solucao_otima_simplex[2]={-1};
    
    cout << "Digite 0 para sair ou 1 para utilizar o Metodo dos Inteiros: ";
    cin >> escolha;
    while (escolha!=0){
          qtd_decisao=qtd_restricao=i=j=qtd_solucoes=0;
          var_decisoes[0]=0;
          var_decisoes[1]=0;
          var_decisoes[2]=0;
          escolha=1;
          system("CLS");
          cabecalho_parametrizacao();
          do {
             cout << "\nDigite quantas variaveis de decisao serao utilizadas (1 - 2): ";
             cin >> qtd_decisao;
          } while (qtd_decisao<=0 || qtd_decisao>=3);
          do {
             cout << "\nDigite quantas restricoes serao utilizadas (maximo de " <<MAX<< "): ";
             cin >> qtd_restricao;
          } while (qtd_restricao<0 || qtd_restricao>MAX);
          cout << "\nDigite as variaveis de decisao da funcao objetivo, na sequencia: ";
          if (qtd_decisao==3){
             cin >> var_decisoes[0];
             cin >> var_decisoes[1];
             cin >> var_decisoes[2];
          }
          if (qtd_decisao==2){
             cin >> var_decisoes[0];
             cin >> var_decisoes[1];
          }
          if (qtd_decisao==1)
             cin >> var_decisoes[0];
          cout << "\n=====> RESTRICOES";
          for (i=0;i<qtd_restricao;i++){
              cout << "\nRestricao "<<i+1<<"\n";
              for (j=0;j<qtd_decisao;j++){
                  if (j==0){
                     cout << "\nDigite o valor da primeira variavel de decisao desta restricao: ";
                     cin >> rest_variavel[i][j];
                  }
                  if (j==1){
                     cout << "\nDigite o valor da segunda variavel de decisao desta restricao: ";
                     cin >> rest_variavel[i][j];
                  }
                  if (j==2){
                     cout << "\nDigite o valor da terceira variavel de decisao desta restricao: ";
                     cin >> rest_variavel[i][j];
                  }
              }
              cout << "\nDigite o valor da variavel basica ( fica apos o sinal de <= ): ";
              cin >> rest_variavel[i][3];              
          }
          calcsimplex(qtd_decisao,qtd_restricao,&qtd_solucoes,var_decisoes,rest_variavel,resultados);
          for (j=1;j<MAX+2+3-2;j++){
             qtdzero=qtdum=0;
             for (i=0;i<qtd_restricao+1;i++){
                 if (resultados[i][j][qtd_solucoes-1]==1){
                    aux=i;
                    qtdum++;
                    }
                 if (resultados[i][j][qtd_solucoes-1]==0)
                    qtdzero++;
             }
             if (qtdum==1 && qtdzero==qtd_restricao)
                if (j==1)
                   solucao_otima_simplex[0]=resultados[aux][14][qtd_solucoes-1];
                if (j==2)
                   solucao_otima_simplex[1]=resultados[aux][14][qtd_solucoes-1];
          }
          resultados2[0][0]=solucao_otima_simplex[0];
          resultados2[0][1]=solucao_otima_simplex[1];
          resultados2[0][2]=resultados[0][14][qtd_solucoes-1];
          calcinteiros(solucao_otima_simplex,qtd_decisao,qtd_restricao,&qtd_solucoes2,var_decisoes,rest_variavel,resultados2);
          while (escolha!=0){
              system("CLS");
              do {
                  cout << "\nSelecione:\n";
                  cout << "\n0 - Sair\n";
                  cout << "\nMetodo Simplex";    
                  cout << "\n1 - Exibir solucao inicial";
                  cout << "\n2 - Exibir todas as solucoes\n3 - Exibir tabelas parciais";
                  cout << "\n4 - Solucao final (otima)\n";
                  cout << "\nMetodo dos Inteiros";
                  cout << "\n5 - Exibir solucao inicial";
                  cout << "\n6 - Exibir todas as solucoes";
                  cout << "\n7 - Solucao final (otima)\n";
                  cin >> escolha;
              } while (escolha<0 || escolha>7);
              switch (escolha){
                     case 1: exibisolucao(resultados,qtd_restricao,qtd_decisao,qtd_solucoes,0);
                             break;
                     case 2: exibisolucao(resultados,qtd_restricao,qtd_decisao,qtd_solucoes,1);
                             break;
                     case 3: exibisolucao(resultados,qtd_restricao,qtd_decisao,qtd_solucoes,2);
                             break;
                     case 4: exibisolucao(resultados,qtd_restricao,qtd_decisao,qtd_solucoes,3);
                             break;
                     case 5: exibisolucao(resultados,qtd_restricao,qtd_decisao,qtd_solucoes,4);
                             break;
                     case 6: exibisolucao2(resultados2,qtd_decisao,qtd_solucoes2,0);
                             break;
                     case 7: exibisolucao2(resultados2,qtd_decisao,qtd_solucoes2,1);
                     default: break;
              }
          }
    }
    return EXIT_SUCCESS;
}

void cabecalho_parametrizacao()
{
     cout << "####################################################\n";
     cout << "#      ======   #* METODO INTEIROS *#   ======     #\n";
     cout << "#               => Parametrizacao <=               #\n";
     cout << "####################################################\n\n";
}

void calcsimplex(int qtd_decisao, int qtd_restricao, int *qtd_solucoes, float var_decisoes[], float rest_variavel[][4], float resultados[][MAX+2+3][MAX2])
{
     int i,j,k,z,g,var_decisao_entra,var_sai,results=1,sai=1;
     int qtdum,qtdzero,disponiveis[3]={0,0,0},otima;
     float aux;

     //Gravando a solução inicial
     for (i=0;i<qtd_restricao+1;i++)
         resultados[i][0][0]=0;
     resultados[0][0][0]=1;
     for (i=1;i<qtd_decisao+1;i++)
         resultados[0][i][0]=(var_decisoes[i-1])*-1;
     for (i=1;i<qtd_restricao+1;i++){
         for (j=1;j<qtd_decisao+1;j++)
             resultados[i][j][0]=rest_variavel[i-1][j-1];
         for (k=4;k<qtd_restricao+4;k++)
             resultados[i][k][0]=0;
         resultados[i][i+3][0]=1;
         resultados[i][14][0]=rest_variavel[i-1][3];
     }
     while (sai!=0){
           otima=1;
           //Verificando quais variaveis de decisão são não basicas
           qtdum=qtdzero=0;
           for (z=1;z<qtd_decisao+1;z++){
               for (g=0;g<qtd_restricao+1;g++){
                   if (resultados[g][z][results-1]==1)
                      qtdum++;
                   if (resultados[g][z][results-1]==0)
                      qtdzero++;
               }
               if (qtdum+qtdzero!=qtd_restricao+1)
                  disponiveis[z-1]=0;
               else disponiveis[z-1]=1;           
           }     
           //Verificando qual variavel entra
           var_decisao_entra = 1;
           for (i=0;i<qtd_decisao;i++)
               if (var_decisoes[i]>var_decisoes[var_decisao_entra-1])
                  if (disponiveis[i]==0)
                     var_decisao_entra = i+1;
           //Verificando qual variavel sai
           aux = resultados[1][14][results-1]/resultados[1][var_decisao_entra][results-1];
           var_sai = 1;
           for (j=2;j<qtd_restricao+2;j++){
               if (resultados[j][14][results-1]/resultados[j][var_decisao_entra][results-1]<0)
                  if ((resultados[j][14][results-1]/resultados[j][var_decisao_entra][results-1])*-1<aux)
                     var_sai = j;
                  else var_sai = var_sai;
               else if (resultados[j][14][results-1]/resultados[j][var_decisao_entra][results-1]<aux)
                         var_sai = j;
           }
           //Alterando a linha pivô
           resultados[var_sai][0][results]=resultados[var_sai][0][results-1]/resultados[var_sai][var_decisao_entra][results-1];
           for (i=1;i<qtd_decisao+1;i++)
               resultados[var_sai][i][results]=resultados[var_sai][i][results-1]/resultados[var_sai][var_decisao_entra][results-1];
           for (i=4;i<qtd_restricao+4;i++)
               resultados[var_sai][i][results]=resultados[var_sai][i][results-1]/resultados[var_sai][var_decisao_entra][results-1];
           resultados[var_sai][14][results]=resultados[var_sai][14][results-1]/resultados[var_sai][var_decisao_entra][results-1];
           //Alterando demais linhas
           for (j=0;j<qtd_restricao+1;j++){
               if (j==var_sai)
                  j=j;
               else {
                    resultados[j][0][results]=(resultados[var_sai][0][results-1]*resultados[j][var_decisao_entra][results-1]*-1)+resultados[j][0][results-1];
                    for (i=1;i<qtd_decisao+1;i++)
                        resultados[j][i][results]=(resultados[var_sai][i][results]*resultados[j][var_decisao_entra][results-1]*-1)+resultados[j][i][results-1];
                    for (i=4;i<qtd_restricao+4;i++)
                        resultados[j][i][results]=(resultados[var_sai][i][results]*resultados[j][var_decisao_entra][results-1]*-1)+resultados[j][i][results-1];
                    resultados[j][14][results]=(resultados[var_sai][14][results]*resultados[j][var_decisao_entra][results-1]*-1)+resultados[j][14][results-1];
               }
           }
           //Verificação da solução ótima
           for (j=1;j<MAX+2+3-2;j++){
                 qtdzero=qtdum=0;
                 for (i=0;i<qtd_restricao+1;i++){
                     if (resultados[i][j][results]==1)
                        qtdum++;
                     if (resultados[i][j][results]==0)
                        qtdzero++;
                 }
                 if (qtdum+qtdzero!=qtd_restricao+1 && resultados[0][j][results]<0)
                    otima=0;
           }
           for (i=1;i<qtd_decisao+1;i++)
                 if (resultados[0][i][results]<0)
                    otima=0;
           if (otima==1)
              sai=0;
           results++;
     }       
     *qtd_solucoes=results;
}

void calcinteiros(float solucao_atual[2], int qtd_decisao, int qtd_restricao, int *qtd_solucoes2, float var_decisoes[3], float rest_variavel[][4], float resultados2[][3])
{
     int i, fila=0, sair=1, voltar=0, guardarimenor[MAX3];
     int auxint, verifmenori, rest_carregadas=0, auxverif, sai_temp, results=1;
     float auxfloat, verif, verifmenor, restricoes_carregadas[MAX3][3]={0};
     float result_temp[3], fila_de_espera[MAX3][2];
     
     while (sair==1){
         //Verifica qual variavel está mais próximo de 0.5  
         if (voltar == 0){//Se não está voltando para verificar a outra parte da árvore
             for (i=0;i!=qtd_decisao;i++){
                 auxint = (int) solucao_atual[i];
                 auxfloat = solucao_atual[i] - auxint;
                 verif = 0.5 - auxfloat;
                 if (verif < 0)
                    verif = verif * (-1);
                 if (verifmenor > verif || i == 0){
                    verifmenor = verif;
                    verifmenori = i;
                 }
             }
         }
         if (verifmenori == 0)
            auxverif = 1;
         else auxverif = 0;
         //Guardando variaveis da outra parte da árvore que será resolvida posteriormente
         if (voltar == 0){
            fila_de_espera[fila][verifmenori] = (((int) solucao_atual[verifmenori])+1);
            fila_de_espera[fila][auxverif] = solucao_atual[auxverif];
            guardarimenor[fila] = verifmenori;
            fila++;
         }
         solucao_atual[verifmenori] = (int) solucao_atual[verifmenori];
         //Carregando novas restrições
         restricoes_carregadas[rest_carregadas][0]=solucao_atual[verifmenori];
         restricoes_carregadas[rest_carregadas][2]=verifmenori;
         if (voltar == 0)
            restricoes_carregadas[rest_carregadas][1]=0;
         else
             restricoes_carregadas[rest_carregadas][1]=1;
         rest_carregadas++;
         result_temp[0]=-1;
         result_temp[1]=-1;
         result_temp[2]=-1;
         calcularinteiros(solucao_atual,verifmenori,auxverif,rest_carregadas,restricoes_carregadas,qtd_restricao,var_decisoes,rest_variavel,result_temp,&sai_temp);
         //Gravando novo resultado
         if (sai_temp!=2){
            resultados2[results][verifmenori]=result_temp[verifmenori];
            resultados2[results][auxverif]=result_temp[auxverif];
            resultados2[results][2]=result_temp[2];
            results++;
         }
         //Continuando na mesma parte da árvore
         if (sai_temp==0){
            solucao_atual[verifmenori]=result_temp[verifmenori];
            solucao_atual[auxverif]=result_temp[auxverif];
            voltar=0;
         }
         //Mudando a linha de resolução (vai para a outra parte da árvore) se ainda
         //tiver algo na fila, caso contrário sai do loop
         if (sai_temp==1 || sai_temp==2){
            if (fila!=0){
                rest_carregadas--;
                fila--;
                solucao_atual[0]=fila_de_espera[fila][0];
                solucao_atual[1]=fila_de_espera[fila][1];
                verifmenori=guardarimenor[fila];
                voltar=1;
            }
            else
                sair=0;
         }
     }
     *qtd_solucoes2=results;
}

void calcularinteiros(float solucao_atual[], int verifmenori, int auxverif, int rest_carregadas, float restricoes_carregadas[][3], int qtd_restricao, float var_decisoes[], float rest_variavel[][4], float result_temp[], int *sai_temp)
{
     int i, auxint, impossivel=0;
     float menorvalor, menor_temp, auxfloat, limiteinferior;
     //Calculando valor da variavel através das restições
     for (i=0;i!=qtd_restricao;i++){
         if (rest_variavel[i][auxverif]!=0){
            menor_temp=(rest_variavel[i][3]-(solucao_atual[verifmenori]*rest_variavel[i][verifmenori]))/rest_variavel[i][auxverif];
            if (menor_temp < menorvalor || i == 0)
               menorvalor = menor_temp;
         }
     }
     //Calculando valor da variavel comparando com as restrições carregadas, se houver
     if (rest_carregadas != 0){
        for (i=0;i!=rest_carregadas;i++){
            if (restricoes_carregadas[i][2] == auxverif){
               menor_temp = restricoes_carregadas[i][0];
               if (restricoes_carregadas[i][1] == 0)
                  if (menor_temp < menorvalor)
                     menorvalor = menor_temp;
               if (restricoes_carregadas[i][1] == 1){
                  if (menor_temp > menorvalor) //não há solução
                     impossivel=1;
                  if (menor_temp < menorvalor && menor_temp < limiteinferior)
                     limiteinferior = menor_temp;
               }
            }
        }
        if (limiteinferior > menorvalor) //não há solução
           impossivel=1;
     }
     if (menorvalor < 0 || impossivel == 1) //não há solução
        *sai_temp = 2;
     //Gravando solução para retornar
     else {
          result_temp[verifmenori]=solucao_atual[verifmenori];
          result_temp[auxverif]=menorvalor;
          result_temp[2]=(var_decisoes[verifmenori]*solucao_atual[verifmenori])+(var_decisoes[auxverif]*menorvalor);
          auxint = (int) menorvalor;
          auxfloat = menorvalor - auxint;
          //Verificando se as variaveis de decisão são inteiros
          if (auxfloat == 0)
             *sai_temp=1;
          else
              *sai_temp=0;
     }
}

void exibisolucao(float resultados[][MAX+2+3][MAX2], int qtd_restricao, int qtd_decisao, int qtd_solucoes, int tipo)
{
     int i, j, k, aux, qtdum, qtdzero;
     i=j=k=aux=qtdum=qtdzero=0;
     system("CLS");
     if (tipo==0){
         cout << "####################################################\n";
         cout << "#      ======   #* METODO SIMPLEX *#   ======      #\n";
         cout << "#               => Solucao Inicial <=              #\n";
         cout << "####################################################\n\n";
         cout << "Variaveis basicas:\n";
         for (j=1;j<MAX+2+3-2;j++){
             qtdzero=qtdum=0;
             for (i=0;i<qtd_restricao+1;i++){
                 if (resultados[i][j][0]==1){
                    aux=i;
                    qtdum++;
                    }
                 if (resultados[i][j][0]==0)
                    qtdzero++;
             }
             if (qtdum==1 && qtdzero==qtd_restricao){
                if (j>=4)
                   cout << "F"<<j-3<<" = " <<resultados[aux][14][0]<<"\n";
                else
                    cout << "X"<<j<<" = " <<resultados[aux][14][0]<<"\n";
             }
         }
         cout << "\nVariaveis nao basicas:\n"; 
         for (j=1;j<MAX+2+3-2;j++){
             qtdzero=qtdum=0;
             for (i=0;i<qtd_restricao+1;i++){
                 if (resultados[i][j][0]==1){
                    aux=i;
                    qtdum++;
                    }
                 if (resultados[i][j][0]==0)
                    qtdzero++;
             }
             if (qtdum+qtdzero!=qtd_restricao+1){
                if (j>=4)
                   cout << "F"<<j-3<<" = 0"<<"\n";
                else
                    cout << "X"<<j<<" = 0"<<"\n";
             }
         }
         cout << "\nZ = "<<resultados[0][14][0]<<"\n"; 
         system("PAUSE");
     }
     
     if (tipo==1){
         cout << "####################################################\n";
         cout << "#      ======   #* METODO SIMPLEX *#   ======      #\n";
         cout << "#               => Todas Solucoes <=               #\n";
         cout << "####################################################\n\n";
         for (k=0;k<qtd_solucoes;k++){
             cout << "\nSolucao "<<k+1<<": \n";
             cout << "Variaveis basicas:\n";
             for (j=1;j<MAX+2+3-2;j++){
                 qtdzero=qtdum=0;
                 for (i=0;i<qtd_restricao+1;i++){
                     if (resultados[i][j][k]==1){
                        aux=i;
                        qtdum++;
                        }
                     if (resultados[i][j][k]==0)
                        qtdzero++;
                 }
                 if (qtdum==1 && qtdzero==qtd_restricao){
                    if (j>=4)
                       cout << "F"<<j-3<<" = " <<resultados[aux][14][k]<<"\n";
                    else
                        cout << "X"<<j<<" = " <<resultados[aux][14][k]<<"\n";
                 }
             }
             cout << "\nVariaveis nao basicas:\n";
             for (j=1;j<MAX+2+3-2;j++){
                 qtdzero=qtdum=0;
                 for (i=0;i<qtd_restricao+1;i++){
                     if (resultados[i][j][k]==1){
                        aux=i;
                        qtdum++;
                        }
                     if (resultados[i][j][k]==0)
                        qtdzero++;
                 }
                 if (qtdum+qtdzero!=qtd_restricao+1){
                    if (j>=4)
                       cout << "F"<<j-3<<" = 0"<<"\n";
                    else
                        cout << "X"<<j<<" = 0"<<"\n";
                 }
             }
         cout << "\nZ = "<<resultados[0][14][k]<<"\n";
         system("PAUSE");
         } 
     }   
     
     if (tipo==2){
        cout << "####################################################\n";
        cout << "#      ======   #* METODO SIMPLEX *#   ======      #\n";
        cout << "#              => Solucoes Parciais <=             #\n";
        cout << "####################################################\n\n";
        cout << "#Apresentado da seguinte forma: Primeira coluna Z, proximas colunas sao\n";
        cout << " as variaveis de decisao, as proximas colunas sao as variaveis de folga e\n";
        cout << " por ultimo a coluna 'b'\n\n";
        for (k=0;k<qtd_solucoes;k++){
             cout << "\n=> Solucao "<<k+1<<": \n\n";
             for (i=0;i<qtd_restricao+1;i++){
                 for (j=0;j<qtd_decisao+1;j++)
                     cout << resultados[i][j][k] <<"     ";
                 for (j=4;j<qtd_restricao+4;j++)
                     cout << resultados[i][j][k] <<"     ";
                 cout << resultados[i][14][k] <<"     ";
                 cout << "\n\n";
             }
             system("PAUSE");
             cout <<"\n\n";
        }
     }
         
     if (tipo==3 || tipo==4){
         if (tipo==3){
            cout << "####################################################\n";
            cout << "#      ======   #* METODO SIMPLEX *#   ======      #\n";
            cout << "#               => Solucao Otima <=                #\n";
            cout << "####################################################\n\n";
         }
         if (tipo==4){
            cout << "####################################################\n";
            cout << "#      ======   #* METODO INTEIROS *#   ======     #\n";
            cout << "#               => Solucao Inicial <=              #\n";
            cout << "####################################################\n\n";
         }
         cout << "Variaveis basicas:\n";
         for (j=1;j<MAX+2+3-2;j++){
             qtdzero=qtdum=0;
             for (i=0;i<qtd_restricao+1;i++){
                 if (resultados[i][j][qtd_solucoes-1]==1){
                    aux=i;
                    qtdum++;
                    }
                 if (resultados[i][j][qtd_solucoes-1]==0)
                    qtdzero++;
             }
             if (qtdum==1 && qtdzero==qtd_restricao){
                if (j>=4)
                   cout << "F"<<j-3<<" = " <<resultados[aux][14][qtd_solucoes-1]<<"\n";
                else
                    cout << "X"<<j<<" = " <<resultados[aux][14][qtd_solucoes-1]<<"\n";
             }
         }
         cout << "\nVariaveis nao basicas:\n"; 
         for (j=1;j<MAX+2+3-2;j++){
             qtdzero=qtdum=0;
             for (i=0;i<qtd_restricao+1;i++){
                 if (resultados[i][j][qtd_solucoes-1]==1){
                    aux=i;
                    qtdum++;
                    }
                 if (resultados[i][j][qtd_solucoes-1]==0)
                    qtdzero++;
             }
             if (qtdum+qtdzero!=qtd_restricao+1){
                if (j>=4)
                   cout << "F"<<j-3<<" = 0"<<"\n";
                else
                    cout << "X"<<j<<" = 0"<<"\n";
             }
         }
         cout << "\nZ = "<<resultados[0][14][qtd_solucoes-1]<<"\n";  
         system("PAUSE");
     } 
}

void exibisolucao2(float resultados2[][3], int qtd_decisao, int qtd_solucoes2, int tipo)
{
     int i, auxint1, auxint2, otimaposicao;
     float auxfloat1, auxfloat2, otimavalor;
     system("CLS");
     if (tipo==0){
         cout << "####################################################\n";
         cout << "#      ======   #* METODO INTEIROS *#   ======     #\n";
         cout << "#               => Todas Solucoes <=               #\n";
         cout << "####################################################\n\n";
         for (i=0;i!=qtd_solucoes2;i++){
             cout << "Solucao "<<i+1;
             cout << "\nX1 = "<<resultados2[i][0];
             if (qtd_decisao>1)
                cout << "\nX2 = "<<resultados2[i][1];
             cout << "\nZ = "<<resultados2[i][2];
             cout << "\n\n";
         }
     }
     if (tipo==1){
         cout << "####################################################\n";
         cout << "#      ======   #* METODO INTEIROS *#   ======     #\n";
         cout << "#                => Solucao Otima <=               #\n";
         cout << "####################################################\n\n";
         otimavalor=0;
         otimaposicao=-1;
         //Verificando qual é a solução ótima (maior Z e variaveis de decisão inteiros)
         for (i=0;i!=qtd_solucoes2;i++){
             auxint1 = (int) resultados2[i][0];
             auxfloat1 = auxint1 - resultados2[i][0];
             auxint2 = (int) resultados2[i][1];
             auxfloat2 = auxint2 - resultados2[i][1];
             if (auxfloat1==0 && auxfloat2==0 && otimavalor<resultados2[i][2]){
                otimaposicao = i;
                otimavalor = resultados2[i][2];
             }
         }
         if (otimaposicao!=-1){
            cout << "X1 = "<<resultados2[otimaposicao][0];
            if (qtd_decisao>1)
               cout << "\nX2 = "<<resultados2[otimaposicao][1];
            cout << "\nZ = "<<resultados2[otimaposicao][2];
         }
         else
             cout << "Nao ha solucao para X1 e X2 inteiros";
         cout << "\n\n";
     }
     system("PAUSE");
}
