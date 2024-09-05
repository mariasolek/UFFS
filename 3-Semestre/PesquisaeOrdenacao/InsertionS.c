#include <stdio.h>

void insertionSort(int *A, int size){
int troca;
for(int i = 1; i < size; i++){
    for(int j = i; j > 0; j--){
        if(A[j] < A[j-1]){
            troca = A[j];
            A[j] = A[j-1];
            A[j-1] = troca;
            }
        }
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

    insertionSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}