#include <stdlib.h>
#include <GL/glut.h>

#include <iostream>
#include <fstream>
#include <stdio.h>


using namespace std;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);
void alocaEstrutura (void);
void desalocaEstrutura (void);
void special(int key,int x,int y);
void SetupRC(void);
void IdleStart(void);
void IdleStart2(void);
void IdleStop(void);

static GLfloat cores[24]={		// Estrutura para armazenar as cores utilizadas.
	0.1, 0.1, 1.0,              // Azul.
	1.0, 0.1, 0.1,              // Vermelho.
	1.0, 1.0, 0.1,              // Amarelo.
	0.1, 1.0, 0.1,              // Verde.
	1.0, 0.1, 1.0,              // Cyan.
	0.8, 0.6, 0.1,              // Laranja.
	0.7, 0.1, 0.6,              // Rosa.
	0.6, 0.6, 0.6               // Cinza.
};

ifstream infile;          // Ponteiro para o arquivo.  
char item[20];            // Variável para leitura do arquivo.


typedef struct {			// Estrutura para armazenar uma única face.
	int nLados;             // Quantidade de lados da face.
	GLubyte *Indices;       // Ponteiro para estrutura de índices que formam as faces.
}Faces;

//Estrutura que armazena os arquivos plys
typedef struct {
	GLfloat *vertices;
	Faces *objeto;
	int nFaces;
	int nVertices;
}EstruturaPly;
EstruturaPly vetPly[4];

int contImg = 0;

static int eixoy_ply1, eixox_ply1,eixoz_ply1;
static int eixoy_ply2, eixox_ply2,eixoz_ply2;
static int eixoy_ply3, eixox_ply3,eixoz_ply3;
static int eixoy_ply4, eixox_ply4,eixoz_ply4;
static float zoom_ply1, zoom_ply2, zoom_ply3, zoom_ply4;
bool sentidoLuz = true;

// Parâmetros de iluminação 1
GLfloat luzEspecular[4] = {0.3, 0.3, 1.0, 1.0};

//Luz da laterna
GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};

//Luz que acende e apaga
GLfloat luzAmbiente2[4] = {0.4,0.4,0.4,1.0}; 
GLfloat luzEspecular2[4] = {0.5,0.5,0.0,1.0};
GLfloat luzDifusa2[4] = {0.2, 1.0, 1.0, 1.0};
GLfloat posicaoLuz2[4] = {0.0, 0.0, 50.0, 1.0};

//Capacidade de brilho do material
GLfloat especularidade[4]={1.0,0.3,1.0,1.0}; 
GLint especMaterial = 60;

int largura, altura;
const string aux;

int main(int argc, char** argv){    
    int i = 0;
    //--------------------------
    //Armazena os arquivos
	infile.open("ply1.ply");
	alocaEstrutura();      
	infile.close();
	infile.open("ply2.ply");
	alocaEstrutura();      
	infile.close();
	infile.open("ply3.ply");
	alocaEstrutura();      
	infile.close();
	infile.open("ply4.ply"); 
	alocaEstrutura();      
	infile.close();
    //--------------------------
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (300, 300); 
	glutInitWindowPosition (100, 350); 
	glutCreateWindow ("EP - ICG - HELTON / RENATO");
	init();
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();
	desalocaEstrutura();
	return 0;
}

void SetupRC(void)
{ 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void init(void){
	glOrtho (-50, 50, -50, 50, -1000, 1000);
	zoom_ply1 = zoom_ply2 = zoom_ply3 = zoom_ply4 = 1.0;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente2); 
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa2 );
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular2 );
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz2 );   
}

void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	largura=w; 
	altura=h;
}

void IdleStart(void){
	if(sentidoLuz){
		posicaoLuz[0] += 0.2;
		if(posicaoLuz[0]>=200){
			sentidoLuz=false;
		}
	}else{
		posicaoLuz[0] -= 0.2;
		if(posicaoLuz[0]<= -200){
			sentidoLuz=true;
		}
	}
	SetupRC(); 
	glutPostRedisplay();
}

void IdleStart2(void){
	if(sentidoLuz){
		posicaoLuz[0] += 0.2;
		if(posicaoLuz[0]>=200){
			sentidoLuz=false;
		}
	}else{
		posicaoLuz[0] -= 0.2;
		if(posicaoLuz[0]<= -200){
			sentidoLuz=true;
		}
	}
    eixoy_ply1 = (eixoy_ply1 + 1) % 360;    
    eixoy_ply2 = (eixoy_ply2 + 1) % 360;    
    eixoy_ply3 = (eixoy_ply3 + 1) % 360;        	
    eixoy_ply4 = (eixoy_ply4 + 1) % 360;    
    
	SetupRC(); 
	glutPostRedisplay();
}

void IdleStop(void){
	glutPostRedisplay();
}

