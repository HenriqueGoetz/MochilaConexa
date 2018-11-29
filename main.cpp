#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "Vertice.h"
#include "Aresta.h"


using namespace std;

void imprimeSolucaoAtual(vector<Vertice*> vertices){

    float valores = 0;
    float pesos = 0;

    cout<<"   **********************************************"<<endl;
    cout<<"   ************    Solucao Atual     ************"<<endl;
    cout<<"   **********************************************"<<endl;

    for(unsigned i = 0; i < vertices.size(); i++){
        pesos = pesos + vertices[i]->getPeso();
        valores = valores + vertices[i]->getValor();
        cout << "   *   " << i+1 << " - Valor:\t" << vertices[i]->getValor() <<"\tPeso:\t" << vertices[i]->getPeso()<< "\t*" << endl;
    }
    cout<<"   **********************************************"<<endl;
    cout <<"   *    Valor Total: " << valores << "\t Peso Total: " << pesos << "\t\t*" << endl;
    cout<<"   **********************************************"<<endl;
    cout<<endl;
}


void imprimeSolucaoFinal(vector<Vertice*> vertices){

    float valores = 0;
    float pesos = 0;
    cout<<endl;
    cout<<endl;
    cout<<"   **********************************************"<<endl;
    cout<<"   ************    Melhor Solucao    ************"<<endl;
    cout<<"   **********************************************"<<endl;

    for(unsigned i = 0; i < vertices.size(); i++){
        pesos = pesos + vertices[i]->getPeso();
        valores = valores + vertices[i]->getValor();
        cout << "   *   " << i+1 << " - Valor:\t" << vertices[i]->getValor() <<"\tPeso:\t" << vertices[i]->getPeso()<< "\t*" << endl;
    }
    cout<<"   **********************************************"<<endl;
    cout <<"   *    Valor Total: " << valores << "\t Peso Total: " << pesos << "\t\t*" << endl;
    cout<<"   **********************************************"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}



vector<Vertice*> geraSolucaoInicial(vector<Vertice*> vertices, float limite){
    vector<Vertice*> v;

    for(unsigned i = 0; i < vertices.size(); i++){
            if(vertices[i]->getPeso()<=limite){
                v.push_back(vertices[i]);
                return v;
            }
    }

    return v;
}

bool UltrapassaLimite(vector<Vertice*> solucao, Vertice* vertice, float limite){

    float acumulado = 0;

    for(unsigned i = 0; i < solucao.size(); i++){
        acumulado = acumulado + solucao[i]->getPeso();
    }

    if (acumulado + vertice->getPeso()>limite){
        return true;
    }

    return false;
}

bool EstaNaSolucao(vector<Vertice*> solucao, Vertice* vertice){

    for(unsigned i = 0; i < solucao.size(); i++){
        if(solucao[i]==vertice){
            return true;
        }
    }

    return false;
}

vector<Vertice*> buscaLocal(vector<Vertice*> solucao, vector<Aresta*> arestas, float limite){
    vector<Vertice*> possiveisInclusoes;

    for(unsigned i = 0; i < solucao.size(); i++){
        for(unsigned j =0; j < arestas.size(); j++){
            if(solucao[i] == arestas[j]->getOrigem() && !EstaNaSolucao(solucao, arestas[j]->getDestino()) && !UltrapassaLimite(solucao, arestas[j]->getDestino(), limite)){
                    possiveisInclusoes.push_back(arestas[j]->getDestino());
            }else
                if(solucao[i] == arestas[j]->getDestino() && !EstaNaSolucao(solucao, arestas[j]->getOrigem()) && !UltrapassaLimite(solucao, arestas[j]->getOrigem(), limite)){
                    possiveisInclusoes.push_back(arestas[j]->getOrigem());
                    }
        }
    }

    while(possiveisInclusoes.size()>0){

        int indice = 0;
        float maisVantajoso = possiveisInclusoes[0]->getValor() / possiveisInclusoes[0]->getPeso();

        for(unsigned i = 1; i < possiveisInclusoes.size(); i++){
            if(maisVantajoso < (possiveisInclusoes[i]->getValor()/ possiveisInclusoes[i]->getPeso())){
                maisVantajoso = possiveisInclusoes[i]->getValor()/ possiveisInclusoes[i]->getPeso();
                indice = i;
            }
        }

        solucao.push_back(possiveisInclusoes[indice]);

        possiveisInclusoes.clear();

        for(unsigned i = 0; i < solucao.size(); i++){
            for(unsigned j =0; j < arestas.size(); j++){
                if(solucao[i] == arestas[j]->getOrigem() && !EstaNaSolucao(solucao, arestas[j]->getDestino()) && !UltrapassaLimite(solucao, arestas[j]->getDestino(), limite)){
                    possiveisInclusoes.push_back(arestas[j]->getDestino());
                }else
                    if(solucao[i] == arestas[j]->getDestino() && !EstaNaSolucao(solucao, arestas[j]->getOrigem()) && !UltrapassaLimite(solucao, arestas[j]->getOrigem(), limite)){
                        possiveisInclusoes.push_back(arestas[j]->getOrigem());
                    }
            }
        }
    }

    return solucao;
}

vector<Vertice*> perturbacao(vector<Vertice*> vertices){

    vector<Vertice*> v ;
    int indice = rand() % vertices.size();
    vertices.erase(vertices.begin() + indice);
    v = vertices;
    return v;
}

bool foiVisitado(vector<Vertice*> visitados, Vertice* vertice){

    for(unsigned i=0; i < visitados.size(); i++){
        if(visitados[i] == vertice){
            return true;
        }
    }
    return false;
}

