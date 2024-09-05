#include <stdio.h>

void countingSort(int *A, int size){
    int k = 0;
    for(int i = 0; i < size; i++){
        if(A[i] > k){
            k = A[i];
        }
    }

    int count[k+1];
    int aux[size];

    for(int i = 0; i <= k; i++){
        count[i] = 0;
    }
    for(int i = 0; i < size; i++){
        count[A[i]]++;
    }
    for(int i = 1; i <= k; i++){
        count[i] += count[i-1];
    }
    for(int i = size-1; i >= 0; i--){
        count[A[i]] = count[A[i]] - 1;
        aux[count[A[i]]] = A[i];
    }
    for(int i = 0; i < size; i++){
        A[i] = aux[i];
    }
}

int main(){

    int i;
    int vetor[] = {1, 20, 10, 30, 5, 7};//vetor  exemplo
    int tamanhoVetor = (int)sizeof(vetor)/sizeof(int);

    printf("\nVetor original: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);

    printf("\nVetor tamanho = %d\n", tamanhoVetor);

    countingSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++) 
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}
