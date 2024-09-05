/**
 * @file ArvoreHuffman.c
 * @author A. Cardoso Siqueira
 * @author Maria Clara Solek
 * @version 7.0
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char valor;
  int frequencia;
  char *codigo;
  struct node *left;
  struct node *right;
  struct node *root;
  struct node *next;
};
typedef struct node Node;

struct lista {
  Node *first;
  int tamanho;
};
typedef struct lista Lista;

// Tabela de frequência
void initTabela(int tab[]) {
  for (int i = 0; i < 256; i++) {
    tab[i] = 0;
  }
}

void setTabela(char texto[], int tab[]) {
  int i = 0;
  while (texto[i] != '\0') {
    tab[(int)texto[i]]++; //tabela no indice do mumero que representa o caractere na tabela ascii
    i++;
  }
}

// lista
Node *criaNo(char valor, int frequencia, const char *codigo) {
  Node *novoNo = (Node *)malloc(sizeof(Node));
  novoNo->valor = valor;
  novoNo->frequencia = frequencia;
  novoNo->left = NULL;
  novoNo->right = NULL;
  novoNo->root = NULL;
  novoNo->next = NULL;
  novoNo->codigo = strdup(codigo);
  return novoNo;
}

Lista *copia(int tab[]) { //copia da tabela para uma lista de tamanho dinamico
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->first = NULL;
  lista->tamanho = 0;

  Node *aux = NULL;
  for (int i = 0; i < 256; i++) { //percorre tabela
    if (tab[i] > 0) { //onde tiver algo
      Node *novoNo = criaNo((char)i, tab[i], "");
      if (lista->first == NULL) {  //copia p/ lista
        lista->first = novoNo;
        aux = lista->first;
      } else {
        aux->next = novoNo;
        aux = aux->next;
      }
      lista->tamanho++;
    }
  }
  return lista;
}

// ordenação
void bubbleSort(Lista *lista) {
  int i = lista->tamanho;
  int flag;
  int swFrenquencia;
  char swValor;
  Node *aux;
  while (i > 1){
    flag = 0;
    aux = lista->first;
    for (int j = 0; j < i - 1; j++){
      if (aux->frequencia >aux->next->frequencia){
        swFrenquencia = aux->frequencia;
        swValor = aux->valor;

        aux->frequencia = aux->next->frequencia;
        aux->valor = aux->next->valor;

        aux->next->frequencia = swFrenquencia;
        aux->next->valor = swValor;
        flag = 1;
      }
      aux = aux->next;
    }
    if (flag == 0){
      break;
    }
    i--;
  }
}

//árvore
void juntaNos(Lista *lista) {
  Node *first = lista->first; // primeiro da lista
  Node *second = lista->first->next; // segundo da lista
  Node *root = criaNo('\0', first->frequencia + second->frequencia,""); // cria a raiz da arvore

  // coloca primeiro e segundo como filhos
  root->left = first;
  root->right = second;

  // atualiza lista
  lista->first = second->next;
  lista->tamanho -= 2;

  // coloca a arvore na posição correta para manter a lista ordenada
  if (lista->first == NULL ||root->frequencia <= lista->first->frequencia) { // adicionar na primeira posição
    root->next = lista->first;
    lista->first = root;
  } else {
    Node *aux = lista->first;
    while (aux->next != NULL && aux->next->frequencia < root->frequencia) {
      aux = aux->next;
    }
    root->next = aux->next;
    aux->next = root;
  }
  // aumenta o tamanho da lista pq adicionou novo nó
  lista->tamanho++;
}

void criaArvore(Lista *lista) {
  while (lista->tamanho > 1) {
    juntaNos(lista);
    bubbleSort(lista);
  }
}

int verificaFolha(Node *root) { return !(root->left) && !(root->right); }

// tabela de códigos
int descobreAltura(Node *root) {
  if (root == NULL) {
    return -1;
  } else {
    int left = descobreAltura(root->left) + 1;
    int right = descobreAltura(root->right) + 1;

    if (left > right) {
      return left;
    } else {
      return right;
    }
  }
}

void codifica(Node *root, char *codigo) {
  if (root != NULL) {
    if (verificaFolha(root)) { // se for folha ele armazena o código no atributo da struct
      root->codigo = strdup(codigo);
    }
    if (root->left != NULL) {
      strcat(codigo, "0");    // adiciona 0 ao codigo
      codifica(root->left, codigo); // percorre recursivamente
      codigo[strlen(codigo) - 1] = '\0'; // adiciona \0 pra dizer q a string acaba ali
    }
    if (root->right != NULL) {
      strcat(codigo, "1");     // adiciona 1 ao codigo
      codifica(root->right, codigo); // percorre recursivamente
      codigo[strlen(codigo) - 1] = '\0';
    }
  }
}

void preencheTabelaCodigos(Node *root, char **tabela) {
  if (root != NULL) {
    if (verificaFolha(root)) {
      tabela[(int)root->valor] = strdup(root->codigo); // se for folha adiciona o valor na tabela
    }
    preencheTabelaCodigos(root->left,tabela); // percore a arvore de forma recursiva
    preencheTabelaCodigos(root->right, tabela);
  }
}

char **criaTabelaCodigos(Node *raiz) {
  char **tabela = (char **)malloc(256 * sizeof(char *)); //cria a tabela
  for (int i = 0; i < 256; i++) {
    tabela[i] = NULL; //inicializa tudo em NULL
  }
  preencheTabelaCodigos(raiz, tabela); //preenche ela
  return tabela;
}

char *codificaPalavra(char **tabela, char *texto) {
  int i = 0;
  size_t codigo_len = 1; // começa em 1 pra colocar nulo no começo tbm
  for (int j = 0; texto[j] != '\0'; j++) {
    codigo_len += strlen(tabela[(int)texto[j]]);
  }

  char *codigo = malloc(codigo_len);
  if (codigo == NULL) {
    exit(1);
  }
  codigo[0] = '\0'; // coloca o caractere nulo ao fim da string

  while (texto[i] != '\0') {
    strcat(codigo, tabela[(int)texto[i]]);
    i++;
  }
  return codigo;
}

char *decodificaPalavra(Node *root, char *codificado) {
  Node *aux = root;
  int tamanho = strlen(codificado); //calcula tamanho do texto codificado
  char *decodificado = malloc(tamanho + 1); // aloca memória para decodificado 
  if (decodificado == NULL) {
    exit(1);
  }

  int iDecodificado = 0;
  for (int i = 0; i < tamanho; i++) { //percorre codificado e segue o caminho até as folhas
    if (codificado[i] == '0') {
      aux = aux->left;
    } else if (codificado[i] == '1') {
      aux = aux->right;
    }
    if (verificaFolha(aux)) { //ao encontrar a folha, adicionamos o seu caractere no texto decodificado
      decodificado[iDecodificado++] = aux->valor;
      aux = root; //aux volta para a raiz
    }
  }
  decodificado[iDecodificado] = '\0';
  return decodificado;
}

int main() {
  char texto[1024]; //texto em amostra.txt | alterar de acordo com o tamanho do texto q deseja codificar !
  int tabFrequencia[256]; // numero de caracteres na tabela ASCII extendida
  char codificado[1024] = ""; //texto que vai para codificado.txt
  char **tabelaCodigos;
  char *decodificado; //texto que vai para decodificado.txt
  int alturaArvore;
  char *codigo;

  initTabela(tabFrequencia);

  FILE *fp = fopen("/Users/solek/Documents/UFFS/github/UFFS/3-Semestre/PesquisaeOrdenacao/ArvoreHuffmancArquivos/amostra.txt","rt"); // cria um ponteiro do tipo FILE para o arquivo do caso de teste e o abre em modo de leitura testa se abertura do arquivo funcionou e notifica caso não tenha uncionado.
  if (fp == NULL) {
     exit(1); // aborta o programa
  }

  while (fgets(texto, sizeof(texto), fp)) {
    //tabela Frequencia
    setTabela(texto, tabFrequencia);

    //tabela Ordenada
    Lista *lista = copia(tabFrequencia);
    bubbleSort(lista);

    //cria Arvore
    criaArvore(lista);

    //codificação das folhas
    alturaArvore = descobreAltura(lista->first) + 1;
    codigo = (char *)malloc(alturaArvore + 1);
    if (codigo == NULL) {
      exit(1);
    }
    codigo[0] = '\0'; //código está inicializando com NULL
    codifica(lista->first, codigo);

    //Tabela Codigos
    tabelaCodigos = criaTabelaCodigos(lista->first);
    strcpy(codificado, codificaPalavra(tabelaCodigos, texto));
    decodificado = decodificaPalavra(lista->first, codificado);

    free(codigo);
  }
  fclose(fp);

  FILE *fp1 = fopen("/Users/solek/Documents/UFFS/github/UFFS/3-Semestre/PesquisaeOrdenacao/ArvoreHuffmancArquivos/codificado","w+");
  if (fp1 == NULL) {
    exit(1);
  }
  fputs(codificado, fp1);
  fclose(fp1);

  FILE *fp2 = fopen("/Users/solek/Documents/UFFS/github/UFFS/3-Semestre/PesquisaeOrdenacao/ArvoreHuffmancArquivos/decodificado.txt","w+");
  if (fp2 == NULL) {
    exit(1); //aborta o programa
  }
  fputs(decodificado, fp2);
  fclose(fp2);

  return 0;
}
