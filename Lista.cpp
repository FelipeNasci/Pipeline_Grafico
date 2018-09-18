
#include "Lista.hpp"


/* CRIAR uma lista */
void criarLista( tLista *lista ){

    lista -> contador = 0;

    printf("Lista Criada");

}

/* Verificar se a lista esta CHEIA */
short verificaListaCheia ( tLista *lista ){

    if(lista -> contador == MAX )
        return 1;

    return 0;

}

/* Verificar se a lista esta VAZIA */
short verificaListaVazia ( tLista *lista ){

    if(lista -> contador == 0 ){

        return 1;

    } else{

        return 0;
    }
}

/* Exibe o tamanho da lista */
short tamanho (tLista *lista){

    return lista ->contador;

}



/* Adiciona um elemento sempre no final da lista */
short adicionaElemento ( tLista *lista , glm::vec4 elemento ){

    if(verificaListaCheia ( lista ) == 1){

return 0;

        } else {

            lista -> dados[lista->contador] = elemento;
            lista-> contador++;

return 1;

        }
}

/* Modifica o valor em determinada posicao */
short modificarValorPosicao( tLista *lista , int posicao, glm::vec4 elemento ){

    if (posicao > (lista->contador) || posicao < 0)

return 0;

    else

        lista->dados[posicao] = elemento;

return 1;

}




/* Obtem o valor em determinada posicao */
glm::vec4 obterValor( tLista *lista, int posicao ){

    glm::vec4 vetorNulo(0,0,0,0);

        if(posicao > (lista->contador) || posicao < 0 )
            return vetorNulo;
        else
            return lista->dados[posicao];
}

void copiaLista (tLista *lista1, tLista *lista2){
    glm::vec4 vetor;

    for(int i = 0; i < tamanho(lista1); i++){
        vetor = obterValor(lista1, i);
        adicionaElemento( lista2, vetor );
    }

}


