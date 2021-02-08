/***************************************************
Introdução a Algoritimos e Programação ----- Noturno
Quarto Exercicio Programa -------------- 1o.Sem.2006
Autor: <Danilo Marques Ribeiro>
       <Helton Isac Torres Galindo>
***************************************************/

#include <stdio.h>   
#include <stdlib.h>  
#include<time.h>     
#define MAX 9        

void zeraMatriz(int m[MAX][MAX]); 
void menuPrincipal(int *opcaoMenu);
void menuJogar(int *numNivel);
void jogo(int numNivel, int m[MAX][MAX], int solucao[MAX][MAX], int *contaJogada); 
void sol(int solucao[MAX][MAX]);
void sorteia (int m[MAX][MAX], int numNivel, int solucao[MAX][MAX]);
int confereTudo(int m[MAX][MAX], int lin, int col, int num);
int confereLinha (int m[MAX][MAX], int linha, int num);
int confereColuna (int m[MAX][MAX], int coluna, int num);
int confereMatriz (int m[MAX][MAX], int coluna, int linha, int num);
void imprime(int m[MAX][MAX]);
void solicitaJogada(int *lin, int *col, int *num, int m[MAX][MAX], int *sent);
void imprimeRegras();
void sudoku(); 
int confereSudoku (int m[MAX][MAX]);
void voceVenceu(int *contaJogada);

int main()
{
   int opcaoMenu, numNivel, fim, contaJogada;
   int m[MAX][MAX]={0}, solucao[MAX][MAX]={0};
   do{
      zeraMatriz(m);
      opcaoMenu = numNivel = fim = 0;
      srand (time(NULL));
      sudoku();
      menuPrincipal(&opcaoMenu);
      switch (opcaoMenu){
         case 1:  menuJogar(&numNivel); 
                  jogo(numNivel, m, solucao, &contaJogada); 
                  break;
         case 2:  imprimeRegras(); break;  
         case 3:  printf("\n\n\t\t\t\t  VOLTE SEMPRE...\n\n\t\t");fim = 1; break;
         default: printf("\n\nERRO DESCONHECIDO\n\n"); system ("PAUSE"); 
                  return 0;
      }
   }while (fim == 0);
   system ("PAUSE");             
   return 0;
}

void zeraMatriz(int m[MAX][MAX])
{
   int i, j;
   for (i=0; i<MAX; i++)
        for (j=0; j<MAX; j++)
             m[i][j]=0;     
}

void menuPrincipal(int *opcaoMenu)
{
  do{
     printf ("\n\t\t_________________________________________________  ");                       
     printf ("\n\n\t\t\t\t  MENU PRINCIPAL:\n");
     printf ("\n\t\t1----JOGAR");
     printf ("\n\t\t2----REGRAS");     
     printf ("\n\t\t3----SAIR");     
     printf ("\n\n\n");
     printf ("\t\tDigite sua opcao: ");
     scanf ("%d", &*opcaoMenu);
  }while (*opcaoMenu < 1 || *opcaoMenu > 3);
}

void menuJogar(int *numNivel)
{
     int opcao;
     printf ("\n\t\t_________________________________________________  ");
     printf ("\n\n\t\tSelecione o nivel do Jogo: \n\n");
     printf ("\t\t1----Facil\n");
     printf ("\t\t2----Medio\n");     
     printf ("\t\t3----Dificil\n\n");     
     printf ("\t\tDigite o nivel desejado: ");
     scanf ("%d", &opcao);
     switch (opcao) {
         case 1: *numNivel = 50; break;
         case 2: *numNivel = 25; break;
         case 3: *numNivel = 15; break;
         default: printf("Jogo Encerrado"); return;
     }
}

void jogo(int numNivel, int m[MAX][MAX], int solucao[MAX][MAX], int *contaJogada)
{
     int lin, col, num, sent;
     sol(solucao);
     sorteia(m, numNivel, solucao);
     *contaJogada = 0;
     do{
        sent = 1;
        sudoku();
        imprime (m);
        solicitaJogada(&lin, &col, &num, m, &sent);
        *contaJogada +=1;
        if (sent == 0){
            printf("\n\n\n\n\n\t\t"); break;
        }
        if (num == solucao[lin-1][col-1])
            m[lin-1][col-1]=num;
        else
            if (confereTudo(m, lin-1, col-1, num)){
                printf("\n\n\n\n\n\t\tERRO de LOGICA\n\n\t\t");
                system("PAUSE");
            }
        if(confereSudoku(m)){
           voceVenceu(contaJogada); 
           sent = 0;
        }
     }while(sent == 1);
}

