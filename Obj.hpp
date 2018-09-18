
#ifndef OBJ_HPP
#define OBJ_HPP

#include "Transformacoes.hpp"
#include "Lista.hpp"
#include <glm/mat4x4.hpp>


class Obj{

public:

    ///Construtores
    Obj();

    Transformacoes t;
    tLista vertex;
    tLista aresta;


    ///Funcoes


private:

    ///Funcoes
    void carregaVertece();

    void carregaAresta();

};

#endif // OBJ_H