vector<Vertice*> coletaVizinhos(vector<Vertice*> vizinhos, vector<Vertice*> vertices, vector<Aresta*> arestas, vector<Vertice*> visitados){

    vector<Vertice*> novosVizinhos = vizinhos;

    for(unsigned i = 0; i < arestas.size(); i++){
        if(vizinhos[0] == arestas[i]->getDestino() && !foiVisitado(visitados, arestas[i]->getOrigem())){
            if(EstaNaSolucao(vertices,arestas[i]->getOrigem())){
                novosVizinhos.push_back(arestas[i]->getOrigem());
            }
        }else
            if(vizinhos[0] == arestas[i]->getOrigem() && !foiVisitado(visitados, arestas[i]->getDestino())){
               if(EstaNaSolucao(vertices,arestas[i]->getDestino())){
                    novosVizinhos.push_back(arestas[i]->getDestino());
                }
            }
    }

    return novosVizinhos;
}

bool conexo(vector<Vertice*> vertices, vector<Aresta*> arestas){

    vector<Vertice*> vizinhos;
    vector<Vertice*> visitados;

    vizinhos.push_back(vertices[0]);

    //cout<< "conexo1" <<endl;

    while(vizinhos.size()>0){
        cout<<vizinhos.size()<<endl;
        long v = vizinhos.size();
        for(int i = 0; i < v; i++){
            visitados.push_back(vizinhos[i]);
            vizinhos = coletaVizinhos(vizinhos, vertices, arestas, visitados);
            vizinhos.erase(vizinhos.begin());
            cout<< i<<endl;
        }
    }

    cout<< "________" <<endl;

    if(visitados.size() == vertices.size()){
        return true;
    }

    return false;
}

bool aceitacao(vector<Vertice*> vertices, vector<Aresta*> arestas, float limite){

    float pesos=0;

    for(unsigned i = 0 ; i < vertices.size(); i++){
        pesos = pesos + vertices[i]->getPeso();
    }

    if(pesos > limite)
        return false;

    //cout<<"Aceitacao1"<<endl;
    if(!conexo(vertices, arestas))
        return false;

    //cout<<"Aceitacao2"<<endl;

    return true;
}

float calculaValor(vector<Vertice*> vertices){

    float valor = 0;

    for(unsigned i = 0; i < vertices.size(); i++){
        valor = valor + vertices[i]->getValor();
    }

    return valor;
}
int main()
{
    int criterio = 0;
    float limite = 31;

    vector<Aresta*> arestas;
    vector<Vertice*> vertices;
    vector<Vertice*> solucao;
    vector<Vertice*> melhorSolucao;

    srand(time(0));

    /*
    vertices.push_back(new Vertice(10,5));
    vertices.push_back(new Vertice(5,4));
    vertices.push_back(new Vertice(1,8));
    vertices.push_back(new Vertice(15,10));
    vertices.push_back(new Vertice(3,6));
    arestas.push_back(new Aresta(vertices[0],vertices[1]));
    arestas.push_back(new Aresta(vertices[1],vertices[4]));
    arestas.push_back(new Aresta(vertices[2],vertices[3]));
    arestas.push_back(new Aresta(vertices[1],vertices[2]));
    arestas.clear();
    vertices.clear();
    */

    //Leitura de arquivo.
    string line, delimiter = " ";
    ifstream myfile("moc01");
    int nVertices, mArestas;
    if (myfile.is_open()){
        while (!myfile.eof()){
            getline(myfile,line);
            nVertices = stoi(line.substr(0,line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());
            mArestas = stoi(line.substr(0,line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());
            limite = stof(line.substr(0,line.find(delimiter)));

            cout << nVertices << endl;
            cout << mArestas << endl;
            cout << limite << endl;
            getline(myfile,line);

            for(int i = 0; i < nVertices; i++){
                vertices.push_back(new Vertice(stof(line.substr(0,line.find(delimiter)))));
                line.erase(0, line.find(delimiter) + delimiter.length());
            }
            getline(myfile,line);
            for(int i = 0; i < nVertices; i++){
                vertices[i]->setValor(stof(line.substr(0,line.find(delimiter))));
                line.erase(0, line.find(delimiter) + delimiter.length());

            }

            for(int i = 0; i < mArestas; i++){
                getline(myfile,line);
                unsigned origem = stoi(line.substr(0,line.find(delimiter)));
                line.erase(0, line.find(delimiter) + delimiter.length());
                arestas.push_back(new Aresta(vertices[origem], vertices[stoi(line.substr(0,line.find(delimiter)))]));
            }

            while(!myfile.eof()){
                getline(myfile,line);
            }
        }
        myfile.close();
    }else
        cout << "Unable to open file" << endl;


    solucao = geraSolucaoInicial(vertices, limite);

    imprimeSolucaoAtual(solucao);

    solucao = buscaLocal(solucao, arestas, limite);

    imprimeSolucaoAtual(solucao);

    melhorSolucao = solucao;

    while(criterio < 100){
        vector<Vertice*> novaSolucao = perturbacao(solucao);

        novaSolucao = buscaLocal(novaSolucao, arestas, limite);

        //imprimeSolucaoAtual(novaSolucao);
       if(aceitacao(novaSolucao, arestas, limite)){
            solucao = novaSolucao;
            if(calculaValor(melhorSolucao)<calculaValor(novaSolucao)){
                melhorSolucao = novaSolucao;
                criterio = 0;
            }else{
                 if(calculaValor(melhorSolucao)==calculaValor(novaSolucao)){
                    criterio++;
                    }
            }
        }

    }

    cout << "Final" << endl;
    imprimeSolucaoFinal(melhorSolucao);

    return 0;
}

