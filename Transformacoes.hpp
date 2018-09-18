
#ifndef TRANSFORMACOES_HPP
#define TRANSFORMACOES_HPP

#include <glm/mat4x4.hpp>

using namespace std;
using namespace glm;

class Transformacoes{

public:

    ///Construtores
    Transformacoes();

    ///Variaveis

    ///Funcoes

    mat4 getRotacao( );
    void setRotacao( float rX, float rY, float rZ );

    mat4 getTranslacao( );
    void setTranslacao( float tX, float tY, float tZ );

    mat4 getEscala( );
    void setEscala( float sX, float sY, float sZ );

    mat4 getShear( );
    void setShear( float sX, float sY, float sZ );

    mat4 getAllTransformations( );


private:

    ///Variaveis
    mat4 rotacao;
    mat4 translacao;
    mat4 escala;
    mat4 shear;


    ///Funcoes
    void inicialize();



};

#endif // TRANSFORM_H


