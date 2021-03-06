#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <math.h>

using namespace std;

//Classe Vértice
class Vertice{
    protected:
    private:
		int id;
        float valor;
        float peso;
    public:
Vertice(){
    //ctor
}
Vertice(float valor, float peso){
    this->valor = valor;
    this->peso = peso;
}
Vertice(int id, float peso){
    this->id = id;
	this->peso = peso;
}
Vertice(float peso){
    this->peso = peso;
}
~Vertice(){
    //dtor
}
int getId(){
    return this->id;
}
float getPeso(){
    return this->peso;
}
float getValor(){
    return this->valor;
}
void setValor(float valor){
    this->valor = valor;
}
};

// Classe Aresta
class Aresta{
    protected:
    private:
        Vertice* origem;
        Vertice* destino;
    public:
Aresta(){
}
Aresta(Vertice* origem, Vertice* destino){
    this->origem = origem;
    this->destino = destino;
}
~Aresta(){
}
Vertice* getOrigem(){
    return this->origem;
}

Vertice* getDestino(){
    return this->destino;
}
};

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

float calculaValor(vector<Vertice*> vertices){

    float valor = 0;

    for(unsigned i = 0; i < vertices.size(); i++){
        valor = valor + vertices[i]->getValor();
    }

    return valor;
}

float calculaPeso(vector<Vertice*> vertices){

    float peso = 0;

    for(unsigned i = 0; i < vertices.size(); i++){
        peso = peso + vertices[i]->getPeso();
    }

    return peso;
}

bool UltrapassaLimite(vector<Vertice*> solucao, Vertice* vertice, float limite){

    if (calculaPeso(solucao)+ vertice->getPeso()>limite){
        return true;
    }
    return false;
}

bool EstaNaSolucao(vector<Vertice*> solucao, Vertice* vertice){

    for(unsigned i = 0; i < solucao.size(); i++){
        if(solucao[i] == vertice){
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
            }else{
                if(solucao[i] == arestas[j]->getDestino() && !EstaNaSolucao(solucao, arestas[j]->getOrigem()) && !UltrapassaLimite(solucao, arestas[j]->getOrigem(), limite)){
                    possiveisInclusoes.push_back(arestas[j]->getOrigem());
                    }
            }
        }
    }

    while(possiveisInclusoes.size()>0){

        unsigned indice = 0;
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
                }else{
                    if(solucao[i] == arestas[j]->getDestino() && !EstaNaSolucao(solucao, arestas[j]->getOrigem()) && !UltrapassaLimite(solucao, arestas[j]->getOrigem(), limite)){
                        possiveisInclusoes.push_back(arestas[j]->getOrigem());
                        }
                }
            }
        }
    }

    return solucao;
}

vector<Vertice*> removeVertice(vector<Vertice*> vertices, unsigned indice){
    vector<Vertice*> v;

    for(unsigned i = 0; i < indice; i++){
        v.push_back(vertices[i]);
    }

    for(unsigned i = indice+1; i < vertices.size(); i++){
        v.push_back(vertices[i]);
    }

    return v;
}

vector<Vertice*> perturbacao(vector<Vertice*> vertices, int perturbation_size){

    float v = vertices.size();
    float p = perturbation_size;

    int nRemove = ceil(v/p);

    for(int i=0; i < nRemove; i++){
        unsigned indice = rand() % vertices.size();
        vertices = removeVertice(vertices, indice);
    }

    return vertices;
}

bool foiVisitado(vector<Vertice*> visitados, Vertice* vertice){


    for(unsigned i=0; i < visitados.size(); i++){
        if(visitados[i] == vertice){
            return true;
        }
    }
    return false;
}

