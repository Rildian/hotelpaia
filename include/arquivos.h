#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "listas.h"

bool cadastrar(Lista *l, char *nome, char *tipo, int senha);                        // C
void lerArquivos(Lista *l);                                                         // R
bool atualizar(Lista *l, char *nome, char *novoNome, int s, int novaSenha);         // U
bool deletar(char *nome, int s);                                                    // D


#endif