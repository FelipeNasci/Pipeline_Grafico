#include "Transformacoes.hpp"
#include <iostream>

using namespace std;


    ///Construtores
    Transformacoes::Transformacoes(){
        cout << "hello Transform" << endl;
        inicialize();
    }

    ///Variaveis


    ///Funcoes

    mat4 Transformacoes::getRotacao( ){
        return this->rotacao;
    }

    void Transformacoes::setRotacao( float rX, float rY, float rZ ){

        //Matrizes de rotacao

        mat4 rotateX   (1,  0,          0,          0,
                        0,  cos(rX),    -sin(rX),   0,
                        0,  sin(rX),    cos(rX),    0,
                        0,  0,          0,          1 );

        mat4 rotateY   (cos(rY),    0,  sin(rY),    0,
                        0,          1,  0,          0,
                        -sin(rY),   0,  cos(rY),    0,
                        0,          0,  0,          1 );

        mat4 rotateZ   (cos(rZ),    -sin(rZ),   0,  0,
                        sin(rZ),    cos(rZ),    0,  0,
                        0,          0,          1,  0,
                        0,          0,          0,  1 );

        this->rotacao = rotateX * rotateY * rotateZ;

    }


    mat4 Transformacoes::getTranslacao( ){

    return this->translacao;

    }

    void Transformacoes::setTranslacao( float tX, float tY, float tZ ){

        //Matriz de Translacao

        this->translacao = {1.0f, 0.0f, 0.0f, tX,
                            0.0f, 1.0f, 0.0f, tY,
                            0.0f, 0.0f, 1.0f, tZ,
                            0.0f, 0.0f, 0.0f, 1.0f };
    }


    mat4 Transformacoes::getEscala( ){
        return this->escala;
    }

    void Transformacoes::setEscala( float sX, float sY, float sZ ){

        //Matriz de Escala

        this->escala = {  sX, 0.0f, 0.0f, 0,
                        0.0f,   sY, 0.0f, 0,
                        0.0f, 0.0f,   sZ, 0,
                        0.0f, 0.0f, 0.0f, 1.0f };

    }

    //mat4 Transformacoes::setShear( );
    //void Transformacoes::setShear( float sX, float sY, float sZ );

    mat4 Transformacoes::getAllTransformations( ){
        return getRotacao() * getTranslacao() * getEscala();
    }


    void Transformacoes::inicialize(){

        setRotacao( 0, 0, 0 );
        setTranslacao( 0, 0, 0 );
        setEscala( 1,1,1 );
    }





