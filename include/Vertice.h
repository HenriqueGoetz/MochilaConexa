#ifndef VERTICE_H
#define VERTICE_H


class Vertice
{
    public:
        Vertice();
        Vertice(float peso);
        Vertice(float valor, float peso);
        virtual ~Vertice();
        float getPeso();
        float getValor();
        void setValor(float valor);
    protected:

    private:
        float valor;
        float peso;

};

#endif // VERTICE_H
