//Autores: A. Cardoso Siqueira e Maria Clara Solek 

#include <bits/stdc++.h> 
#include "Grafo.h"
#include "Aresta.h"
#include <iostream>
using namespace std;

int main() {
    try {
        int V; //número de vértices
        int O; //número de operações
        cin >> V;
        cin >> O;

        Grafo G(V);

        int i = 0;
        while(i < O){
                char caractere;
                cin >> caractere;
                switch (caractere)
                {
                case 'I': {
                        int X, Y;
                        cin >> X >> Y;
                        G.insere_aresta(Aresta(X, Y));
                        i++;
                        break;
                }
                case 'R': {
                        int X, Y;
                        cin >> X >> Y;
                        G.remove_aresta(Aresta(X, Y));
                        i++;
                        break;
                }
                case 'E': {
                        G.num_arestas();
                        i++;
                        break;
                }
                case 'S': {
                        int N;
                        cin >> N;
                        std::vector<int> S(N);
                        for(int i=0; i < N; i++){
                                cin >> S[i];
                        }
                        G.num_arestas_subgrafo_induzido(N, S);
                        i++;   
                        break;  
                }
                case 'X': {
                        G.imprime_complemento();
                        i++;  
                        break;
                }
                default:{
                        break;
                }
                }
        }
    }
    catch(const exception &e) { //usando try catch pra nao "quebrar" o programa
        cerr << e.what() << "\n"; //impressão relacionada a erro
    }
    return 0;
}
