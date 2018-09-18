
#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

/******************************************************/
/*******  ALGORITMO DE BRESENHAM - PONTO MEDIO  *******/
/*******    PARA RASTERIZAR LINHAS UTILIZANDO   *******/
/*******          APENAS NUMEROS INTEIROS       *******/
/******************************************************/

void drawLine(Point pointA, Point pointB)
{

    if(pointA.x > pointB.x){
        drawLine(pointB, pointA);
        return;
    }

    int dx = pointB.x - pointA.x;
    int dy = pointB.y - pointA.y;

    if(abs(dx) >= abs(dy))
        dxdy(pointA, pointB);
    else
        dydx(pointA, pointB);
}

void dxdy(Point pointA, Point pointB)
{

    int dy = pointB.y - pointA.y;
    int dx = pointB.x - pointA.x;

    if(dy > 0){

        int d_new = 2*dy - dx;
        int inc_E = 2*dy;
        int inc_NE = 2*dy - 2*dx;

        while(pointA.x <= pointB.x){

            putPixel(pointA);
            pointA.x++;

            if (d_new < 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointA.y ++;
            }

            interpolaCor (&pointA, pointB);
        }
    }
    else{

        int d_new = 2 * dy + dx;
        int inc_E = 2 * dy;
        int inc_NE = 2 * dy + 2 * dx;

            while(pointA.x <= pointB.x){

            putPixel(pointA);
            pointA.x++;

            if (d_new > 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointA.y--;
            }

            interpolaCor (&pointA, pointB);
        }

    }


}

void dydx (Point pointA, Point pointB)
{

    int dy = pointB.y - pointA.y;
    int dx = pointB.x - pointA.x;

    if(dy >= 0){

        int d_new = dy - 2* dx;
        int inc_E = -2*dx;
        int inc_NE = 2*dy - 2*dx;

        while(pointA.y <= pointB.y){

            putPixel(pointA);
            pointA.y++;

            if (d_new > 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointA.x++;
            }

            interpolaCor (&pointA, pointB);
        }

    }
    else{

        int d_new = dy + 2*dx;
        int inc_E = 2*dx;
        int inc_NE = 2*dy + 2*dx;

        while(pointA.y >= pointB.y){

            putPixel(pointA);
            pointA.y--;

            if (d_new < 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointA.x ++;
            }

            interpolaCor (&pointA, pointB);
        }


    }

}


/******************************************************/
/*******    INTERPOLA CORES ENTRE OS PONTOS     *******/
/******************************************************/

void interpolaCor(Point *pointA, Point pointB)
{

    Color cor_aux;

    int dx = pointB.x - pointA -> x;            //  Distancia do ponto x inicial ate o final
    int dy = pointB.y - pointA -> y;            //  Distancia do ponto y inicial ate o final

    float distance;

        if( abs(dx) >= abs(dy) )                //  Em alguns casos (dependendo do angulo da reta)
            distance = (float) abs(dx);         //  dy ou dx podem assumir valores negativos
        else                                    //  O que prejudica a interpolacao de algumas retas
            distance = (float) abs(dy);


    /************************************************************************/
    /*****                 A COR AUXILIAR EH IGUAL A:                   *****/
    /*****  ( COR_PONTO_A - COR_PONTO_B ) / DISTANCIA ENTRE OS PONTOS   *****/
    /************************************************************************/

    cor_aux.r = nearbyint( ( pointB.color.r - pointA -> color.r ) / distance );
    cor_aux.g = nearbyint( ( pointB.color.g - pointA -> color.g ) / distance );
    cor_aux.b = nearbyint( ( pointB.color.b - pointA -> color.b ) / distance );
    cor_aux.a = nearbyint( ( pointB.color.a - pointA -> color.a ) / distance );

    /************************************************************************/
    /*****  SE A COR NO PONTO_A FOR NEGATIVA OU MAIOR QUE 255 SIGNIFICA *****/
    /*****  QUE FOI ESTRAPOLADO O LIMITE DE BYTES NA MEMORIA, OU SEJA,  *****/
    /*****          GERA DISCREPANCIA DE CORES NA INTERPOLACAO          *****/
    /************************************************************************/

    if (pointA ->color.r < 0 || pointA -> color.r > 255)
        pointA -> color.r = pointB.color.r;
    else
        pointA -> color.r += cor_aux.r;

    if (pointA ->color.g < 0 || pointA -> color.g > 255)
        pointA -> color.g = pointB.color.g;
    else
        pointA -> color.g += cor_aux.g;

    if (pointA ->color.b < 0 || pointA -> color.b > 255)
        pointA -> color.b = pointB.color.b;
    else
        pointA -> color.b += cor_aux.b;

    if (pointA ->color.a < 0 || pointA -> color.a > 255)
        pointA -> color.a = pointB.color.b;
    else
        pointA -> color.a += cor_aux.a;

}


