#include <stdio.h>

void selectionSort(int *A, int size){
int troca, menor;
for (int i = 0; i < size-1; i++){
    menor = i;
    for (int j = i + 1; j < size; j++){
        if (A[menor] > A[j]){
            menor = j;
        }
    }
    troca = A[i];
    A[i] = A[menor];
    A[menor] = troca;
}
}

int main(){

    int i;
    int vetor[] = {1, 20, -10, 30, 5, 7}; //vetor teste
    int tamanhoVetor = (int)sizeof(vetor)/sizeof(int);

    printf("\nVetor original: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);

    printf("\nVetor tamanho = %d\n", tamanhoVetor);

    selectionSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}