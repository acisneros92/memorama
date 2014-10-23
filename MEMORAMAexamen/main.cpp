#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Sound.h"

using namespace std;

Sound sonido = Sound("/Users/arianacisneros/Desktop/song.wav");

void ChangeSize(int w, int h);
GLsizei winWidth = 800, winHeight =600; // Tamaño inicial de la ventana
GLint xRaster = -770, yRaster= 200;
string texto = "I-Iniciar, P-Pausar, R-Reiniciar";
string texto_esc_salir = "Esc-Salir";
string nombreMontse = "Montserrat Lozano A01088686";
string nombreAriana = "Ariana Cisneros A01138381";
bool moveCamera = false;
int _num;
int _delta = 1;
int anguloTodo = 0;
bool _stop;
bool _gameOver;
char ganar[40];
char turnos[20];
char tiempo[200];
//arreglo de cartas
char arr[24]={'0','1','2','3','4','5','6','7','0','1','2','3','4','5','6','7','0','1','2','3','4','5','6','7'};
//estatus de cartas
bool expuesta[24]={false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false, false,false,false,false,false,false,false,false};

bool colored[24] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false, false,false,false,false,false,false,false,false};
bool rotated[24] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false, false,false,false,false,false,false,false,false};
int angles[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int deltaRect =100; // delta del ancho de cada rectangulo
int deltaHeight = 200;
int beginHeight = 400;
int deltaHeight2 = 400;
int ancho = 100;
int alto = 200;
GLdouble scaleX = .9;
GLdouble scaleY = .9;

int estado = 0;
int carta1 = 0;
int carta2 = 0; //para comparar cartas
int carta3 = 0;
int turno = 0;
int sepHor = 30;
int sepVert= 100;
int angleTeapot = 0;

bool ayuda = false;

GLubyte cero[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x3F,0x80,0x00,
    0x00,0x7F,0xC0,0x00,
    0x00,0xFF,0xE0,0x00,
    0x01,0xFF,0xF0,0x00,
    0x03,0xFB,0xF8,0x00,
    0x03,0xF1,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xE0,0xF8,0x00,
    0x03,0xF1,0xF8,0x00,
    0x03,0xFB,0xF8,0x00,
    0x01,0xFF,0xF0,0x00,
    0x00,0xFF,0xE0,0x00,
    0x00,0x7F,0xC0,0x00,
    0x00,0x3F,0x80,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,

};

GLubyte uno[] ={
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x01,0xFF,0xF8,0x00,
    0x01,0xFF,0xF8,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x03,0x0F,0x00,0x00,
    0x03,0x8F,0x00,0x00,
    0x01,0xCF,0x00,0x00,
    0x00,0xFF,0x00,0x00,
    0x00,0x7F,0x00,0x00,
    0x00,0x3F,0x00,0x00,
    0x00,0x1F,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x01,0xFF,0xF8,0x00,
    0x01,0xFF,0xF8,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x00,0x0F,0x00,0x00,
    0x03,0x0F,0x00,0x00,
    0x03,0x8F,0x00,0x00,
    0x01,0xCF,0x00,0x00,
    0x00,0xFF,0x00,0x00,
    0x00,0x7F,0x00,0x00,
    0x00,0x3F,0x00,0x00,
    0x00,0x1F,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
};

GLubyte dos[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x1F,0xFF,0xE0,
    0x00,0x3F,0xFF,0xF0,
    0x00,0x3F,0xFF,0xF0,
    0x00,0x3F,0xFF,0xF0,
    0x00,0x3E,0x00,0x00,
    0x00,0x1F,0x00,0x00,
    0x00,0x0F,0x80,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x03,0xE0,0x00,
    0x00,0x01,0xF0,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0x7C,0x00,
    0x00,0x00,0x3E,0x00,
    0x00,0x00,0x1F,0x00,
    0x00,0x00,0x0F,0x80,
    0x00,0x00,0x07,0xC0,
    0x00,0x00,0x03,0xE0,
    0x00,0x00,0x01,0xF0,
    0x00,0x00,0x01,0xF0,
    0x00,0x00,0x00,0xF0,
    0x00,0x00,0x00,0xF0,
    0x00,0x3E,0x01,0xF0,
    0x00,0x3E,0x03,0xE0,
    0x00,0x1F,0x03,0xE0,
    0x00,0x0F,0x87,0xC0,
    0x00,0x07,0xCF,0xC0,
    0x00,0x03,0xFF,0x80,
    0x00,0x01,0xFF,0x80,
    0x00,0x00,0xFF,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
};

GLubyte tres[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x00,0x00,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x03,0xFF,0xF8,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
};

GLubyte cuatro[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x00,0x07,0xC0,0x00,
    0x1F,0xFF,0xC0,0x00,
    0x1F,0xFF,0xC0,0x00,
    0x1F,0xFF,0xC0,0x00,
    0x1F,0xFF,0xC0,0x00,
    0x1F,0xFF,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x1E,0x07,0xC0,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    
    
};



GLubyte cinco[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x01,0xFF,0xFC,0x00,
    0x01,0xFF,0xFE,0x00,
    0x01,0xFF,0xFF,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x00,0x00,0x07,0x00,
    0x01,0xFF,0xFF,0x00,
    0x01,0xFF,0xFE,0x00,
    0x01,0xFF,0xFC,0x00,
    0x01,0xC0,0x00,0x00,
    0x01,0xC0,0x00,0x00,
    0x01,0xC0,0x00,0x00,
    0x01,0xC0,0x00,0x00,
    0x01,0xC0,0x00,0x00,
    0x01,0xFF,0xFF,0x00,
    0x01,0xFF,0xFF,0x00,
    0x01,0xFF,0xFF,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
};

GLubyte seis[] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0x01,0xF0,0x00,
    0x1F,0x01,0xF0,0x00,
    0x1F,0x01,0xF0,0x00,
    0x1F,0x01,0xF0,0x00,
    0x1F,0x01,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0x00,0x00,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x1F,0xFF,0xF0,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00
    
};


