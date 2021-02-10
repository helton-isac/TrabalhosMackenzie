/************************************************
** TRABALHO DE INTRODUÇÃO A COMPUTAÇÃO GRÁFICA **
** ALUNO: HELTON ISAC TORRES GALINDO ************
** n° 3068645-8 ************************** 5°N **
************************************************/

#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <iostream>
#define MAX 100

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);
void recuperaPly();

static GLfloat vertices[MAX];
static GLubyte faces[MAX];
static int vetorFaces[MAX][MAX];
static int eixoy, eixox, largura, altura;
static int qtdVertex;
static int qtdFaces;
static char x[1];   
static float r,g,b;

using namespace std;

static string strAux;

int main(int argc, char** argv){
	recuperaPly();        
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (300, 300); 
	glutInitWindowPosition (300, 300); 
	glutCreateWindow (argv[0]);
	init();
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void recuperaPly(){
	int lintCount=0, lintDots=0, i = 0, j=0;  
	int lintVetGuia[MAX];    

	ifstream arquivo("arquivo.ply");              
	if(arquivo.is_open()){
		while(!arquivo.eof()){
			arquivo >> strAux;
			if(strAux == "vertex"){
				arquivo >> x;
				if((x[0] >= 48) && (x[0] <= 57)) 
					qtdVertex = atoi(x);
			}
			if(strAux == "face"){
				arquivo >> x;
				if((x[0] >= 48) && (x[0] <= 57))
					qtdFaces = atoi(x);
			}
			if(strAux == "end_header"){         
				while(!arquivo.eof()){            
					arquivo >> x;      
					if((x[0] >= 48) && (x[0] <= 57)){
						lintVetGuia[i] = atoi(x);
						i++;                 
					}               
				}	
				for(i = 0; i < qtdVertex * 3; i++){
					vertices[i] = lintVetGuia[i];
				}
				for(i = qtdVertex * 3; lintCount < qtdFaces; lintCount++){
					lintDots = lintVetGuia[i];
					for(j = 0; j <= lintDots; j++){
						vetorFaces[lintCount][j] = lintVetGuia[i];
						i++;
					}
				}
			}         
		}
	}
	arquivo.close();  
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho (-50, 50, -50, 50, -50 , 50);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	largura=w; 
	altura=h;
}

void display(void){
	int i = 0, j = 0, lintDots = 0;

	glPushMatrix();  
	glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
	glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	for(i = 0; i < qtdFaces; i++){
		lintDots = vetorFaces[i][0];
			for(j=0; j<lintDots; j++)
				faces[j] = vetorFaces[i][j+1];
			switch (i){
				case 0:
					glColor3f(1, 0, 0);
					break;
				case 1:
					glColor3f(0, 1, 0);
					break;
				case 2:
					glColor3f(0, 0, 1);
					break;
				case 3:
					glColor3f(0, 1, 1);
					break;
				case 4:
					glColor3f(1, 1, 0);
					break;
				case 5:
					glColor3f(0.5, 0.8, 0);
					break;
				case 6:
					glColor3f(0, 0.5, 0.8);
					break;
			}
			glDrawElements(GL_POLYGON, lintDots, GL_UNSIGNED_BYTE, faces);  
	}
	glDisableClientState (GL_VERTEX_ARRAY);
	glPopMatrix();  
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27:
			exit(0);
			break;
		case '6':
			eixoy = (eixoy + 5) % 360;
			glutPostRedisplay();
			break;
		case '4':
			eixoy = (eixoy - 5) % 360;
			glutPostRedisplay();
			break;
		case '2':
			eixox = (eixox + 5) % 360;
			glutPostRedisplay();
			break;
		case '8':
			eixox = (eixox - 5) % 360;
			glutPostRedisplay();
			break;
		case 'p':
			glLoadIdentity();
			gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
			gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
			glutPostRedisplay();
			break;
		case 'o':
			glLoadIdentity();
			glOrtho (-50, 50, -50, 50, -50 , 50);
			glutPostRedisplay();
			break;
	}
}
