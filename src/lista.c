#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/listas.h"
#include "../include/structs.h"
#include "../include/constants.h"

Lista *criarLista()
{
    Lista *lista = malloc(sizeof(Lista));
    if (lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        exit(1);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

    return lista;
}

void inserir(Lista *l, char* nome, int senha, char *tipo)
{
    Node *novo = malloc(sizeof(Node));
    if (novo == NULL)
    {
        printf("Deu erro :O !!\n");
        return;
    }
    
    // Remover o \n de arquivos csv
    size_t tamanho = strlen(tipo);
    if (tamanho > 0 && tipo[tamanho - 1] == '\n') {
        tipo[tamanho - 1] = '\0';
    }

    // Dados
    strncpy(novo->pessoa.user, nome, TAMANHO);
    strncpy(novo->pessoa.tipo, tipo, TAMANHO);
    novo->pessoa.senha = senha;

    novo->prox = NULL;
        
    // Se a lista estiver vazia
    if (l->inicio == NULL)
    {
        l->inicio = novo;
        l->fim = novo;
    }
    // Add fim
    else
    {    
        l->fim->prox = novo;
        l->fim = novo;
    }

    l->tamanho++;
}

void imprimir(Lista *l) {
    int largura = TAMANHO - 20;
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| %-*s |  %s      |\n", largura, "Usuarios", "Tipo");
    printf("|--------------------------------|------------|\n");

    
    Node *aux = l->inicio;
    
    while(aux != NULL) 
    {
        printf("| %-*s | %-*s |\n", largura, aux->pessoa.user, 10, aux->pessoa.tipo);
        aux = aux->prox;
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void remover(Lista *l, char *nome, int senha)
{
    if (l->inicio == NULL)
    {
        printf("Vazia!\n");
        return;
    }

    Node *aux = l->inicio;

    // Inicio
    if (strcmp(aux->pessoa.user, nome) == 0 && aux->pessoa.senha == senha)
    {
        l->inicio->prox = aux->prox;
        free(aux);
        l->tamanho--;
        return;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->prox->pessoa.user, nome) == 0 && aux->prox->pessoa.senha == senha)
        {   
            Node *lixo = aux->prox;
            // Fim
            if (aux->prox == l->fim)
            {
                l->fim = aux;
                aux->prox = NULL;
            }
            // Meio
            else
            {
                aux->prox = lixo->prox;
            }

            free(lixo);
            l->tamanho--;
            return;
        }
        aux = aux->prox;
    }
    // Não achou
    printf("Nao foi encontrado.\n");
}

void atualizarLista(Lista *l, char *nome, char *novoNome, int s, int novaSenha)
{
    if (l->inicio == NULL)
    {
        printf("Vazia!\n");
        return;
    }
    
    Node *aux = l->inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->pessoa.user, nome) == 0 && aux->pessoa.senha == s)
        {
            strncpy(aux->pessoa.user, novoNome, TAMANHO); 
            aux->pessoa.senha = novaSenha;
            return;
        }
        aux = aux->prox;
    }
    // Não achou
    printf("Nao foi encontrado.\n");
}