GLubyte siete[] = {
    
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x00,
    0x00,0x00,0xC0,0x00,
    0x00,0x00,0x60,0x00,
    0x00,0x00,0x30,0x00,
    0x00,0x00,0x18,0x00,
    0x00,0x00,0x0C,0x00,
    0x00,0x00,0x06,0x00,
    0x00,0x00,0x3F,0xF0,
    0x00,0x00,0x3F,0xF0,
    0x00,0x00,0x01,0xC0,
    0x00,0x00,0x00,0xE0,
    0x00,0x00,0x00,0x70,
    0x00,0x00,0x00,0x3C,
    0x00,0x00,0x00,0x0C,
    0x00,0x00,0x00,0x0C,
    0x00,0x00,0x00,0x0C,
    0x00,0x00,0x00,0x0C,
    0x00,0x03,0xFF,0xFC,
    0x00,0x03,0xFF,0xFC,
    0x00,0x03,0xFF,0xFC,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
};

GLfloat light_position[] = { 0, 0, 2.0, 1.0 };




void sound (int value){
    
    sonido.PlaySound();
    glutTimerFunc(50000,sound,0);
    
}


void shuffle()
{
    srand(time(NULL));
    int auxIndex;
    char tmp;
    
    for (int i = 0; i < 24; i++)
    {
        auxIndex = rand()% 24;
        tmp = arr[i];
        arr[i] = arr[auxIndex];
        arr[auxIndex] = tmp;
    }
}

void comparar ()
{
    if (!((arr[carta1] == arr[carta2]) && (arr[carta1] == arr[carta3])))
    {   //si las cartas son diferentes ocultar
        expuesta[carta1] = false;
        expuesta[carta2] = false;
        expuesta[carta3] = false;
    }else
    {
        colored[carta1] = true;
        colored[carta2] = true;
        colored[carta3] = true;
    }
}

void isGameOn()
{
    for (int i = 0; i < 24; i++)
    {
        if(!expuesta[i]){
            estado = 4;
            return;
        }
    }
    
    colored[carta1] = true;
    colored[carta2] = true;
    colored[carta3] = true;
    estado = 3;
    _stop = true;
}

