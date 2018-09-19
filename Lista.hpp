#ifndef LISTA_H
#define LISTA_H

#define TRUE 1
#define FALSE 0
#define MAX 3000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Biblioteca Externa
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

    typedef struct tLista{

        glm::vec4 dados[MAX];
        int contador;

    }tLista;

/* CRIAR uma lista */
void criarLista( tLista *lista ); //ok


/* Verificar se a lista esta CHEIA */
short verificaListaCheia ( tLista *lista ); //ok

/* Verificar se a lista esta VAZIA */
short verificaListaVazia ( tLista *lista ); //ok

/* Exibe o tamanho da lista */
short tamanho ( tLista *lista ); //ok


/* Obtem o valor em determinada posicao */
glm::vec4 obterValor( tLista *lista, int posicao );

/* Modifica o valor em determinada posicao */
short modificarValorPosicao( tLista *lista , int posicao, glm::vec4 elemento );

/* Remove um elemento a lista */
short removeElemento ( tLista *lista , int posicao ); //ok


/* Adiciona um elemento sempre no final da lista */
short adicionaElemento ( tLista *lista , glm::vec4 elemento );

/* Adiciona um elemento a lista */
short adicionaElementoMeio ( tLista *lista , int posicao, int elemento ); //ok

void copiaLista (tLista *lista1, tLista *lista2);



#endif // LISTA_H

