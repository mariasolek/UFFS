/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Maria Clara Solek da Costa Vaz e Ângela Cardoso Siqueira
 */

#ifndef DIGRAFO_H
#define DIGRAFO_H
#include <bits/stdc++.h>
#include <stack>
#include <vector>
#include "Aresta.h"

class Digrafo {

public:
    Digrafo(int num_vertices);
    int num_vertices();
    int num_arestas(); 
    bool tem_aresta(Aresta e);
    void insere_aresta(Aresta e);
    void remove_aresta(Aresta e);
    void busca_prof_preenche(int v, int marcado[], std::stack<int>& pilha);
    void busca_prof(int v, int marcado[], std::vector<int>& componente);
    Digrafo grafo_transposto();
    void fortemente_conexa();

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<int>> lista_adj_; 
    
};

#endif 
