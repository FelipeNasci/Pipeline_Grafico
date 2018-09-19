#include "main.h"

static GLfloat rX = 0, rY = 0, rZ = 0;
static GLfloat tX = 0, tY = 0, tZ = 0;

static Obj objeto;

//-----------------------------------------------------------------------------
void Bresenham_Test();

void MyGlDraw(void) {

    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //************************************************************************



    objeto.t.setRotacao(0,rY,0);  //add ROTACAO nos 03 eixos
    //objeto.t.setEscala(1,1,5);
    //objeto.t.setTranslacao(rX,0,0);  //add TRANSLACAO nos 03 eixeos

    rX += 0.01;
    rY += 0.01;
    rZ += 0.01;


    pipeline( objeto );
   // Bresenham_Test();
}

void Bresenham_Test()
{
    Point axis, axis1;
    Point  p1, p2;

    /////////////////////////////////
    //          EIXO X             //
    /////////////////////////////////
    axis.x = IMAGE_WIDTH / 2;
    axis.y = IMAGE_HEIGHT / 2;

    //  COR
    axis.color.r = 0;
    axis.color.g = 255;
    axis.color.b = 255;

    axis1.x = IMAGE_WIDTH;
    axis1.y = IMAGE_HEIGHT / 2;

    //  COR
    axis1.color.r = 0;
    axis1.color.g = 0;
    axis1.color.b = 255;

    drawLine(axis,axis1);       //  DESENHA A LINHA

    axis1.x = 0;
    axis1.y = IMAGE_HEIGHT / 2;

    drawLine(axis,axis1);

    /////////////////////////////////
    //            EIXO Y           //
    /////////////////////////////////

    axis.x = IMAGE_WIDTH / 2;
    axis.y = IMAGE_HEIGHT / 2;

    axis1.x = IMAGE_WIDTH / 2;
    axis1.y = IMAGE_HEIGHT;

    drawLine(axis,axis1);

    axis1.x = IMAGE_WIDTH / 2;
    axis1.y = 0;

    drawLine(axis,axis1);


    //////////////////////////////////
    //  SEPARACAO DE QUADRANTES     //
    //////////////////////////////////

    p1.color.r = 0;
    p1.color.g = 150;
    p1.color.b = 255;

    p2.color.r = 180;
    p2.color.g = 255;
    p2.color.b = 0;

    p1.x = IMAGE_WIDTH / 2;
    p1.y = IMAGE_HEIGHT / 2;


    p2.x = IMAGE_WIDTH;
    p2.y = IMAGE_HEIGHT;
    drawLine(p1,p2);

    p2.x = 0;
    p2.y = 0;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH;
    p2.y = 0;
    drawLine(p1,p2);

    p2.x = 0;
    p2.y = IMAGE_HEIGHT;
    drawLine(p1,p2);

    ///////////////////////////////////
    //  SEPARACAO DE OCTANTES        //
    //////////////////////////////////

    p2.x = IMAGE_WIDTH / 4;
    p2.y = 0;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH / 4;
    p2.y = IMAGE_HEIGHT;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH / 4 + IMAGE_WIDTH / 2;
    p2.y = 0;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH / 4 + IMAGE_WIDTH / 2;
    p2.y = IMAGE_HEIGHT;
    drawLine(p1,p2);

    p2.x = 0;
    p2.y = IMAGE_HEIGHT / 4;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH;
    p2.y = IMAGE_HEIGHT / 4;
    drawLine(p1,p2);

    p2.x = 0;
    p2.y = IMAGE_HEIGHT / 4 + IMAGE_HEIGHT / 2;
    drawLine(p1,p2);

    p2.x = IMAGE_WIDTH;
    p2.y = IMAGE_HEIGHT / 4 + IMAGE_HEIGHT / 2;
    drawLine(p1,p2);

}

//-----------------------------------------------------------------------------

int main(int argc, char **argv) {

    // Inicializações.
    InitOpenGL(&argc, argv);
    InitCallBacks();
    InitDataStructures();

    // Ajusta a função que chama as funções do mygl.h
    DrawFunc = MyGlDraw;

    // Framebuffer scan loop.
    glutMainLoop();

    return 0;
}


