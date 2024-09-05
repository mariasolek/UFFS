#include <stdio.h>

void bubbleSort(int *A, int size){
int flag;
int i = (size);
int troca;
    while (i > 1){
        flag = 0;
        for (int j = 0; j < i-1; j++){
            if (A[j] > A[j+1]){
                troca = A[j];
                A[j] = A[j+1];
                A[j+1] = troca;
                flag = 1;
            }
        }
        if (flag == 0){
            break;
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

    bubbleSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}