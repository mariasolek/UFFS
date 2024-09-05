#include <stdio.h>

void copia(int *A, int *v, int size) {
  for (int i = 0; i < size; i++) {
    v[i] = A[i];
  }
}
int particiona(int *A, int inicio, int fim) {
  int troca;
  int posPivo = fim;
  int k = inicio;
  for (int i = inicio; i < fim; i++) {
    if (A[i] <= A[posPivo]) {
      troca = A[i];
      A[i] = A[k];
      A[k] = troca;
      k++;
    }
  }
  if (A[k] > A[posPivo]) {
    troca = A[k];
    A[k] = A[posPivo];
    A[posPivo] = troca;
  }
  return posPivo;
}

void quickS(int *A, int inicio, int fim) {
  if (inicio < fim) {
    int posPivo = particiona(A, inicio, fim);
    quickS(A, inicio, posPivo-1);
    quickS(A, posPivo + 1, fim);
  }
}

void quickSort(int *A, int size) {
    quickS(A, 0, size-1);
}

int main(){

    int i;
    int vetor[] = {1, 20, -10, 30, 5, 7}; //vetor teste
    int tamanhoVetor = (int)sizeof(vetor)/sizeof(int);

    printf("\nVetor original: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);

    printf("\nVetor tamanho = %d\n", tamanhoVetor);

    quickSort(vetor, tamanhoVetor);
    printf("\nVetor ordenado: ");
    for (i = 0 ; i < tamanhoVetor ; i++)
        printf("%d ", vetor[i]);
    printf("\n");
    
    return 0;
}