void callback(int x, int y)
{
    int i=0, j= 0;
    bool encontro = false;
    //mapear indices
    int openGL_X = (x - (winWidth/2)) * 2;
    int openGL_Y = winHeight - y * 2;
    
    //Determinar cuál baraja es
    for (int k=0; k< 24; k++) {
        if(k < 12)
        {
     
                if (openGL_X >= (-(winWidth-(ancho*k)))+(sepHor*k) && openGL_X <= (-(winWidth-(ancho*k)))+(sepHor*k)+ancho && openGL_Y >= (winHeight-deltaHeight) && openGL_Y <= winHeight)
                {
                    i= k;
                    rotated[i] = true;
                    encontro = true;
                }
            
        }else
        {
            //glTranslatef((-(winWidth-(ancho*j)))+(30*j)+(ancho/2), (winHeight-100-deltaHeight2)+(alto/2), 0);
            if (openGL_X >= (-(winWidth-(ancho*j)))+(sepHor*j) && openGL_X <= (-(winWidth-(ancho*j)))+(sepHor*j)+ancho &&
                openGL_Y >= (winHeight-sepVert-deltaHeight2) && openGL_Y <= (winHeight-deltaHeight2-sepVert+alto))
            {
                i = k;
                rotated[i] = true;
                encontro = true;
            }
            j++;
        }
    }

    
    if (!expuesta[i] && encontro) {
        switch (estado) {
            case 0: //inicio 1era carta
                expuesta[i] = true; carta1 = i; estado = 1;
                break;
            case 1: // mostrar 2nda carta y contar el turno
                expuesta[i] = true; carta2 = i; estado = 2;
                break;
            case 2: // mostrar tercera carta otra carta
                expuesta[i] = true; carta3 = i; turno++; isGameOn();
                break;
            case 4:
                comparar(); expuesta[i] = true; carta1 = i; estado = 1;
                
        }
    }
    
}

void mouse(int button, int state, int x, int y){
    
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            callback(x,y);
            glutPostRedisplay();
        }
    }
}

void formato()
{
    int mili = _num % 10;
    int seg = (_num/10)%60;
    int min = (_num/10)/60;
    
    if(seg < 10)
    {
        sprintf(tiempo, "%d : 0%d : %d", min, seg, mili);
    }
    else
    {
        sprintf(tiempo, "%d : %d : %d", min, seg, mili);
    }
    
}


void myTimer(int v)
{
    if (v == 1){
        if(!_stop)
        {
            _num += _delta;
            formato();
            glutPostRedisplay();
            glutTimerFunc(100, myTimer, 1);
        }else
        {
            glutPostRedisplay();
            glutTimerFunc(100, myTimer, 1);
        }
    }
}

void init()
{
    _num = 0;
    _stop = true;
    shuffle();
    sprintf(tiempo, "0 : 00 : 0");
    glClearColor(1.0,.6,0,0); //background del display naranja
    
    }
void lucesitas()
{
    /*HABILITAR LUCES*/
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };//negra
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//luz difusa blanca
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 }; //posicion de la luz, direccional
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };
    
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //lmodel ambient
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Si no ponemos luz NOO se ven los materiales.
    ////////////
    
    
    
}


void transparencia (){
    glEnable(GL_BLEND);
    //cambiar el modo de mezcla
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLineWidth(30);
    glBegin(GL_LINES);
    glColor4f(1.0, 0, 0, 1.0); //	rojo opaco
    glVertex2f(-800, -300);
    glColor4f(0.5, 0, 0,0); //	rojo semi-transparente
    glVertex2f(800, -300);
    
    glEnd();

}

