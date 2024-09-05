#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* Item;

typedef struct elemStack {
    Item item;
    struct elemStack *next;
} ElemStack;

typedef struct {		
    ElemStack *top;	
} Stack;	

Stack *stack;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmptyStack(Stack *s) {
    if (s->top == NULL) return 1;
    else return 0;
}

void push(Stack *s,char item[]) {
    ElemStack *aux;
    aux = (ElemStack *)malloc(sizeof(ElemStack));
    aux->item = strdup(item);
    aux->next = s->top;
    s->top = aux;
}

void pop(Stack *s) {
    ElemStack *aux;

    if (isEmptyStack(s)==1)
        printf("Vazio\n");
    else {
        printf("%s", s->top->item); 
        aux = s->top;
        s->top = aux->next;
        free(aux);
}
}

void freeStack(Stack *s) {
    ElemStack *aux;

    while (!isEmptyStack(s)) {
 
        aux = s->top;
        s->top = s->top->next;
        free(aux);
    }
} 

int main() {
Stack stack;
char input[60];

initStack(&stack);
fgets(input, 60, stdin);
fflush(stdin);

while (strcmp(input,"E\n")!=0){

    if (strcmp(input,"B\n")!=0){
        push(&stack, input);
    }
    else {
        pop(&stack);
    }

    fgets(input, 60, stdin);
    fflush(stdin);
}

if (isEmptyStack(&stack)==1)
    printf("!\n");
else{
    while (!isEmptyStack(&stack)){
    freeStack(&stack);
    printf("@");
    printf("\n");
    }
}



return 0;
}