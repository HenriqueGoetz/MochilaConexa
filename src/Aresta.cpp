#include "Aresta.h"

Aresta::Aresta()
{
    //ctor
}

Aresta::Aresta(Vertice* origem, Vertice* destino)
{
    this->origem = origem;
    this->destino = destino;
}

Aresta::~Aresta()
{
    //dtor
}

Vertice* Aresta::getOrigem(){
    return this->origem;
}

Vertice* Aresta::getDestino(){
    return this->destino;
}
