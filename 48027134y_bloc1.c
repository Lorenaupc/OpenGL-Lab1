#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdio.h>

int x0,y0;

float res_x = 0;
float res_y = 0;

int index = 0;
float array[6];

int canviar_color = 0;
int dibuixar_triangle = 0;


//Inici array coordenades

void iniciar_array(){

	array[0] = -0.5;
	array[1] = -0.3;
	array[2] = 0.5;
	array[3] = -0.3;
	array[4] = 0.0;
	array[5] = 0.6;

}


//Cas en que arrastrem el ratolí

void onMotion(int x, int y) {
	
	if(canviar_color == 1){
		x0 = x; y0 = y;		
		glutPostRedisplay();
	}

}


//Captura clicks mouse per dibuixar el nou triangle

void mouse(int button,int state,int x, int y){
	
	//Si hem pres la tecla 't' i hem clicat el botó esquerre del ratolí
	if(dibuixar_triangle == 1){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	
			//Agafem les mesures
			res_x = (float)glutGet(GLUT_WINDOW_WIDTH);
			res_y = (float)glutGet(GLUT_WINDOW_HEIGHT);
	
			//Calculem les noves coordenades dels vèrtexs
			float coord_x = ((float)x/(res_x/2)) - 1;
			float coord_y = ((float)y/(res_y/2)) - 1;

			//Guardem les coordenades en un array i adjustem el signe segons el quadrant on es dibuixi el vèrtex

			if(((float)x > res_x/2) && ((float)y > res_y/2)) {
				array[index] = coord_x; index++;
				array[index] = -1.0*coord_y;  index++;		
			}

			else if(((float)x >= res_x/2) && ((float)y <= res_y/2)) {
				array[index] = coord_x; index++;
				array[index] = -1.0*coord_y; index++;
			}

			else if(((float)x < res_x/2) && ((float)y < res_y/2)) {
				array[index] = coord_x; index++;
				array[index] = -1.0*coord_y;  index++;
			}

			else if(((float)x < res_x/2) && ((float)y >= res_y/2)){
				array[index] = coord_x; index++; 
				array[index] = -1.0*coord_y; ;index++;
			}

			else{
				array[index] = 0; index++;
				array[index] = 0; index++;
			}
		
		}
	
		//Si ja hem omplert l'array, deixem dibuixar el triangle
		if (index == 6){

			//Posem l'índex a 0 perquè tornarem a omplir l'array si volem dibuixar un altre triangle
			index = 0;
			glutPostRedisplay();
		}

	}

}

void keyboard(unsigned char c, int x, int y){

	//Si s'ha polsat 'ESC' sortim
	if(c == 27) exit(0);

	//Si s'ha polsat 'h' surt l'ajuda
	else if (c == 'h'){
		printf("\n");
		printf("Heu desplegat l'ajuda: \n \n");
		printf("-Si es reescala la finestra el dibuix no es deformarà  \n");
		printf("-Si s'arrossega el ratoli horitzontalment canviara el color de fons \n");
		printf("-Si es prem ESC s'aturara el programa \n");
		printf("-Si es prem la tecla 'h' es desplega l'ajuda \n");
		printf("-Si es prem la tecla 't' es permet clicar i escollir els vertexs d'un nou triangle \n");
		printf("-Si es prem la tecla 'f', es permet fer el color de fons més fosc o més clar \n \n");
	}
		
	//Si s'ha polsat 'f' aclarim o obscurim el color de fons
	else if(c == 'f'){
		if (canviar_color == 0) canviar_color = 1;
		else if (canviar_color == 1) canviar_color = 0;
	}

	//Si polsem 't', amb els clicks seleccionem els nous vèrtexs 
	else if(c == 't'){
		if (dibuixar_triangle == 0) dibuixar_triangle = 1;
		else if (dibuixar_triangle == 1) dibuixar_triangle = 0;
	}
}


void display(void) {

	//Calculem el paràmetre que variarà el color de fons de la finestra openGL
	float colorx = (float)x0/1000;

	//Establim color de fons
	glClearColor(colorx,colorx,1.0,1.0); 
	glClear(GL_COLOR_BUFFER_BIT); 

	glBegin(GL_TRIANGLES);

		glColor3f(1.0,0.0,0.0);
		glVertex3f(array[0],array[1],0.0);
		
		glColor3f(1.0,0.0,1.0);
		glVertex3f(array[2],array[3],0.0);

		glColor3f(0.0,1.0,0.0);
		glVertex3f(array[4],array[5],0.0);

	glEnd();

	glutSwapBuffers();
}


void reshape(int x, int y) {

	//Calculem el nou aspect ratio i adjustem viewport
	int nouorigen = (x-y)/2;
	glViewport(nouorigen, 0, y, y);

}

int main (int argc, char **argv){

	iniciar_array();
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(600,600);

	glutCreateWindow("INDI: practiques openGL");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(onMotion);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}

