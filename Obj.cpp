
#include "Obj.hpp"

#include <iostream>
#include <fstream>


using namespace std;

    ///Construtores
    Obj::Obj(){
        cout << "Objeto instanciado" << endl;

        //loadout = objl::load.LoadFile("cubo.obj");


        criarLista(&vertex);
        criarLista(&aresta);
        carregaVertece();
        carregaAresta();
    }

    ///Variaveis


    ///Funcoes
    void Obj::carregaVertece(){

        cout<< "Carregando Vertice" << endl;

        adicionaElemento( &vertex, { -1, -1, -1, 1 } );
        adicionaElemento( &vertex, { -1, -1,  1, 1 } );
        adicionaElemento( &vertex, {  1, -1, -1, 1 } );
        adicionaElemento( &vertex, {  1, -1,  1, 1 } );
        adicionaElemento( &vertex, { -1,  1, -1, 1 } );
        adicionaElemento( &vertex, { -1,  1,  1, 1 } );
        adicionaElemento( &vertex, {  1,  1, -1, 1 } );
        adicionaElemento( &vertex, {  1,  1,  1, 1 } );

    }

    void Obj::carregaAresta(){

        cout<< "Carregando Aresta" << endl;

        ///**   Lista de aresta

        //bottom
        adicionaElemento( &aresta, { 0, 1, 0, 0 } );
        adicionaElemento( &aresta, { 0, 2, 0 ,0 } );
        adicionaElemento( &aresta, { 1, 3, 0 ,0 } );
        adicionaElemento( &aresta, { 2, 3, 0 ,0 } );

        //top
        adicionaElemento( &aresta, { 4, 5, 0, 0 } );
        adicionaElemento( &aresta, { 4, 6, 0 ,0 } );
        adicionaElemento( &aresta, { 5, 7, 0 ,0 } );
        adicionaElemento( &aresta, { 6, 7, 0 ,0 } );

        // vert

        adicionaElemento( &aresta, { 0, 4, 0, 0 } );
        adicionaElemento( &aresta, { 1, 5, 0 ,0 } );
        adicionaElemento( &aresta, { 2, 6, 0 ,0 } );
        adicionaElemento( &aresta, { 3, 7, 0 ,0 } );

    }