/******************************************************/
/*******       DESENHA TRIANGULOS NA TELA       *******/
/******************************************************/

void drawTriangle(Point pointA, Point pointB, Point pointC, short fill_)
{

    if(fill_)
        fill_Triangle(pointA, pointB, pointC);
    else{
        drawLine(pointA, pointB);
        drawLine(pointA, pointC);
        drawLine(pointB, pointC);
    }

}


/******************************************************/
/*******     PREENCHE UM TRIANGULO DADO         *******/
/*******            DETERMINADA COR             *******/
/******************************************************/

void fill_Triangle( Point pointA, Point pointB, Point pointC )
{

if( pointB.x > pointC.x ){

        fill_Triangle(  pointA, pointC, pointB );
        return;
    }

    drawLine(pointA, pointB);

    int dx, dy, inc_E, inc_NE, d_new;
    short slope = 1;

    dy = pointC.y - pointB.y;
    dx = pointC.x - pointB.x;

    if( abs(dx) >= abs(dy))
    {
        if( dy < 0){
            slope = -slope;
            dy = -dy;
        }

        d_new = 2*dy - dx;
        inc_E = 2*dy;
        inc_NE = 2*dy - 2*dx;

        while(pointB.x <= pointC.x){


            pointB.x++;

            if (d_new < 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointB.y += slope;
            }
                drawLine(pointA, pointB);

        }
    }
    else
    {
        if(dy > 0)
            slope = -1;

        d_new = dy + slope * 2*dx;
        inc_E = slope * 2*dx;
        inc_NE = 2*dy + slope * 2*dx;


        if(slope < 0){
            inc_E = -inc_E;
            inc_NE = -inc_NE;
        }

        while(pointB.y != pointC.y){

            pointB.y += -slope;

            if (d_new < 0)
                d_new += inc_E;
            else{
                d_new += inc_NE;
                pointB.x ++;
            }

           drawLine(pointA, pointB);
        }
    }


}


/******************************************************/
/*******     PLOTA O PIXEL DE DETERMINADA       *******/
/*******            COR NA TELA                 *******/
/******************************************************/

void putPixel(Point point)
{
    if ( point.x < 0|| point.y < 0 || point.x > IMAGE_WIDTH || point.y > IMAGE_HEIGHT  )
        return;

    FBptr[offset(point) + RED] = point.color.r;
    FBptr[offset(point) + GREEN] = point.color.g;
    FBptr[offset(point) + BLUE] = point.color.b;
    FBptr[offset(point) + ALPHA] = point.color.a;
}


/******************************************************/
/*******  RETORNA A POSICAO NO COLOR_BUFFER DE  *******/
/*******        ACORDO COM AS COORDENADAS       *******/
/******************************************************/

unsigned int offset(Point point)
{
    return point.x * 4 + point.y * IMAGE_WIDTH * 4;
}

/******************************************************/
/*******     LIMPA A TELA COM UMA COR           *******/
/*******            PREDEFINIDA                 *******/
/******************************************************/

void clearScreen(Color cor){

    Point p;

    p.color = cor;

    for(p.y = 0; p.y < IMAGE_HEIGHT; p.y++)
        for (p.x = 0; p.x < IMAGE_WIDTH; p.x++)
            putPixel(p);

}

#endif // _MYGL_H_


