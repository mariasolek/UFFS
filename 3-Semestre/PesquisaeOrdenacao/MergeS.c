#include <stdio.h>

void intercala(int *A, int inicio, int meio, int fim){ 
    int aux[fim - inicio + 1];
    int i = inicio;
    int j = meio + 1;
    int k = 0;
    while (i <= meio && j <= fim)
    {
        if (A[i] <= A[j]){
            aux[k] = A[i];
            i++;
        }
        else{
            aux[k] = A[j];
            j++;
        }
        k++;
    }
    while (i <= meio)
    {
        aux[k] = A[i];
        k++;
        i++;
    }
    while (j <= fim)
    {
        aux[k] = A[j];
        j++;
        k++;
    }
    for (k = inicio; k < fim; k++){
       A[k] = aux[k - inicio];
    }
}

void mergeS(int *A, int inicio, int fim){
    if (inicio < fim){
        int meio = (inicio + fim)/2;
        mergeS(A, inicio, meio);
        mergeS(A, meio+1, fim);
        intercala(A, inicio, meio, fim);
    }
}

void mergeSort(int *A, int size){
    mergeS(A, 0, size);
}

int main(){

    int i;
    int vetor[] = {1, 20, -10, 30, 5, 7}; //vetor  exemplo
    int tamanhoVetor = (int)sizeof(vetor)/sizeof(int);

    printf("\nVetor original: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);

    printf("\nVetor tamanho = %d\n", tamanhoVetor);

    mergeSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++) 
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}