void sol(int solucao[MAX][MAX])
{
 int i, j, sol;
 sol = rand()%10+1;
 int sol1[MAX][MAX] =  {{5,4,2,6,9,8,7,3,1},
                        {1,3,7,5,4,2,9,6,8},
                        {6,8,9,1,3,7,2,4,5},
                        {2,1,4,3,5,6,8,9,7},
                        {9,5,6,8,7,4,1,2,3},
                        {3,7,8,2,1,9,4,5,6},
                        {7,2,1,4,6,5,3,8,9},
                        {4,6,3,9,8,1,5,7,2},
                        {8,9,5,7,2,3,6,1,4}};
 int sol2[MAX][MAX] =  {{9,1,5,8,6,3,4,2,7},
                        {6,2,3,5,4,7,1,9,8},
                        {8,4,7,9,1,2,5,3,6},
                        {1,8,9,6,2,5,7,4,3},
                        {4,3,6,7,9,8,2,5,1},
                        {7,5,2,1,3,4,6,8,9},
                        {2,6,1,4,8,9,3,7,5},
                        {3,7,8,2,5,1,9,6,4},
                        {5,9,4,3,7,6,8,1,2}};
 int sol3[MAX][MAX] =  {{9,6,3,1,7,4,2,5,8},
                        {1,7,8,3,2,5,6,4,9},
                        {2,5,4,6,8,9,7,3,1},
                        {8,2,1,4,3,7,5,9,6},
                        {4,9,6,8,5,2,3,1,7},
                        {7,3,5,9,6,1,8,2,4},
                        {5,8,9,7,1,3,4,6,2},
                        {3,1,7,2,4,6,9,8,5},
                        {6,4,2,5,9,8,1,7,3}};
 int sol4[MAX][MAX] =  {{1,3,7,6,5,8,4,9,2},
                        {2,4,5,3,9,7,6,1,8},
                        {8,6,9,1,4,2,7,5,3},
                        {6,2,8,5,7,9,3,4,1},
                        {3,7,1,8,6,4,9,2,5},
                        {5,9,4,2,1,3,8,6,7},
                        {7,5,2,4,8,6,1,3,9},
                        {4,8,3,9,2,1,5,7,6},
                        {9,1,6,7,3,5,2,8,4}};
 int sol5[MAX][MAX] =  {{1,5,3,2,8,7,4,6,9},
                        {2,4,6,5,9,3,7,8,1},
                        {7,8,9,6,4,1,5,3,2},
                        {9,1,8,3,7,5,6,2,4},
                        {4,2,7,9,1,6,8,5,3},
                        {6,3,5,8,2,4,1,9,7},
                        {3,7,2,4,6,8,9,1,5},
                        {8,9,4,1,5,2,3,7,6},
                        {5,6,1,7,3,9,2,4,8}};
 int sol6[MAX][MAX] =  {{6,4,3,2,5,7,9,1,8},
                        {8,9,1,6,3,4,7,5,2},
                        {7,2,5,1,8,9,3,4,6},
                        {2,1,7,5,4,6,8,3,9},
                        {5,3,6,7,9,8,1,2,4},
                        {9,8,4,3,2,1,6,7,5},
                        {4,7,9,8,1,2,5,6,3},
                        {1,5,8,4,6,3,2,9,7},
                        {3,6,2,9,7,5,4,8,1}};
 int sol7[MAX][MAX] =  {{1,4,7,3,5,6,2,8,9},
                        {9,2,6,1,4,8,5,3,7},
                        {3,5,8,9,7,2,6,1,4},
                        {4,8,3,2,6,5,9,7,1},
                        {2,7,9,4,1,3,8,6,5},
                        {5,6,1,7,8,9,4,2,3},
                        {6,3,4,8,9,1,7,5,2},
                        {7,1,5,6,2,4,3,8,9},
                        {8,9,2,5,3,7,1,4,6}};
 int sol8[MAX][MAX] =  {{4,7,8,9,1,2,5,3,6},
                        {5,6,9,3,4,7,1,8,2},
                        {1,2,3,6,8,5,4,9,7},
                        {9,3,1,5,7,4,6,2,8},
                        {2,4,7,8,3,6,9,5,1},
                        {8,5,6,1,2,9,7,4,3},
                        {6,8,5,2,9,1,3,7,4},
                        {7,9,2,4,6,3,8,1,5},
                        {3,1,4,7,5,8,2,6,9}};
 int sol9[MAX][MAX] =  {{7,8,5,9,1,4,2,6,3},
                        {4,3,2,7,6,8,5,9,1},
                        {1,6,9,2,3,5,7,4,8},
                        {5,4,7,8,9,3,1,2,6},
                        {8,2,1,5,7,6,9,3,4},
                        {6,9,3,1,4,2,8,5,7},
                        {9,7,4,3,5,1,6,8,2},
                        {2,5,6,4,8,7,3,1,9},
                        {3,1,8,6,2,9,4,7,5}};
 int sol10[MAX][MAX] = {{4,5,7,8,6,1,9,2,3},
                        {8,2,9,3,7,4,5,6,1},
                        {6,1,3,2,9,5,7,8,4},
                        {3,4,5,7,1,6,8,9,2},
                        {7,8,6,9,4,2,3,1,5},
                        {2,9,1,5,8,3,6,4,7},
                        {9,6,2,1,3,7,4,5,8},
                        {5,7,4,6,2,8,1,3,9},
                        {1,3,8,4,5,9,2,7,6}};
                           
 switch (sol){
  case 1: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol1[i][j];break;
  case 2: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol2[i][j];break;
  case 3: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol3[i][j];break;
  case 4: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol4[i][j];break;
  case 5: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol5[i][j];break;
  case 6: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol6[i][j];break;
  case 7: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol7[i][j];break;
  case 8: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol8[i][j];break;
  case 9: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol9[i][j];break;
  case 10: for(i=0;i<MAX;i++) for(j=0;j<MAX;j++) solucao[i][j]=sol10[i][j];break;
 }
}

