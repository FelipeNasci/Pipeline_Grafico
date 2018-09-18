#ifndef PIPELINE_H
#define PIPELINE_H

#include "definitions.h"
#include "mygl.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace glm;

int control = 0;

///Parametros da camera
GLfloat pX, pY, pZ;
GLfloat lX,lY,lZ;
GLfloat uX,uY,uZ;

///Parametro da Projecao
GLfloat d_clip;

static Obj obj;


void showVector(glm::vec4 vec){
    printf("\n");
    for (int i = 0; i < vec.length(); i++){
        printf("\t\t");
        cout <<  vec[i] << endl;

    }
}


void space_Obj( Obj objeto ){
    obj = objeto;
}

mat4 space_World( mat4 transformations ){

    mat4 universe  (1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f );

    mat4 M_model = universe  * transformations;

    return M_model;
}

mat4 space_Camera(){

    ///Parametros da camera

    vec3 position (pX, pY, pZ);             //  Posicao da camera no universo.
    vec3 lookAt (lX,lY,lZ);                 //  Ponto para onde a camera esta olhando.
    vec3 up (uX,uY,uZ);                     //  'up' da camera no espaco do universo.
    vec4 homogenious (0,0,0,1);

    vec3 direction ( lookAt - position );   //  Para onde a camera esta olhando

    //auxilia no calculo da base
    vec3 zAux ( -(direction) / length(direction) );                 //Normalizando vetor de direcao
    vec3 xAux ( cross(   up, zAux ) / length( cross( up,zAux ) ) );
    vec3 yAux ( cross( zAux, xAux ) );

    ///Base da Camera
    vec4 Xc ( xAux , 0 );
    vec4 Yc ( yAux , 0 );
    vec4 Zc ( zAux , 0 );

    mat4 Bt (Xc,
             Yc,
             Zc,
             homogenious);

    mat4 T( 1, 0, 0, -position[0],
            0, 1, 0, -position[1],
            0, 0, 1, -position[2],
            0, 0, 0, 1);

    mat4 M_view ( T * Bt );
    mat4 M_modelView ( M_view);

    return M_modelView;

}

mat4 space_Clipping(){

    GLfloat d = d_clip;

    mat4 M_projection ( 1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, d,
                        0, 0, -(1/d), 0);

    mat4 M_modelViewProjection ( M_projection );

    return M_modelViewProjection;

}

void space_Canonical(mat4 screen){

    vec4 vertObj;
    GLfloat cood_w;

    for (int i = 0; i < tamanho(&obj.vertex); i++){

        vertObj = obterValor(&obj.vertex, i);       // Obtem o conj. de vertices da posicao i
        vertObj = vertObj * screen;                 // Multiplica os vertices pelas coord de Tela
        vertObj = vertObj / vertObj[3];             // Obtem a coordenada w para desHomogenizar
        modificarValorPosicao (&obj.vertex, i, vertObj );

    }

}

mat4 space_Screen(){

    GLfloat w = (IMAGE_WIDTH - 1)/2 ;
    GLfloat h = (IMAGE_HEIGHT - 1)/2 ;

    mat4 S1 (1, 0,  0, 0,
             0, -1, 0, 0,
             0, 0,  1, 0,
             0, 0,  0, 1 );

    mat4 T2 (1, 0, 0, 1,
             0, 1, 0, 1,
             0, 0, 1, 0,
             0, 0, 0, 1 );

    mat4 S2 (w, 0, 0, 0,
             0, h, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1 );

    mat4 M_viewPort( S1 * T2 * S2 );

    return M_viewPort;

}

void screen(){

    Point pointA;
    Point pointB;

    int posicao1, posicao2;

    vec4 aresta, aux;

    for (int i = 0; i < tamanho(&obj.aresta); i++){

        aresta = obterValor(&obj.aresta, i);

        posicao1 = aresta[0];
        posicao2 = aresta[1];

        aux = obterValor( &obj.vertex, posicao1 );

            pointA.x = round( aux[0] );
            pointA.y = round( aux[1] );

        aux = obterValor( &obj.vertex, posicao2 );

            pointB.x = round( aux[0] );
            pointB.y = round( aux[1] );

            //printf("Ponto A = (%d, %d) \n", pointA.x, pointA.y);
            //printf("Ponto B = (%d, %d) \n", pointB.x, pointB.y);

            drawLine(pointA, pointB);
    }

}

void inicialize(){

    control = 1;

    pX = 0, pY = 0, pZ = 5;     //posicao da camera
    lX = 0, lY = 0, lZ = 0;     //lookat da camera
    uX = 0, uY = 1, uZ = 0;     //up da camera
    d_clip = 1;

}

void pipeline(Obj objeto){

    Color cor;

    cor.r = 0;
    cor.b = 0;
    cor.g = 0;
    clearScreen(cor);

    if (!control)
        inicialize();

    space_Obj(objeto);

    mat4 viewPort = ( space_World( obj.t.getAllTransformations() ) *
                     space_Camera() * space_Clipping() * space_Screen() );

    space_Canonical(viewPort);
    screen();

}

#endif // PIPELINE_H
