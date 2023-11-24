#ifndef STRUCTS_H
#define STRUCTS_H

#include "constants.h"

// Struct pessoa
typedef struct pessoa{
    char user[TAMANHO];
    int senha;
    char tipo[TAMANHO];
} Pessoa;

// Lista encadeada
typedef struct no {
    Pessoa pessoa;
    struct no *prox;
} Node;

typedef struct lista {
    Node *inicio;
    Node *fim;
    int tamanho;
} Lista;

#endif