void renderBitmapString(float x,float y,float z,char *string)
{
    int i;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y,0);
    
    glScalef(scaleX,scaleY,0.04);
    
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *string);
    
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
   

    
    glPushMatrix();
    if (estado == 3)
    {
        glRotatef(anguloTodo, 0, 0, 1);
        anguloTodo++;
        if(anguloTodo >= 360)
            anguloTodo= 0;
    }
    
    int j = 0;
    //CARDS
    for (int i =0; i<24; i++) {
        
        if(expuesta[i])
        {
            if(colored[i])
                glColor3f(250, 0, 0);
            else
                glColor3f(0, 255, 0);

        }else if (i%2 == 0) {
            glColor3f(128, 0, 128);
        } else {
            glColor3f(255,192,203);
        }
        
        if(i < 12)
        {
            glPushMatrix();
            glTranslatef((-(winWidth-(ancho*i)))+(sepHor*i)+(ancho/2), (winHeight-deltaHeight)+(alto/2), 0);
            if(rotated[i])
            {
                glRotatef(angles[i], 0, 0, 1);
                angles[i] = angles[i] + 10;
                
                if(angles[i] >= 360)
                {   cout<<"Hello";
                    rotated[i] = false;
                    angles[i] = 0;
                }
            }
            glScalef(ancho, alto, .05);
            
            if(expuesta[i])
            {
                glEnable(GL_POLYGON_STIPPLE);
                switch (arr[i]) {
                    case '0':
                        glPolygonStipple(cero);
                        break;
                    case '1':
                        glPolygonStipple(uno);
                        break;
                    case '2':
                        glPolygonStipple(dos);
                        break;
                    case '3':
                        glPolygonStipple(tres);
                        break;
                    case '4':
                        glPolygonStipple(cuatro);
                        break;
                    case '5':
                        glPolygonStipple(cinco);
                        break;
                    case '6':
                        glPolygonStipple(seis);
                        break;
                    case '7':
                        glPolygonStipple(siete);
                        break;
                    default:
                        break;
                }
                
            }
            glutSolidCube(1);
            glColor3f(0, 0, 1);
            glutWireCube(1);
            glDisable (GL_POLYGON_STIPPLE);
            glPopMatrix();
            if(expuesta[i])
            {
                glDisable(GL_POLYGON_STIPPLE);
                glColor3f(0, 0, 0);
                renderBitmapString((-(winWidth-(ancho*i)))+(sepHor*i), (winHeight-deltaHeight)+(alto/2), 1, &arr[i]);
            }
            
        }else
        {
            glPushMatrix();
            glTranslatef((-(winWidth-(ancho*j)))+(sepHor*j)+(ancho/2), (winHeight-sepVert-deltaHeight2)+(alto/2), 0);
            if(rotated[i])
            {
                glRotatef(angles[i], 0, 0, 1);
                angles[i] = angles[i] + 10;
                
                if(angles[i] >= 360)
                {
                    rotated[i] = false;
                    angles[i] = 0;
                   
                }
            }
            glScalef(ancho, alto, .05);
            if(expuesta[i])
            {
                glEnable(GL_POLYGON_STIPPLE);
                switch (arr[i]) {
                    case '0':
                        glPolygonStipple(cero);
                        break;
                    case '1':
                        glPolygonStipple(uno);
                        break;
                    case '2':
                        glPolygonStipple(dos);
                        break;
                    case '3':
                        glPolygonStipple(tres);
                        break;
                    case '4':
                        glPolygonStipple(cuatro);
                        break;
                    case '5':
                        glPolygonStipple(cinco);
                        break;
                    case '6':
                        glPolygonStipple(seis);
                        break;
                    case '7':
                        glPolygonStipple(siete);
                        break;
                    default:
                        break;
                }
                
            }

            glutSolidCube(1);
            glColor3f(0, 0, 1);
            glutWireCube(1);
            glDisable (GL_POLYGON_STIPPLE);
            glPopMatrix();
            
            if(expuesta[i])
            {
                glColor3f(0, 0, 0);
                renderBitmapString((-(winWidth-(ancho*j)))+(sepHor*j), (winHeight-sepVert-deltaHeight2)+(alto/2), 1, &arr[i]);
            }
            j++;
            
        }
        
    }
    
    if( !_stop && ayuda){
        //Numeros de cartas abajo
        glColor3f(255, 255, 255);
        int m = 0;
        for(int i = 0; i < 24; i++)
        {
            if(i < 12)
            {
            glRasterPos2i(xRaster + i*ancho + i*30, yRaster + 40);
            //draw3dString(GLUT_BITMAP_HELVETICA_18, cards[i], xRaster + i*50, yRaster, 1);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, arr[i]);
            }
            else{
                glRasterPos2i(xRaster + m*ancho + m*30, yRaster);
                //draw3dString(GLUT_BITMAP_HELVETICA_18, cards[i], xRaster + i*50, yRaster, 1);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, arr[i]);
                m++;
            }
        }
    }
    
    if (estado == 3) { //gano
        //TEXTO GANASTE
        
      
        glColor3f(0, 255, 0);
        glPushMatrix();
        glScalef(1500, 200, 0.4);
        glutSolidCube(1);
        glColor3f(255, 0, 255);
        glutWireCube(1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(-400,-200, 0);
        glRotatef(angleTeapot, 0, 0, 1);
        angleTeapot+= 10;
        if(angleTeapot >= 360)
        {
            angleTeapot = 0;
        }
        cout<<angleTeapot;
        glScalef(70, 70, .1);
        glColor3ub(255, 0, 0);
        
        lucesitas();
        GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 0.0 };
        GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
        GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat no_shininess[] = { 0.0 };
        GLfloat low_shininess[] = { 5.0 };
        GLfloat high_shininess[] = { 100.0 };
        GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};//que luz va a emitir
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        
   
        glutSolidTeapot(1);
        glColor3ub(0, 0, 0);
        glutWireTeapot(1);
        glPopMatrix();
    
        
        glColor3f(100, 24, 100);
        glRasterPos2d(-winWidth/3.2, 0);
        
        sprintf(ganar, "Felicidades!! Ganaste en %d turnos! ", turno);
        for(int i= 0; ganar[i]!='\0'; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ganar[i]);
        }
        
    }else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    
    cout<<estado<<endl;
    //TEXTO TURNOS
    glColor3f(255, 255, 255);
    sprintf(turnos, "Turnos: %d", turno);
    glRasterPos2d(-winWidth/1.07,-winHeight/1.5);
    for(int i = 0; turnos[i] != '\0'; i++)
    {
        
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, turnos[i]);
    }
    
    //TIEMPO
    glColor3f(100, 24, 100);
    glRasterPos2d(-winWidth/1.07, -winHeight/1.33);
    for(int i= 0; tiempo[i]!='\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tiempo[i]);
    }
    
    //TEXTO TECLADO
    glColor3f(100, 24, 100);
    glRasterPos2d(-winWidth/2.7,-winHeight/1.33);
    for(int i= 0; texto[i]!='\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
    
    //TEXTO ESC SALIR
    glColor3f(100, 24, 100);
    glRasterPos2d(winWidth/1.45,-winHeight/1.33);
    for(int i= 0; texto_esc_salir[i]!='\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto_esc_salir[i]);
    }
    
    //NOMBRES
    glColor3f(100, 24, 100);
    glRasterPos2d(-winWidth/4,-winHeight/3);
    for(int i= 0; nombreMontse[i]!='\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nombreMontse[i]);
    }
    
    glColor3f(100, 24, 100);
    glRasterPos2d(-winWidth/4.44,-winHeight/2.4);
    for(int i= 0; nombreAriana[i]!='\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nombreAriana[i]);
    }
    
    transparencia ();
    glLineWidth(1);
    
    glPopMatrix();
    glutSwapBuffers();
    
}