void display(void){
	int j;
	j = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();
    glColor3f(0.4, 0.5, 0.7);
    glTranslatef(0,0,-900);
    glScalef(8.0,6,10);
    glutSolidCube(15);  
    glPopMatrix();  	
	while(j < 4 ){
		glPushMatrix();
		if(j == 0){
            glScalef(zoom_ply1,zoom_ply1,zoom_ply1);
			glTranslatef (-27.0, 0.0, 0.0);
			glRotatef ((GLfloat) eixoy_ply1, 0.0, 1.0, 0.0); 
			glTranslatef (26.0, 0.0, 0.0);
            glRotatef ((GLfloat) eixox_ply1, 1.0, 0.0, 0.0); 
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vetPly[j].vertices);
    		for (int i = 0; i < vetPly[j].nFaces; i++){
   			    glColor3f (1, 0.2, 0.2);
    			glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
    		}               
		}else{
			if(j == 1){
                glScalef(zoom_ply2,zoom_ply2,zoom_ply2);
				glTranslatef (0.0, 0.0, 0.0);
                glRotatef ((GLfloat) eixoy_ply2, 0.0, 1.0, 0.0);
                glRotatef ((GLfloat) eixox_ply2, 1.0, 0.0, 0.0); 
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vetPly[j].vertices);                 
        		for (int i = 0; i < vetPly[j].nFaces; i++){
                      glColor3f (1, 1, 0.2);
        			  glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
        		}                   
			}else{
				if(j == 2){
                    glScalef(zoom_ply3,zoom_ply3,zoom_ply3);
					glTranslatef (28.0, 0.0, 0.0);
                    glRotatef ((GLfloat) eixoy_ply3, 0.0, 1.0, 0.0);
					glTranslatef (-27.0, 0.0, 0.0);
                    glRotatef ((GLfloat) eixox_ply3, 1.0, 0.0, 0.0); 
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(3, GL_FLOAT, 0, vetPly[j].vertices);                     
            		for (int i = 0; i < vetPly[j].nFaces; i++){
                          glColor3f (0.2, 1, 0.2);
            			  glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
            		}                       
				}else{
					if(j == 3){
                        glScalef(zoom_ply4,zoom_ply4,zoom_ply4);
						glTranslatef (0.0, 0.0, 0.0);
                        glRotatef ((GLfloat) eixox_ply4, 1.0, 0.0, 0.0); 
						glTranslatef (0.0, 0.0, 0.0);
                        glRotatef ((GLfloat) eixoy_ply4, 0.0, 1.0, 0.0); 
                        glRotatef ((GLfloat) eixoz_ply4, 0.0, 0.0, 1.0); 
                        glEnableClientState(GL_VERTEX_ARRAY);
                        glVertexPointer(3, GL_FLOAT, 0, vetPly[j].vertices);  
                        int i;
                		for (i = 0; i < (vetPly[j].nFaces-3); i++){
                            glColor3f (cores[3*(i%8)], cores[3*(i%8)+1], cores[3*(i%8)+2]);
                			glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
                		}
						glColor3f (0.3,0.4,0.3);
						glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
						i++;
						glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
						i++;
						glDrawElements(GL_POLYGON, vetPly[j].objeto[i].nLados, GL_UNSIGNED_BYTE, vetPly[j].objeto[i].Indices);           
					}
				}
			}
		}
		glDisableClientState (GL_VERTEX_ARRAY);
		glPopMatrix();
		j++;
	}

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27://ESC
			exit(0); break;
		case 'z'://Eixo X do I
			eixoy_ply1 = (eixoy_ply1 + 5) % 360; glutPostRedisplay(); break;
		case 'Z'://Eixo X do I
			eixoy_ply1 = (eixoy_ply1 - 5) % 360; glutPostRedisplay(); break;
		case 'x'://Eixo X do C
			eixoy_ply2 = (eixoy_ply2 + 5) % 360; glutPostRedisplay(); break;
		case 'X'://Eixo X do C
			eixoy_ply2 = (eixoy_ply2 - 5) % 360; glutPostRedisplay(); break;
		case 'c'://Eixo X do G
			eixoy_ply3 = (eixoy_ply3 + 5) % 360; glutPostRedisplay(); break;
		case 'C'://Eixo X do G
			eixoy_ply3 = (eixoy_ply3 - 5) % 360; glutPostRedisplay(); break;
		case 'a'://Eixo Y do I
			eixox_ply1 = (eixox_ply1 + 5) % 360; glutPostRedisplay(); break;
		case 'A'://Eixo Y do I
			eixox_ply1 = (eixox_ply1 - 5) % 360; glutPostRedisplay(); break;
		case 's'://Eixo Y do C
			eixox_ply2 = (eixox_ply2 + 5) % 360; glutPostRedisplay(); break;
		case 'S'://Eixo Y do C
			eixox_ply2 = (eixox_ply2 - 5) % 360; glutPostRedisplay(); break;
		case 'd'://Eixo Y do G
			eixox_ply3 = (eixox_ply3 + 5) % 360; glutPostRedisplay(); break;
		case 'D'://Eixo Y do G
			eixox_ply3 = (eixox_ply3 - 5) % 360; glutPostRedisplay(); break;
       case 'q'://Zoom + do I
            zoom_ply1 = (zoom_ply1 * 1.1); glutPostRedisplay(); break;  
       case 'Q'://Zoom - do I    
            if(zoom_ply1<=0) break; zoom_ply1 = (zoom_ply1 * 0.9); glutPostRedisplay(); break;             
       case 'w'://Zoom + do C
            zoom_ply2 = (zoom_ply2 * 1.1); glutPostRedisplay(); break;  
       case 'W'://Zoom - do C
            if(zoom_ply2<=0) break; zoom_ply2 = (zoom_ply2 * 0.9); glutPostRedisplay(); break;             
       case 'e'://Zoom + do G
            zoom_ply3 = (zoom_ply3 * 1.1); glutPostRedisplay(); break;  
       case 'E'://Zoom - do G
            if(zoom_ply3<=0) break; zoom_ply3 = (zoom_ply3 * 0.9); glutPostRedisplay(); break;             

		case 'i'://Acende a luz
           	glEnable(GL_LIGHT1); glutPostRedisplay(); break;
		case 'I'://Apaga a luz
           	glDisable(GL_LIGHT1); glutPostRedisplay(); break;            			
        case 'l'://Liga a Luz automatica
			glutIdleFunc(IdleStart); break;
		case 'L'://Desliga a Luz automatica
			glutIdleFunc(IdleStop); break;
        case 'j'://Liga a Luz automatica
			glutIdleFunc(IdleStart2); break;
		case 'J'://Desliga a Luz automatica
			glutIdleFunc(IdleStop); break;			

       case '+'://Zoom + do Diamante
            zoom_ply4 = (zoom_ply4 * 1.1); glutPostRedisplay(); break;  
       case '-'://Zoom - do Diamante
            if(zoom_ply4<=0) break; zoom_ply4 = (zoom_ply4 * 0.9); glutPostRedisplay(); break;                                                 

	}
}