void sorteia (int m[MAX][MAX], int numNivel, int solucao[MAX][MAX])
{
     int i, j, lin, col;
     for(i=0; i<numNivel; i++){
         lin = rand()%9;
         col = rand()%9;
         if(m[lin][col] == 0)
            m[lin][col] = solucao[lin][col];
         else i--;
     }
}

int confereTudo(int m[MAX][MAX], int lin, int col, int num)
{
  int aux, erroMatriz, erroLinha, erroColuna;
     aux = erroMatriz = erroLinha = erroColuna = 1;
     if(confereMatriz(m, col, lin, num));
     else{ 
        aux = erroMatriz = 0;
     }
     if(confereLinha(m, lin, num));
     else{ 
        aux = erroLinha = 0;
     }
     if(confereColuna(m, col, num));
     else{  
        aux = erroColuna = 0;
     }
     if (aux == 0){
         printf ("\n\t\t_________________________________________________  ");
         printf ("\n\n\t\t      FORAM ENCONTRADOS OS SEGUINTES ERROS:\n");
         if(erroMatriz == 0)
            printf("\n\t\tERRO NA SUBMATRIZ (3X3)...");
         if(erroLinha == 0)
            printf("\n\t\tERRO NA LINHA...");
         if(erroColuna == 0)
            printf("\n\t\tERRO NA COLUNA...");
         printf ("\n\t\t_________________________________________________  ");            
         printf ("\n\n\n\t\t");                        
         system ("PAUSE");
         
     }
     return (aux);
}              

int confereLinha (int m[MAX][MAX], int linha, int num)
{
     int i;
     for (i = 0; i < MAX; i++)
          if (m[linha][i] == num)
              return 0;
     return (1);    
}
     
int confereColuna (int m[MAX][MAX], int coluna, int num)
{
     int i;
     for (i = 0; i < MAX; i++)
          if (m[i][coluna] == num)
              return 0;
     return (1);    
}

int confereMatriz (int m[MAX][MAX], int coluna, int linha, int num)
{
     int i, j, aux1, aux2, lin, col;         
     switch (linha / 3){                     
            case 0: lin = 0; break;          
            case 1: lin = 3; break;          
            case 2: lin = 6; break;
            default: printf ("\nERRO DESCONHECIDO\n"); system("PAUSE"); return -1;   
     }                                                                            
     switch (coluna / 3){                                                         
            case 0: col = 0; break;                                               
            case 1: col = 3; break;                                               
            case 2: col = 6; break;                                               
            default: printf ("\nERRO DESCONHECIDO\n"); system("PAUSE"); return -1;   
     }                                                                            
     aux1 = lin + 3;                                                              
     aux2 = col + 3;                         
     for(i = lin; i < aux1; i++){            
          for(j = col; j < aux2; j++){       
              if (m[i][j] == num)
                  return (0);
          }
     }
     return (1);
}

void imprime(int m[MAX][MAX])
{
   int i, j, z;
   printf ("\n\t\t_________________________________________________  ");
   printf ("\n\n\t\t        ");
   for (i=0;i < MAX; i++){
        if (i == 2 || i == 5 || i == 8 )
            printf ("%d    ", i+1);
        else printf ("%d   ", i+1);
   }
   printf ("\n");
   for (i=0;i < MAX; i++){
        if (i == 0 || i == 3 || i == 6 || i == 9){
            printf ("\n\t\t     ");            
            for (j=0;j < 41; j++)
                 printf ("X");
        }
        printf ("\n\t\t  %d  XX ", i+1);
        for (z=0; z<MAX; z++){
             if (z == 2 || z == 5 || z == 8){
                 if(m[i][z] == 0)
                    printf ("  XX ");
                 else printf ("%d XX ", m[i][z]); 
             }
             else{ 
                  if(m[i][z] == 0)
                     printf ("  I ");
                  else printf ("%d I ", m[i][z]);
             }
        }
   }
   printf ("\n\t\t     ");            
   for (i=0;i < 41; i++)
        printf ("X");
   printf ("\n\n\t\t\t");
}

