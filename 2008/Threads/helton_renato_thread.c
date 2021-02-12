/*********************************************
** Helton Isac Torres Galindo     3068645-8 **
** Renato Ribeiro Pedrosa         3062961-6 **
**                                          **
** SISTEMAS OPERACIONAIS 5°N                **
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//Tempo minimo da função que simula o sleep
#define TEMPO 200000000

void CaseOpcoes();//Switch para as opções disponíveis.
int MenuInicial();//Exibe o menu com as opções a serem escolhidas pelo usuário
void Parametrizacao();//Solicita, recebe, valida e armazena os parametros necessario
void VerificarParametros();//Exibe os Parametros que foram inseridos pelo usuário
void ExecutarThreads();//Executa a Thread Geradora 
void *GerarComerciantes(void *arg);//Rotina da Thread Geradora
void *AtravessarPonteEsqDir(void *arg);//Rotina do comerciante que atravessa da Esq para a Dir
void *AtravessarPonteDirEsq(void *arg);//Rotina do comerciante que atravessa da Dir para a Esq
void ExibeMsg(int pintMessage);//Exibe Mensagens provenientes das Threads
int CriarOuNaoCriar();//Retorna 1 como true e 0 como false para auxiliar na criação de threads
int CriarEsqOrDir();//Cria comerciantes que entrarão pela esquerda(1), direita(2), finaliza(0)
void breveHistoriaCivilizacao();//Trama do programa sequência copiada do arquivo PDF do Moodle
void PassaTempo(int tempo);//Rotina para simular o sleep


//Variaveis Globais de controle do programa
int gQtdComerciantes, gQtdComerciantes_aux, gProbabilidade;
int gQtdEsquerdas, gQtdDireitas, gQtdEsq, gQtdDir;
//Threads
int gThrComerciantes, gThrGeradora;
//Semáforos
pthread_mutex_t  semPonte, semMsg; 

/*
	Função Main
*/
int main(){
	//Inicializa a semente do Randomico
	srand(time(NULL));
	//Inicializa o valor da qtd de comerciantes
	gQtdComerciantes = 0;
	//Chama a rotina que ficara em loop até que seja solicitado
	//a opção sair
    CaseOpcoes();
	//Sai do programa
    return 0;
}
/*
	Switch para as opções disponíveis.
*/
void CaseOpcoes(){
     int escolha;
     int sair = 0;
	 //Repete até que seja solicitado pelo usuario a opção 5
     do{          
		 //Solicita uma opção do usuário
         escolha = MenuInicial();
         switch(escolha){
             case 1://Historia do algoritmo
                  breveHistoriaCivilizacao();
                  break;
             case 2://Recebe os parametros necessarios
                  Parametrizacao();
                  break;
             case 3://Exibe os parametros armazenados
                  VerificarParametros();              
                  break;
             case 4://Executa a thread Geradora
                  ExecutarThreads();              
                  break;                  
             case 5://Abandona o programa
                  sair = 1;
                  break;                                                        
         }
     }while(sair == 0);
}
/*
	Exibe o menu com as opções a serem escolhidas pelo usuário
*/
int MenuInicial(){
     int escolha;
     int sair = 0;
     do{
         system("CLS");
         printf("\n");         
         printf("********************************************************************\n");
         printf("**** ** ** ** ** ** ** ** * MENU INICIAL * ** ** ** ** ** ** ** ****\n");
         printf("********************************************************************\n");
         printf("* 1 - Breve Introducao                                             *\n");
         printf("* 2 - Parametrizacao                                               *\n");
         printf("* 3 - Verificar Parametros                                         *\n");
         printf("* 4 - Executar                                                     *\n");     
         printf("* 5 - Sair                                                         *\n");          
         printf("********************************************************************\n");         
         printf("*Escolha uma opcao: ");
         scanf("%d",&escolha);
         if(escolha < 1 || escolha > 5){
              printf("\n\n");
              printf("                  ********************************\n");                    
              printf("                  * Parametro Incorreto!!!       *\n");                    
              printf("                  * Por favor tente novamente.   *\n");                    
              printf("                  ********************************\n\n");                    
              printf("                  ");
              system("PAUSE");
         }else{
              sair = 1;
         }
     }while(sair == 0);
     return escolha;
}
/*
	Solicita, recebe, valida e armazena os parametros necessario
*/
void Parametrizacao(){
     system("CLS");
     printf("\n");
     printf("********************************************************************\n");
     printf("**** ** ** ** ** ** ** **  PARAMETRIZACAO  ** ** ** ** ** ** ** ****\n");
     printf("********************************************************************\n");     
     do{
        printf("* Quantidade de Comerciantes.......: ");
        scanf("%d",&gQtdComerciantes);
        if(gQtdComerciantes <= 0) 
           printf("\nERRO: O valor esperado devera ser um inteiro positivo\n\n");
     }while(gQtdComerciantes <= 0);
     printf("********************************************************************\n");          
     do{
        printf("* Probabilidade (0 a 100)..........: ");
        scanf("%d",&gProbabilidade);
        if(gProbabilidade < 0 || gProbabilidade > 100) 
           printf("\nERRO: O valor esperado devera estar entre 0 e 100\n\n");
     }while(gProbabilidade < 0 || gProbabilidade > 100);
     printf("********************************************************************\n");          
     printf("* Dados inseridos com sucesso                                      *\n");               
	 //Dividindo comerciantes para esquerda e direita   
	 //Para somente 1
	 if(gQtdComerciantes == 1){
	    gQtdEsquerdas = 1;
	    gQtdDireitas = 0;
     }else{
 	    //Para uma quantidade par
        if(gQtdComerciantes % 2 == 0){
		    gQtdEsquerdas = gQtdComerciantes / 2;
		    gQtdDireitas = gQtdComerciantes / 2;
	    //Para uma quantidade impar maior que 1
		}else{
            gQtdEsquerdas = gQtdComerciantes / 2 + 1;
		    gQtdDireitas = gQtdComerciantes / 2;
        }
     }
     gQtdEsq = gQtdEsquerdas;
	 gQtdDir = gQtdDireitas;
     printf("* Quantidade de Comerciantes TOTAL...: %d\n",gQtdComerciantes);
     printf("* Comerciantes do lado Esquerdo......: %d\n",gQtdEsq);
     printf("* Comerciantes do lado Direito.......: %d\n",gQtdDir);
     printf("* Probabilidade......................: %d%%\n",gProbabilidade);
     printf("********************************************************************\n");               
     printf("\n");
     system("PAUSE");
     system("CLS");     
}
/*
	Exibe os Parametros que foram inseridos pelo usuário
*/
void VerificarParametros(){
	 if(gQtdComerciantes==0){
	      printf("\n\n");
	      printf("                  ********************************\n");                    
	      printf("                  * Os parametros ainda nao foram*\n");                    
	      printf("                  * preenchidos                  *\n");                    	      
	      printf("                  ********************************\n\n");                    
	      printf("                  ");
	      system("PAUSE");	    
     }else{
	     system("CLS");
	     printf("\n");
	     printf("********************************************************************\n");
	     printf("**** ** ** ** ** ** ** ** ** PARAMETROS ** ** ** ** ** ** ** ** ****\n");
	     printf("********************************************************************\n");     	 
	     printf("* Quantidade de Comerciantes TOTAL...: %d\n",gQtdComerciantes);
	     printf("* Comerciantes do lado Esquerdo......: %d\n",gQtdEsq);
	     printf("* Comerciantes do lado Direito.......: %d\n",gQtdDir);
	     printf("* Probabilidade......................: %d%%\n",gProbabilidade);
	     printf("********************************************************************\n");               
	     printf("\n");
	     system("PAUSE");
	     system("CLS");	 
	 }
}
/*
	Executa a Thread Geradora caso os parametros 
	tenham sido preenchidos corretamente
*/
void ExecutarThreads(){
	 int idGeradora[1]; 
     pthread_t thrGeradora;
     //Verifica se os parametros foram preenchidos corretamente
	 if(gQtdComerciantes==0){
	      printf("\n\n");
	      printf("                  ********************************\n");                    
	      printf("                  * Os parametros ainda nao foram*\n");                    
	      printf("                  * preenchidos                  *\n");                    	      
	      printf("                  ********************************\n\n");                    
	      printf("                  ");
	      system("PAUSE");	    
     }else{
	     idGeradora[0]=0;//Id da Thread geradora
		 //Inicializa Semaforos
		 pthread_mutex_init(&semPonte, NULL);
		 pthread_mutex_init(&semMsg, NULL);     
		 //Restaura os valores das quantidades de comerciantes
		 //a serem criados
	     gQtdEsquerdas = gQtdEsq;
		 gQtdDireitas = gQtdDir;
		 system("CLS");
		 //Cria a thread geradora
	     pthread_create (&thrGeradora, NULL, GerarComerciantes, &idGeradora[0]);
		 //Aguarda a finalização da thread geradora
	     pthread_join(thrGeradora,NULL);
		 //Exibe Mensagem
		 ExibeMsg(6);
	 }
}
/*
	Rotina da Thread Geradora
*/
void *GerarComerciantes(void *arg){
	int i,intEsqDir;
	int ids[gQtdComerciantes]; 
	pthread_t thrComerciantes[gQtdComerciantes];
	for(i=0; i < gQtdComerciantes; i++) ids[i]=i;
     
	gQtdComerciantes_aux=0;
	for(;;){
	    //Para verificar se cria ou não
	    if(CriarOuNaoCriar() == 1){
		   intEsqDir=CriarEsqOrDir();
	 	   if(intEsqDir == 1){
              pthread_mutex_lock(&semMsg);
              ExibeMsg(0);
              pthread_mutex_unlock(&semMsg);
  		      pthread_create(&thrComerciantes[gQtdComerciantes_aux], NULL, AtravessarPonteEsqDir, &ids[gQtdComerciantes_aux]);	 
              gQtdEsquerdas--;		      
           }else{ 
              if(intEsqDir == 2){
	              pthread_mutex_lock(&semMsg);
	              ExibeMsg(1);
	              pthread_mutex_unlock(&semMsg);			  			   
           	      pthread_create (&thrComerciantes[gQtdComerciantes_aux], NULL, AtravessarPonteDirEsq, &ids[gQtdComerciantes_aux]);	 
    	          gQtdDireitas--;
     	      }else
     	         break;
	       }
	       gQtdComerciantes_aux++;
        }
        PassaTempo(1);        
	}
	for(i=0; i < gQtdComerciantes; i++) 
	     pthread_join(thrComerciantes[i],NULL);	 
    pthread_exit((void*) 0);
}
/*
	Rotina do comerciante que atravessa da Esq para a Dir
*/
void *AtravessarPonteEsqDir(void *arg){
	 //Impede que quem venha da direita consiga entrar na ponte
     pthread_mutex_lock(&semPonte);	 
     pthread_mutex_lock(&semMsg);
	 ExibeMsg(2);
     pthread_mutex_unlock(&semMsg); 	 
	 PassaTempo(5);
     pthread_mutex_lock(&semMsg);
	 ExibeMsg(5);
     pthread_mutex_unlock(&semMsg); 	 
	 pthread_mutex_unlock(&semPonte);
     pthread_exit((void*) 0);	 
}
/*
	Rotina do comerciante que atravessa da Dir para a Esq
*/
void *AtravessarPonteDirEsq(void *arg){
	 //Impede que quem venha da esquerda consiga entrar na ponte
     pthread_mutex_lock(&semPonte);	 
     pthread_mutex_lock(&semMsg);
	 ExibeMsg(3);
     pthread_mutex_unlock(&semMsg); 	 
	 PassaTempo(5);
     pthread_mutex_lock(&semMsg);
	 ExibeMsg(4);
     pthread_mutex_unlock(&semMsg); 	 
	 pthread_mutex_unlock(&semPonte);
     pthread_exit((void*) 0);	 
}
/*
	Exibe Mensagens provenientes das Threads 
	de acordo com o parametro
*/
void ExibeMsg(int pintMessage){
	 switch(pintMessage){
	    case 0:
			 printf("\n*****Foi gerado um comerciante que ");
			 printf("atravessara da Esquerda para a Direita");
			 break;
	    case 1:
			 printf("\n*****Foi gerado um comerciante que ");
			 printf("atravessara da Direita para a Esquerda");
			 break;
	    case 2:
			 printf("\n>>>>>Um comerciante entrou do lado esquerdo da ponte");
			 break;
	    case 3:
			 printf("\n<<<<<Um comerciante entrou do lado direito da ponte");
			 break;
	    case 4:
			 printf("\n<<<<<Um comerciante saiu pelo lado esquerdo da ponte");
			 break;
	    case 5:
			 printf("\n>>>>>Um comerciante saiu pelo lado direito da ponte");
			 break;
	    case 6:
			 printf("\n\nTodos os comerciantes Atravessaram a ponte\n\n");
			 system("PAUSE");
			 break;			 
	    default:
		     break;
	 }
}
/*
	Retorna 1 como true e 0 como false
	De acordo com a probabilidade de entrada do usuário
*/
int CriarOuNaoCriar(){
	float iRand; //Variavel que armazenara o valor randomico
	iRand = rand() % 101; //gera um numero de 0 a 100
	if(iRand < gProbabilidade){
		return 1;
	}
	return 0;
}
/*	
	Verifica se Cria um comerciante pela esquerda ou direita
	Se retornar 1 cria um que entra pela esquerda
	Se retornar 2 cria um que entra pela direita
	se retornar 0 não cria nenhum e finaliza a thread geradora
*/
int CriarEsqOrDir(){
	float iRand; //Variavel que armazenara o valor randomico
	iRand = rand() % 101; //gera um numero de 0 a 100
	if(iRand < 51.00){//Probabilidade de 50%
		if(gQtdEsquerdas > 0)
			return 1;
		else
			if(gQtdDireitas > 0)
				return 2;
	}else{
		if(gQtdDireitas > 0)
			return 2;
		else
			if(gQtdEsquerdas > 0)
				return 1;
	}
	return 0;		  
}
/*
	Trama do programa
	Sequência copiada do arquivo PDF disponibilizado no Moodle
*/
void breveHistoriaCivilizacao(){
     system("CLS");
     printf("\n");
     printf("********************************************************************\n");
     printf("**** ** ** ** ** ** ** ** ** INTRODUCAO ** ** ** ** ** ** ** ** ****\n");
     printf("********************************************************************\n");
     printf("*                                                                  *\n");
     printf("*      Um povoado indiano vive a beira de um precipicio bastante   *\n");
     printf("* profundo, mas nao muito largo. Este povo habita duas cidades,    *\n");
     printf("* fundadas uma em cada lado do precipicio. Devido a necessidades   *\n");
     printf("* comerciais existentes, foi construida uma ponte rustica entre as *\n");
     printf("* duas cidades sobre o precipicio, das custas de muitas vidas de   *\n");
     printf("* operarios acidentados.                                           *\n");
     printf("*      Esta ponte e muito estreita, mas bastante resistente.       *\n");
     printf("* Os comerciantes conseguem levar suas mercadorias de uma cidade a *\n");
     printf("* outra em elefantes por ela. Com o crescimento das duas cidades o *\n");
     printf("* comercio tornou-se intenso, gerando problemas de travessia.      *\n");
     printf("*                                                                  *\n");
     printf("*                                                                  *\n");     
     printf("********************************************************************\n");
     printf("*                                                              1/4 *\n");
     printf("********************************************************************\n");
     printf("\n");
     system("PAUSE");
     system("CLS");
     printf("\n");
     printf("********************************************************************\n");
     printf("**** ** ** ** ** ** ** ** ** INTRODUCAO ** ** ** ** ** ** ** ** ****\n");
     printf("********************************************************************\n");
     printf("*                                                                  *\n");
     printf("*      Como a ponte e muito estreita, e possivel apenas a travessia*\n");
     printf("* em um sentido. E impossivel que dois elefantes se cruzem. Assim, *\n");
     printf("* tornou-se bastante comum o encontro de comerciantes em sentidos  *\n");
     printf("* opostos proximo ao meio da ponte. Como nenhum dos comerciantes   *\n");
     printf("* quer retornar e esperar pela passagem do outro, longas discussoes*\n");
     printf("* sao travadas, desperdicando o tao precioso tempo de travessia e  *\n");
     printf("* levando a um impasse (deadlock).                                 *\n");
     printf("*      As autoridades nao querem construir outra ponte para        *\n");
     printf("* resolver o problema, alegando um proibitivo custo de vidas       *\n");
	printf("* humanas.                                                         *\n");
     printf("*                                                                  *\n");
     printf("*                                                                  *\n");     
     printf("********************************************************************\n");
     printf("*                                                              2/4 *\n");
     printf("********************************************************************\n");
     printf("\n");
     system("PAUSE");
     system("CLS");
     printf("\n");
     printf("********************************************************************\n");
     printf("**** ** ** ** ** ** ** ** ** INTRODUCAO ** ** ** ** ** ** ** ** ****\n");
     printf("********************************************************************\n");
     printf("*                                                                  *\n");     
     printf("*      Um sabio conselheiro resolveu implementar uma politica de   *\n");
     printf("* acesso nos dois extremos da ponte. Dois guardas, um de cada      *\n");
     printf("* lado, controlam o acesso. Os guardas permitem apenas a travessia *\n");
     printf("* em um sentido. Se a ponte estiver livre, o primeiro comerciante  *\n");
     printf("* que chegar tem seu acesso liberado. Se porventura outros         *\n");
     printf("* comerciantes necessitarem realizar a travessia no mesmo sentido, *\n");
     printf("* sua passagem e liberada. Comerciantes que necessitem realizar a  *\n");
     printf("* travessia no sentido oposto devem esperar ate que os comerciantes*\n");
     printf("* na ponte terminem a travessia. Uma vez que nao houver mais       *\n");
     printf("* nenhum comerciante necessitando realizar a travessia no sentido  *\n");
     printf("* liberado, os comerciantes do outro lado iniciam sua travessia.   *\n");
     printf("*                                                                  *\n");
     printf("********************************************************************\n");
     printf("*                                                              3/4 *\n");
     printf("********************************************************************\n");
     printf("\n");
     system("PAUSE");
     system("CLS");
     printf("\n");
     printf("********************************************************************\n");
     printf("**** ** ** ** ** ** ** ** ** INTRODUCAO ** ** ** ** ** ** ** ** ****\n");
     printf("********************************************************************\n");
     printf("*                                                                  *\n");
     printf("*      Apesar de esta solucao otimizar o uso da ponte (eficiencia),*\n");
     printf("* o tempo de espera medio total dos comerciantes (turnaround) e a  *\n");
     printf("* quantidade de travessias realizadas por unidade de tempo         *\n");
     printf("* (throughput), o tempo de espera dos comerciantes do lado oposto  *\n");
     printf("* ao da travessia (tempo de resposta interativo) as vezes se torna *\n");
     printf("* proibitivo, causando o problema de starvation.                   *\n");
     printf("*      Foi entao proposto ao sabio o desafio de resolver o problema*\n");
     printf("* com imparcialidade para comerciantes de ambos os lados.          *\n");
     printf("*                                                                  *\n");
     printf("*                                                                  *\n");
     printf("*                                                                  *\n");
     printf("*                                                                  *\n");               
     printf("********************************************************************\n");
     printf("*                                                              4/4 *\n");
     printf("********************************************************************\n");
     printf("\n");
     system("PAUSE");
     system("CLS");
}
/*
	Rotina para simular o sleep
*/
void PassaTempo(int tempo){
     int time, i, j;
     time = TEMPO;
     for(j=0;j<tempo;j++)
          for(i = 0; i < time;i++);
}
