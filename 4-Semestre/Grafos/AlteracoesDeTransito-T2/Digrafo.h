/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Maria Clara Solek da Costa Vaz e Ângela Cardoso Siqueira
 * Matricula: 2311100059, 2311100029
 */

#ifndef DIGRAFO_H
#define DIGRAFO_H
#include <bits/stdc++.h>
#include "Aresta.h"

class Digrafo {

public:
    Digrafo(int num_vertices);
    int num_vertices();
    int num_arestas(); 
    bool tem_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void Grafo::busca_prof(int v);

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<std::pair<int, int>>> lista_adj_;
};

#endif 
