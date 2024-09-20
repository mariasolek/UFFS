//Autores: A. Cardoso Siqueira e Maria Clara Solek 

#include <iostream> 
#include "Grafo.h"
using namespace std;

Grafo::Grafo(int num_vertices) {
    if (num_vertices <= 0) {
        throw(invalid_argument("Erro no construtor Grafo(int): o numero de vertices é invalido!"));
    }

    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices);
}

    int Grafo::num_vertices() { 
        return num_vertices_;
    }
    int Grafo::num_arestas() {
        cout << num_arestas_ << "\n";
        return num_arestas_;
    }

    bool Grafo::tem_aresta(Aresta e) {
        for (auto i : lista_adj_[e.v1]){ 
            if (i == e.v2){ 
                return true;
            }
        }
        return false;
    }

    void Grafo::insere_aresta(Aresta e) {
        if (tem_aresta(e) || e.v1 == e.v2){
            return;
        }
        lista_adj_[e.v1].push_front(e.v2);
        lista_adj_[e.v2].push_front(e.v1);
        num_arestas_ ++;
    }

    void Grafo::remove_aresta(Aresta e) {
        if (!tem_aresta(e)) {
            return;
        }
        lista_adj_[e.v1].remove(e.v2);
        lista_adj_[e.v2].remove(e.v1);
        num_arestas_ --;
    }

    void Grafo::imprime_complemento() {
        for (int i = 0; i < num_vertices_ ; i++) {
            cout << i << ": ";
            for (int j = 0; j < num_vertices_; j++){
                if (i != j && !tem_aresta(Aresta(i, j))){ 
                    cout << " " << j;
                }
            }
            cout << "\n";
        }
    }
   
    void Grafo::num_arestas_subgrafo_induzido(int n, std::vector<int>& s) {
        int arestas = 0;
        for (int i = 0; i < n; i++) { 
            if (s[i] < 0 || s[i] >= num_vertices_){ 
                return;
            }
            for (int j = i + 1; j < n; j++){ 
                if (tem_aresta(Aresta(s[i], s[j]))){ 
                    arestas++;
                }
            }
        }  
        cout << arestas << "\n";  
    }