void special(int key,int x,int y){
	//Funções especificas para o diamante
	switch (key){
		case GLUT_KEY_RIGHT://Gira em torno do eixo Y 
			eixoy_ply4 = (eixoy_ply4 + 5) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT://Gira em torno do eixo Y 
			eixoy_ply4 = (eixoy_ply4 - 5) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN://Gira em torno do eixo X
			eixox_ply4 = (eixox_ply4 + 5) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP://Gira em torno do eixo X
			eixox_ply4 = (eixox_ply4 - 5) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_DOWN://Gira em torno do eixo Z
			eixoz_ply4 = (eixoz_ply4 + 5) % 360;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_UP://Gira em torno do eixo Z
			eixoz_ply4 = (eixoz_ply4 - 5) % 360;
			glutPostRedisplay();
			break;
	}
}

void alocaEstrutura(){
    int nFaces = 0;
    int nVertices = 0;   
    int i, tmp = 0;
    
    while (strcmp(item, "end_header")){
        infile >> item;  
        if (!strcmp(item, "element")){
            infile >> item;
            if (!strcmp(item, "vertex"))
                infile >> nVertices;
            else if (!strcmp(item, "face"))
                infile >> nFaces;
        }
    }
    Faces *objeto;  
    GLfloat *vertices;
    vertices = (GLfloat *)malloc(sizeof(GLfloat)* 3 * nVertices);
    for (i = 0; i < 3 * nVertices; i++){
        infile >> vertices[i];   
    }
    objeto = (Faces *)malloc(sizeof(Faces) * nFaces);
    for (i = 0; i < nFaces; i++){
        infile >> objeto[i].nLados;   
		objeto[i].Indices = (GLubyte *)malloc(sizeof(GLubyte)*objeto[i].nLados);
        for (int j = 0; j < objeto[i].nLados; j++){
            infile >> tmp;
            objeto[i].Indices[j] = tmp; 
        }
    }
    EstruturaPly *est_ply = (EstruturaPly *)malloc(sizeof(EstruturaPly));
    est_ply->vertices = vertices;
    est_ply->objeto = objeto;
    est_ply->nFaces = nFaces;
    est_ply->nVertices = nVertices;
    vetPly[contImg] = *est_ply;
    contImg++;
	for(i = 0 ; i < 20 ; i++){
		item[i] = ' ';
	}
}

void desalocaEstrutura (void){
	int i = 0;
	while(i < vetPly[i].nFaces){
		free(vetPly[i].objeto[i].Indices);
		free(vetPly[i].objeto);
		free(vetPly[i].vertices);
		i++;
	}
}


