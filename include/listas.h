#ifndef LISTAS_H
#define LISTAS_H

#include "structs.h"

Lista *criarLista();
void inserir(Lista *l, char *nome, int senha, char *tipo);
void remover(Lista *l, char *nome, int senha);
void atualizarLista(Lista *l, char *nome, char *novoNome, int s, int novaSenha);
void imprimir(Lista *l);

#endif