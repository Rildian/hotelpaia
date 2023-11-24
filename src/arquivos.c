#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/constants.h"
#include "../include/structs.h"
#include "../include/listas.h"

char *usuariosPath = "./data/usuarios.txt";
char *usuariosTempPath = "./data/tempusuarios.txt";

void lerArquivos(Lista *l)
{
    // Iniciar arquivos necessarios
    // Usuarios
    FILE *arq = fopen(usuariosPath, "r");
    if (arq == NULL) {
        arq = fopen(usuariosPath, "w");
        if (arq == NULL) {
            fprintf(stderr, "Erro ao criar o arquivo.\n");
            exit(1);
        }
        fprintf(arq, "Usuario, Senha, Tipo\n");
        fclose(arq);
    } 
    else {
        // Se o arquivo existe, iremos ler para formar uma lista encadeada
        char buffer[1024];
        
        // Descartar primeira linha
        // Se eh nulo tem nada ou deu erro 
        if (fgets(buffer, sizeof(buffer), arq) == NULL) {
            fclose(arq);
            return;  
        }

        while (fgets(buffer, sizeof(buffer), arq) != NULL) {
            char usuario[50];
            char senha[50];
            char tipo[50];

            // Extrair data
            sscanf(buffer, "%49[^,],%49[^,],%49[^,]", usuario, senha, tipo);
            // Inserir
            inserir(l, usuario, atoi(senha), tipo);
        }
        fclose(arq);
    }
}


bool cadastrar(Lista *l, char *nome, char *tipo, int senha)
{
    FILE *arq  = fopen(usuariosPath, "a");

    if (arq == NULL)
    {
        fprintf(stderr, "Nao conseguiu abrir o arquivo :(.\n)");
        return false;
    }
    
    if (strcmp(tipo, "Hospede") == 0)
        fprintf(arq, "%s, %d, %s\n", nome, senha, tipo);
    else if (strcmp(tipo, "Anfitriao") == 0)
        fprintf(arq, "%s, %d, %s\n", nome, senha, tipo);

    inserir(l, nome, senha, tipo);
    fclose(arq);

    return true;
}

bool deletar(char *nome, int s)
{
    FILE *arq = fopen(usuariosPath, "r");
    FILE *tmp = fopen(usuariosTempPath, "w");

    if (arq == NULL || tmp == NULL)
    {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        exit(1);
    }

    bool usuarioEncontrado = false;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        char usuario[50];
        char senha[50];
        char tipo[50];

        // Extrair data
        sscanf(buffer, "%49[^,],%49[^,],%49[^,]", usuario, senha, tipo);
        if (strcmp(usuario, nome) == 0 && s == atoi(senha))
        {
            usuarioEncontrado = true;
            continue;
        }

        fprintf(tmp, "%s,%s,%s", usuario, senha, tipo);

    }

    fclose(arq);
    fclose(tmp);
    
    // Temporario vira o novo /data/usuarios.txt
    if (remove(usuariosPath) != 0 || rename(usuariosTempPath, usuariosPath) != 0) {
        fprintf(stderr, "Erro ao substituir o arquivo.\n");
        exit(1);
    }
}

bool atualizar(Lista *l, char *nome, char *novoNome, int s, int novaSenha)
{
    FILE *arq = fopen(usuariosPath, "r");
    FILE *tmp = fopen(usuariosTempPath, "w");

    if (arq == NULL || tmp == NULL)
    {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        exit(1);
    }

    bool usuarioEncontrado = false;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        char usuario[50];
        char senha[50];
        char tipo[50];

        // Extrair data
        sscanf(buffer, "%49[^,],%49[^,],%49[^,]", usuario, senha, tipo);
        if (strcmp(usuario, nome) == 0 && s == atoi(senha))
        {
            fprintf(tmp, "%s, %d,%s", novoNome, novaSenha, tipo);
            usuarioEncontrado = true;
            continue;
        }
        else
            fprintf(tmp, "%s,%s,%s", usuario, senha, tipo);

    }

    fclose(arq);
    fclose(tmp);
    
    // Temporario vira o novo /data/usuarios.txt
    if (remove(usuariosPath) != 0 || rename(usuariosTempPath, usuariosPath) != 0) {
        fprintf(stderr, "Erro ao substituir o arquivo.\n");
        exit(1);
    }
    atualizarLista(l, nome, novoNome, s, novaSenha);
}