/***************************************************
Introdução a Algoritimos e Programação ----- Noturno
Quarto Projeto  ------------------------ 1o.Sem.2006
Autor: <Renato Ribeiro Pedrosa>
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>  
# define MAX 9

void dificuldade(int *num);
void selecionajogo(int m1[][MAX], int m2[][MAX]);
void esconde(int m1[][MAX], int *num);
void imprime(int m1[][MAX]);
void jogo(int m1[][MAX], int m2[][MAX]);
int linha(int num, int lin, int m[][MAX]);
int coluna(int num, int col, int m[][MAX]);
int caixa(int num, int col, int lin, int m[][MAX]);
void fim(int m[][MAX], int *num);

main()
{
    srand (time(NULL));
    int num, m1[MAX][MAX]={0}, m2[MAX][MAX]={0};
    dificuldade(&num);
    if(num == 0)
       return (0);
    selecionajogo(m1, m2);
    esconde(m1, &num);
    imprime(m1);
    jogo(m1, m2);
    if(m1[1][1]==10)
       return 0;
    system("PAUSE");	
    return 0;
}

  void dificuldade(int *num)
{
  int sel;
  do{
      printf("\n\n##############  MENU  ################\n\n");
      printf("\n1 - Novo Jogo; ");
      printf("\n2 - Regra; ");
      printf("\n3 - Sair; \n");
      printf ("\nO que deseja fazer: ");
      scanf("%d", &sel);
  }while (sel<1 || sel>3);
  switch (sel){
        case 1:
              printf("\n\n##############  NIVEL  ################\n\n");
              printf ("1 - Peace of Cake\n");
              printf ("2 - Let's Rock\n");     
              printf ("3 - Extreme!!\n");     
              do{
                printf ("\nEscolha o nivel: ");
                scanf ("%d", num);
              }while(*num<1 || *num>3);
             if (*num == 1){
               *num = 20; break;
             }
             else if (*num == 2){
                   *num = 35; break;
                  }
                  else{
                     *num = 60; break;
                  }
        case 2: 
           printf("\n##############  REGRAS  #################\n");
           printf("\nSelecione uma posicao para colocar um numero de 1 a 9,"); 
           printf("\nO Jogo so aceita \"Jogadas Validas\", ou seja:");
           printf("\nO numero nao podera se repetir na linha, coluna ou caixa");
           printf("\nAlgumas jogadas sao consideradas Invalidas, pois");
           printf("\no jogo ficaria sem solucao em uma jogada posterior");
           printf("\n\nBOA SORTE!!!\n\n");
           system("PAUSE");
           main();
           *num = 0;
           return;
        case 3:
            printf("\n\nEspero que tenha se divertido\n\n");
            system("PAUSE");
            *num = 0;
            return;
     }  
}
  
void selecionajogo(int m1[MAX][MAX], int m2[MAX][MAX])
{
  int i, j, jogo;
  jogo = rand()%3+1;
  int jogo1[MAX][MAX] =  {{9,6,3,1,7,4,2,5,8},
                          {1,7,8,3,2,5,6,4,9},
                          {2,5,4,6,8,9,7,3,1},
                          {8,2,1,4,3,7,5,9,6},
                          {4,9,6,8,5,2,3,1,7},
                          {7,3,5,9,6,1,8,2,4},
                          {5,8,9,7,1,3,4,6,2},
                          {3,1,7,2,4,6,9,8,5},
                          {6,4,2,5,9,8,1,7,3}};
                        
  int jogo2[MAX][MAX] =  {{1,3,7,6,5,8,4,9,2},
                          {2,4,5,3,9,7,6,1,8},
                          {8,6,9,1,4,2,7,5,3},
                          {6,2,8,5,7,9,3,4,1},
                          {3,7,1,8,6,4,9,2,5},
                          {5,9,4,2,1,3,8,6,7},
                          {7,5,2,4,8,6,1,3,9},
                          {4,8,3,9,2,1,5,7,6},
                          {9,1,6,7,3,5,2,8,4}};
                        
  int jogo3[MAX][MAX] =  {{4,7,8,9,1,2,5,3,6},
                          {5,6,9,3,4,7,1,8,2},
                          {1,2,3,6,8,5,4,9,7},
                          {9,3,1,5,7,4,6,2,8},
                          {2,4,7,8,3,6,9,5,1},
                          {8,5,6,1,2,9,7,4,3},
                          {6,8,5,2,9,1,3,7,4},
                          {7,9,2,4,6,3,8,1,5},
                          {3,1,4,7,5,8,2,6,9}};
                           
 if (jogo == 1)
   for(i=0;i<MAX;i++) 
    for(j=0;j<MAX;j++){ 
            m1[i][j] = jogo1[i][j];
            m2[i][j] = jogo1[i][j];
            }
  else if (jogo == 2)
        for(i=0;i<MAX;i++) 
           for(j=0;j<MAX;j++){ 
            m1[i][j] = jogo2[i][j];
            m2[i][j] = jogo2[i][j];
            }
       else   
          for(i=0;i<MAX;i++)
            for(j=0;j<MAX;j++){ 
            m1[i][j] = jogo3[i][j];
            m2[i][j] = jogo3[i][j];
            }
}  

void esconde(int m1[MAX][MAX], int *num)
{
   int i, linha, coluna;
   for(i=0; i<=*num; i++){
          linha = rand()%9;
          coluna = rand()%9;
          m1[linha][coluna] = 0;
   }                      
}

void imprime(int m1[MAX][MAX])
{ 
  int i,j;
  printf("\n\n    0  1  2   3  4  5   6  7  8");
  printf("\n  +---------+---------+---------+\n");
  for (i = 0; i < MAX; i++){
    printf("%d |", i);
    for (j = 0; j < MAX; j++){
      if (m1[i][j] != 0)
         printf(" %d ", m1[i][j]);
      else
    	 printf("   ");
      if (j % 3 == 2) 
	      printf("|");
    }
    if (i % 3 == 2)
        printf("\n  +---------+---------+---------+");
    printf("\n");
  }
  printf ("\n\n");
}

void jogo(int m1[MAX][MAX], int m2[MAX][MAX])
{      
   int num,lin, col, i, j, z, end=1;
   do{
      printf("Digite o numero 10 na Linha para sair do jogo");                    
      do{
         printf("\n\nDigite a Linha desejada(0-8): ");
         scanf ("%d", &lin);
         if (lin == 10)
             break;
      }while(lin<0 || lin>8);
      if (lin == 10){
          main();
          m1[1][1]=10;
          return;
      }
      do{          
      printf("\n\nDigite a Coluna desejada(0-8): ");
      scanf ("%d", &col);     
      }while(col<0 || col>8);      
      do{      
      printf("\n\nDigite o Numero desejado: ");
      scanf ("%d", &num);
      }while(num<1 || num>9);      
      if (num == m2[lin][col]){
          m1[lin][col] = num;
          fim(m1, &end);
          if (end == 0){
              imprime(m1);
              printf("PARABENS! VOCE CONCLUIU O SUDOKU!\n\n");
              system("PAUSE");
              main();
              m1[1][1]=10;
              return;
          }  
          printf("\n\nContinue...\n\n");
          system("PAUSE");          
          imprime(m1);
      }
      else{     
          printf("\n\n############  JOGADA INVALIDA  ############\n\n");             
          if(linha(num, lin, m1)==0)
             printf("\nNumero Repetido na Linha!\n");
          if(coluna(num, col, m1)==0)
             printf("\nNumero Repetido na Coluna!\n");           
          if(caixa(num, col, lin, m1)==0)          
             printf("\nNumero Repetido dentro da Caixa!\n");
          printf("\n\n###########################################\n\n");
          system("PAUSE");
          printf("\n\n");
          imprime(m1);
      }
   }while(lin != 10);
   printf ("\n");
}
int linha(int num, int lin, int m[][MAX])
{
     int i;
     for (i = 0; i < MAX; i++)
          if (m[lin][i] == num)
              return (0);
     return (1);    
}
     
int coluna(int num, int col, int m[][MAX])
{
     int i;
     for (i = 0; i < MAX; i++)
          if (m[i][col] == num)
              return (0);
     return (1);    
}

int caixa(int num, int col, int lin, int m[][MAX])
{
     int i, j;         
     switch (lin / 3){                     
            case 0: lin = 0; break;          
            case 1: lin = 3; break;          
            case 2: lin = 6; break;
     }                                                                            
     switch (col / 3){                                                         
            case 0: col = 0; break;                                               
            case 1: col = 3; break;                                               
            case 2: col = 6; break;                                               
     }                                                                            
     for(i = lin; i < lin+3; i++){            
          for(j = col; j < col+3; j++){       
              if (m[i][j] == num)
                  return (0);
          }
     }
     return (1);
}
void fim(int m[][MAX], int *num)
{
  int i, j, aux=0;
  for (i=0; i<MAX; i++)
     for (j=0; j<MAX; j++)
        if (m[i][j] == 0){
          aux = 1;  
          break;
        }
  if (aux==0)
     *num =0;
}