void reset()
{
    _num = 0;
    _stop = false;
    shuffle();
    turno = 0;
    estado = 0;
    carta1 = 0;
    carta2 = 0;
    carta3 = 0;
    ayuda = false;
    moveCamera = false;
    
    for (int i = 0; i < 24; i ++)
    {   expuesta[i] = false;
        colored[i] = false;
        angles[i] = 0;
        rotated[i] = false;
    }
    
    sprintf(tiempo, "0 : 00 : 0");
}

void stop()
{
    if(!_stop)
    {
        _stop = true;
        sonido.PauseSound();
    }else
    {
        _stop = false;
        sonido.PlaySound();
    }
}
void start()
{
    _stop = false;
    moveCamera = false;
    glutMouseFunc(mouse);
    glutTimerFunc(100, myTimer, 1);
}
void keyboardFunc(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27: //esc
            exit(0);
            break;
            
        case 'p':
        case 'P':
            stop();
            break;
            
        case 'i':
        case 'I':
            start();
            break;
            
        case 'r':
        case 'R':
            reset();
            break;
        case 'o':
        case 'O':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho (-winWidth, winWidth, -winHeight, winHeight, 4, 0);
            glMatrixMode(GL_MODELVIEW);
            glutPostRedisplay();
            break;
        case 'c':
        case 'C':
            if(moveCamera)
                moveCamera= false;
            else
                moveCamera = true;
            ChangeSize(800, 600);
            break;
        case 'f':
        case 'F':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-winWidth, winWidth, -winHeight, winHeight, 1,4);
            glMatrixMode(GL_MODELVIEW);//dejar activa son todas las traslaciones, escalaciones
            //glLoadIdentity();//que no tenga ninguna transformación
            glutPostRedisplay();
            break;
    }
    
    
}

