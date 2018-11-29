#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"

class Aresta
{
    public:
        Aresta();
        Aresta(Vertice* origem, Vertice* destino);
        virtual ~Aresta();
        Vertice* getOrigem();
        Vertice* getDestino();
    protected:

    private:
        Vertice* origem;
        Vertice* destino;
};

#endif // ARESTA_H