void solicitaJogada(int *lin, int *col, int *num, int m[MAX][MAX], int *sent)
{
 int aux;
 do{
   do{
     printf ("\n\t\t_________________________________________________  ");                     
     printf("\n\n\t\tDigite 0 para sair ou 1 para continuar: ");
     scanf ("%d", sent);
     if(*sent==0){
      printf ("\n\t\t_________________________________________________  ");                              
      printf("\n\n\t\tDeseja realmente Sair?\n");
      printf("\t\tDigite 0 para Sim e 1 para Nao: ");
      scanf ("%d", sent);         
     }
   }while(*sent < 0 || *sent > 1);
   if (*sent == 0)
       return;
   aux = 1;
   printf ("\n\t\t_________________________________________________\n");               
   printf("\n\t\tDigite a Linha desejada: ");
   scanf ("%d", lin);
   printf("\n\t\tDigite a Coluna desejada: ");
   scanf ("%d", col);     
   printf("\n\t\tDigite o Numero desejado: ");
   scanf ("%d", num);
   if (*lin<1 || *lin>9 || *col<1 || *col>9 || *num<1 || *num>9){
     printf("\n\t\t_________________________________________________\n");                             
     printf("\n\t\t Digite apenas numeros de 1 a 9. Tente novamente\n\n\n\t\t");
     system("PAUSE");
     printf("\n\n");
     imprime (m);
     aux = 0;
   }
 }while(aux == 0);
}

void imprimeRegras()
{
     printf("\n\t\t----------------------REGRAS-----------------------\n");
     printf("\n\t\tSudoku e um jogo de logica cujo objetivo e"); 
     printf("\n\t\tpreencher as celulas vazias com numeros entre 1 e 9" );
     printf("\n\t\tde forma que cada numero apareca uma unica vez");
     printf("\n\t\tem cada coluna, linha e subMatriz 3x3.\n");
     printf("\n\t\t---------------------------------------------------\n\n");
     printf("\t\t");
     system("PAUSE");
}

void sudoku()
{
     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");    
     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");              
     printf ("\n\t\t XXXXX  XX  XX  XXXXXX    XXXXX   XX  XX  XX  XX   ");
     printf ("\n\t\tXX      XX  XX  XX   XX  XX   XX  XX XX   XX  XX   ");     
     printf ("\n\t\t XXXX   XX  XX  XX   XX  XX   XX  XXXX    XX  XX   ");
     printf ("\n\t\t    XX  XX  XX  XX   XX  XX   XX  XX XX   XX  XX   ");
     printf ("\n\t\tXXXXX    XXXX   XXXXXX    XXXXX   XX  XX   XXXX  \n");     
     printf ("\n\t\t             TESTE O SEU RACIOCINIO                ");
}

int confereSudoku (int m[MAX][MAX])
{
   int i, j;
   for (i=0; i<MAX; i++)
        for (j=0; j<MAX; j++)
             if (m[i][j] == 0)
                 return (0);
   return (1);
}

void voceVenceu(int *contaJogada)
{
     printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");    
     printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");    
     printf ("\n\t\t                                    xx              ");
     printf ("\n\t\t                                   x  x             ");
     printf ("\n\t\t        XX    XX  XXXXXX  XXXXXX  XXXXXX            ");
     printf ("\n\t\t         XX  XX   XX  XX  XX      XX                ");
     printf ("\n\t\t         XX  XX   XX  XX  XX      XXXX              ");
     printf ("\n\t\t          XXXX    XX  XX  XX      XX                ");
     printf ("\n\t\t           XX     XXXXXX  XXXXXX  XXXXXX            ");
     printf ("\n\t\t                                                    ");
     printf ("\n\t\tXX    XX  XXXXXX  XX   XX  XXXXXX  XXXXXX  XX  XX   ");
     printf ("\n\t\t XX  XX   XX      XXX  XX  XX      XX      XX  XX   ");
     printf ("\n\t\t XX  XX   XXXX    XX X XX  XX      XXXX    XX  XX   ");
     printf ("\n\t\t  XXXX    XX      XX  XXX  XX      XX      XX  XX   ");
     printf ("\n\t\t   XX     XXXXXX  XX   XX  XXXXXX  XXXXXX  XXXXXX   ");
     printf ("\n\n\t\t                   COM %d JOGADAS", *contaJogada);
     printf ("\n\n\n\n\t\t");
     system ("PAUSE");
}