void onMenu(int idEntry)
{
    switch (idEntry) {
        case 1: glClearColor(1.0,.6,0,0); glutPostRedisplay(); break;
        case 2: glClearColor(.8,.8,0,0); glutPostRedisplay(); break;
        case 3: start(); break;
        case 4: stop(); break;
        case 5: reset(); break;
        case 6: exit(0); break;
        case 7: ayuda = true; break;
        case 8: ayuda = false; break;
    }
}

void createMenus()
{
    int menuAutora, menuPrincipal, menuAyuda;
    menuAutora = glutCreateMenu(onMenu);
    glutAddMenuEntry("Montserrat Lozano A01088686", 1);
    glutAddMenuEntry("Ariana Cisneros A01138381", 2);
    
    menuAyuda = glutCreateMenu(onMenu);
    glutAddMenuEntry("Ver Ayuda", 7);
    glutAddMenuEntry("Ocultar Ayuda", 8);
    
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Autoras", menuAutora);
    glutAddMenuEntry("Iniciar", 3);
    glutAddMenuEntry("Pausa", 4);
    glutAddMenuEntry("Reiniciar", 5);
    glutAddSubMenu("Ayuda", menuAyuda);
    glutAddMenuEntry("Salir", 6);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat aspectRatio;
    
    if(h==0)  h=1; //si la altura que llego es 0.. Forzamos a que la altura sea minimo 0
    
    glViewport (0,0,w,h);
    
    //cambiar deltas con proporcion al nuevo tamaño de pantalla
    sepHor = (30*w/800);
    sepVert= (100*h/600);
    ancho = (100*w/800);
    alto = (200*h/600);
    deltaRect = (67*w)/800;
    deltaHeight = (200*h)/600;
    deltaHeight2 = (400*h)/600;
    xRaster = (-770*w)/800;
    yRaster = (-100*h)/600;
    scaleX = (.9*w)/800;
    scaleY = (.9*h)/600;
    winWidth = w;
    winHeight = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //limpiar matriz de proyeccion
    glFrustum(-winWidth, winWidth, -winHeight, winHeight, 1,4);
    glMatrixMode(GL_MODELVIEW);//dejar activa son todas las traslaciones, escalaciones
    glLoadIdentity();//que no tenga ninguna transformación
    
    if(moveCamera)
    {
        gluLookAt(0, 0, 1.1, 0, 0, 0, 0, 1, 0);
    }else{
        gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    }
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth,winHeight);
    glutInitWindowPosition(200, 400); // 100, 100
    glutCreateWindow("Memorama");
    glutTimerFunc(0,sound,0);
    init();
    createMenus();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardFunc);
    glutMainLoop();
    return 0;
}