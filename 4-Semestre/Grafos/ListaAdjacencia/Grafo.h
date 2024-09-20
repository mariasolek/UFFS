//Autores: A. Cardoso Siqueira e Maria Clara Solek 

#ifndef GRAFO_H
#define GRAFO_H
#include <bits/stdc++.h> //ou #include <vector> e <list>
#include "Aresta.h"

class Grafo {
public:
    Grafo(int num_vertices);
    int num_vertices();
    int num_arestas(); 
    bool tem_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void imprime_complemento();
    void num_arestas_subgrafo_induzido(int n, std::vector<int>& s);

private:
    int num_vertices_;
    int num_arestas_;
    //declarando vetor: std::vector<int> vet;
    std:: vector<std::list<int>> lista_adj_; 
};


#endif