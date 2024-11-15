/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Maria Clara Solek da Costa Vaz e Ângela Cardoso Siqueira
 */

#include <bits/stdc++.h> 
#include "Digrafo.h"
#include "Aresta.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
     try {
        int P; //número de vértices
        int D; //número de operações
        cin >> P;
        cin >> D;

        Digrafo G(P);

        int i = 0;
        while(i < D){
            int X, Y, S;
            cin >> X >> Y >> S;

            switch (S){
                case 1: {
                        G.insere_aresta(Aresta(X, Y));
                        i++;
                        break;
                }
                case 2: {
                        G.insere_aresta(Aresta(X, Y));
                        G.insere_aresta(Aresta(Y, X));
                        i++;
                        break;
                }
                default:{
                        break;
                }
            }
        }
        
        G.fortemente_conexa();
     }
    catch(const exception &e) { //usando try catch pra nao "quebrar" o programa
        cerr << e.what() << "\n"; //impressão relacionada a erro
    }
   
    return 0;
}