vector<Vertice*> coletaVizinhos(vector<Vertice*> vizinhos, vector<Vertice*> vertices, vector<Aresta*> arestas, vector<Vertice*> *visitados){

    vector<Vertice*> novosVizinhos = vizinhos;

    for(unsigned i = 0; i < arestas.size(); i++){
        if(vizinhos[0] == arestas[i]->getDestino() && !foiVisitado(*visitados, arestas[i]->getOrigem())){
            if(EstaNaSolucao(vertices,arestas[i]->getOrigem())){
                (*visitados).push_back(arestas[i]->getOrigem());
                novosVizinhos.push_back(arestas[i]->getOrigem());
            }
        }else
            if(vizinhos[0] == arestas[i]->getOrigem() && !foiVisitado(*visitados, arestas[i]->getDestino())){
               if(EstaNaSolucao(vertices,arestas[i]->getDestino())){
                (*visitados).push_back(arestas[i]->getDestino());
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
    visitados.push_back(vertices[0]);

    while(vizinhos.size()>0){
            vizinhos = coletaVizinhos(vizinhos, vertices, arestas,& visitados);
            vizinhos.erase(vizinhos.begin());
    }

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

    if(pesos > limite){
        cout << "ERROR" <<endl;
        return false;
    }

    if(!conexo(vertices, arestas))
        return false;

    return true;
}

void lerArquivo(vector<Vertice*> *vertices, vector<Aresta*> *arestas, float *limite,string filename){

    vertices->clear();
    arestas->clear();

    //Leitura de arquivo.
    string line, delimiter = " ";
    ifstream myfile(filename);
    int nVertices, mArestas;
    if (myfile.is_open()){
        while (!myfile.eof()){
            getline(myfile,line);
            nVertices = stoi(line.substr(0,line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());
            mArestas = stoi(line.substr(0,line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());
            *limite = stof(line.substr(0,line.find(delimiter)));

            getline(myfile,line);

            for(int i = 0; i < nVertices; i++){
                vertices->push_back(new Vertice(i,stof(line.substr(0,line.find(delimiter)))));
                line.erase(0, line.find(delimiter) + delimiter.length());
            }
            getline(myfile,line);
            for(int i = 0; i < nVertices; i++){
                (*vertices)[i]->setValor(stof(line.substr(0,line.find(delimiter))));
                line.erase(0, line.find(delimiter) + delimiter.length());
            }

            for(int i = 0; i < mArestas; i++){
                getline(myfile,line);
                unsigned origem = stoi(line.substr(0,line.find(delimiter)));
                line.erase(0, line.find(delimiter) + delimiter.length());
                arestas->push_back(new Aresta((*vertices)[origem], (*vertices)[stoi(line.substr(0,line.find(delimiter)))]));
            }

            while(!myfile.eof()){
                getline(myfile,line);
            }
        }
        myfile.close();
    }else
        cout << "Unable to open file" << endl;
}

void escreverArquivo(vector<Vertice*> vertices,string fileOut, float tempo){

	ofstream myfile(fileOut);
	myfile << "N de Vertices: " << vertices.size()<<endl;
	myfile << "Valor Total: " << calculaValor(vertices) << endl;
	myfile << "Peso Total: " << calculaPeso(vertices) << endl;
	myfile << "Tempo de Duracao: " << tempo << " s" <<endl;
	myfile << endl;
	myfile << "Vertice:		Valor:		Peso:"<< endl;
	for(unsigned i = 0; i < vertices.size(); i++){
		myfile << vertices[i]->getId() << "				" << vertices[i]->getValor() << "			" << vertices[i]->getPeso() << endl;
	}

	myfile.close();

}

int main(int argc, char *argv[]){
    int criterio = 0;
    float limite = 0;

    if(argc!=7){
        cout << "Error: number of parameters incorrect." <<endl;
        cout << "Parameters: stdout stdin max_time min_time max_not_improved perturbation_size" <<endl;
        return 0;
    }

    float max_time = atof(argv[3]);
    float min_time = atof(argv[4]);
    int max_not_improved = atoi(argv[5]);
    int perturbation_size = atoi(argv[6]);

    vector<Aresta*> arestas;
    vector<Vertice*> vertices;
    vector<Vertice*> solucao;
    vector<Vertice*> melhorSolucao;

    srand(time(0));

    lerArquivo(&vertices, &arestas, &limite, argv[2]);

    clock_t tInicio = clock();

    solucao = geraSolucaoInicial(vertices, limite);

    solucao = buscaLocal(solucao, arestas, limite);

    melhorSolucao = solucao;

    while((criterio < max_not_improved && ((float)(clock()-tInicio))/CLOCKS_PER_SEC < max_time) || ((float)(clock()-tInicio))/CLOCKS_PER_SEC < min_time){ //
        cout<< "Criterio: " << criterio << " Tempo: " << ((float)(clock()-tInicio))/CLOCKS_PER_SEC <<endl;
        vector<Vertice*> novaSolucao = perturbacao(solucao, perturbation_size);

        novaSolucao = buscaLocal(novaSolucao, arestas, limite);

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

    imprimeSolucaoFinal(melhorSolucao);

	escreverArquivo(melhorSolucao, argv[1], ((float)(clock()-tInicio))/CLOCKS_PER_SEC);

    return 0;
}

