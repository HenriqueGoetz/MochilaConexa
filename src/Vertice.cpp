#include "Vertice.h"

Vertice::Vertice()
{
    //ctor
}


Vertice::Vertice(float valor, float peso)
{
    this->valor = valor;
    this->peso = peso;
}

Vertice::Vertice(float peso)
{
    this->peso = peso;
}


Vertice::~Vertice()
{
    //dtor
}

float Vertice::getPeso(){
    return this->peso;
}

float Vertice::getValor(){
    return this->valor;
}

void Vertice::setValor(float valor){
    this->valor = valor;
}
