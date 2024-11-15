/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Maria Clara Solek da Costa Vaz e Ângela Cardoso Siqueira
 */

#include <iostream> 
#include "Digrafo.h"
#include <vector>
#include <stack>
using namespace std;

Digrafo::Digrafo(int num_vertices) {
    if (num_vertices <= 0) {
        throw(invalid_argument("Erro no construtor Digrafo(int): o numero de vertices é invalido!"));
    }

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices);
}

    int Digrafo::num_vertices() { 
        return num_vertices_;
    }
    int Digrafo::num_arestas() {
        return num_arestas_;
    }

    bool Digrafo::tem_aresta(Aresta e) {
        for (auto i : lista_adj_[e.v1]){ 
            if (i == e.v2){ 
                return true;
            }
        }
        return false;
    }

    void Digrafo::insere_aresta(Aresta e) {
        if (tem_aresta(e) || e.v1 == e.v2){
            return;
        }
        lista_adj_[e.v1].push_front(e.v2);
        num_arestas_ ++;
    }


    void Digrafo::remove_aresta(Aresta e) {
        if (!tem_aresta(e)) {
            return;
        }
        lista_adj_[e.v1].remove(e.v2);
        num_arestas_ --;
  }

    void Digrafo::busca_prof_preenche(int v, int marcado[], std::stack<int>& pilha) { //preenche a pilha
        marcado[v] = 1;

        for (auto i : lista_adj_[v]) {
            if (marcado[i] == 0){
                busca_prof_preenche(i, marcado, pilha); 
            }
        }
        pilha.push(v);
    }

   void Digrafo::busca_prof(int v, int marcado[], std::vector<int>& componente) {
        std::stack<int> pilha;
        pilha.push(v);

        while (!pilha.empty()) {
            int w = pilha.top();
            pilha.pop();

            if (marcado[w] == 0) { //se ainda não foi visitado
                marcado[w] = 1;
                componente.push_back(w); //adiciona no componente em que estamos

                for (int u = num_vertices_ - 1; u >= 0; u--) { //faz andar
                    if (tem_aresta(Aresta(w, u)) && marcado[u] == 0) {
                        pilha.push(u);
                    }
                }
            }
        }
    }

    Digrafo Digrafo::grafo_transposto(){  
        Digrafo transposto(num_vertices_); //cria um grafo novo

         for(int i = 0; i < num_vertices_ ; i++){
            for (int j = 0; j < num_vertices_ ; j++){
                if (tem_aresta(Aresta(i, j))){ //onde tem aresta insere ao contrário no transposto
                    transposto.insere_aresta(Aresta(j,i));
                }
            }
         }
         return transposto;
    }
    
    void Digrafo::fortemente_conexa() {
        std::stack<int> pilha;
        std::vector<int> marcado(num_vertices_);

        for (int i = 0; i < num_vertices_; i++) { //preenche a pilha
            if (marcado[i] == 0) {
                busca_prof_preenche(i, marcado.data(), pilha);
            }
        }

        for (int i = 0; i < num_vertices_; i++){ //zera marcado
            marcado[i] = 0;
        } 

        Digrafo transposto = grafo_transposto(); //cria grafo transposto

        
        std::vector<std::vector<int>> componentes; //vai armazenar os componentes
        while (!pilha.empty()) { 
            int v = pilha.top();
            pilha.pop();

            if (marcado[v] == 0) { //se ainda não foi visitado
                std::vector<int> componente;
                transposto.busca_prof(v, marcado.data(), componente);  //busca por profundidade no grafo transposto
                componentes.push_back(componente);
            }
        }

        std::vector<int> indice_componentes(num_vertices_, -1); //armazena em que componente está cada vértice
        for (int i = 0; i < int(componentes.size()); i++) {
            for (auto v : componentes[i]) {
                indice_componentes[v] = i;
            }
        }
        
        std::vector<std::vector<int>> adjacencias(componentes.size()); //para contar as adjacencias dos componentes

        for (int v = 0; v < num_vertices_; v++) {
            int ci = indice_componentes[v];  //componente do vértice v
            for (int w : lista_adj_[v]) {   //para cada vértice adjacente w
                int cj = indice_componentes[w];  //componente do vértice w
                if (ci != cj) {  
                    bool existe = false; //flag para verificar se já existe
                    for (auto adj : adjacencias[ci]) {
                        if (adj == cj) {
                            existe = true;
                            break;
                        }
                    }
                    if (!existe) { //se não existe, insere cj
                        adjacencias[ci].push_back(cj);
                    }
                }
            }
        }

        // Imprimir resultado
        for (int i = 0; i < int(adjacencias.size()); i++) {
            cout << i << ": " << adjacencias[i].size() << "\n";
        }
    }
 
   
