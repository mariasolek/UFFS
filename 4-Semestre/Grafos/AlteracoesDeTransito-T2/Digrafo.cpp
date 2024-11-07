/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Maria Clara Solek da Costa Vaz e Ângela Cardoso Siqueira
 * Matricula: 2311100059, 2311100029
 */

#include <iostream> 
#include "Digrafo.h"
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
            if (i.first == e.v2){ 
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

    void Digrafo::busca_prof(int v) {
        stack<int> pilha;
        pilha.push(v);
        while (!pilha.empty()) {
            int w = pilha.top();
            pilha.pop();
            if (marcado[w] == 0) {
                printf("%d\n", w);
                marcado[w] = 1;
                for (int u = (num_vertices_ - 1); u >= 0; u--)
                    if (matriz_adj_[w][u] != 0)
                        if (marcado[u] == 0)
                            pilha.push(u);
        }
    }
 }

    bool Digrafo::caminho(int v, int w, int marcado[]) {
        if (v == w) {
            printf("%d-", v);
            return true;
        }
        marcado[v] = 1;
        for (int u = 0; u < num_vertices_; u++)
            if (matriz_adj_[v][u] != 0)
                if (marcado[u] == 0)
                    if (caminho(u, w, marcado)) {
                        printf("%d-", v);
                        return true;
                    }
        return false;
 }

    Digrafo Digrafo::grafo_transposto(){
        //usar como base trabalho 1 função complemento
    }

 //achar componente conexa
    vector<vector<int>> Digrafo::fortemente_conexa(int n, vector<vector<int>>& vetor) {
        //1. busca em profundidade pra preencher a pilha (entra na pilha quando todos os vertices filhos do vertice atual já estão marcados)
        //2. inverter a orientação das arestas
        //3. desmarcar vertices
        //3. busca em profundidade na ordem da pilha
        //4. se depois de inverter a orientação tenho um ciclo então é fortemente conexo
        // se vou pro próximo da pilha e o único caminho possível já está marcado então é o vertice é uma componente fortemente conexa
        // se vou pro próximo da pilha e ele já está marcado então ele já faz parte de uma componente e posso exclui-lo da pilha
    }