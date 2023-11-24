#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/constants.h"
#include "../include/structs.h"
#include "../include/listas.h"
#include "../include/arquivos.h"

bool cadastro(Lista *l);

int main(int argc, char **argv)
{
    Lista *lista = criarLista();
    lerArquivos(lista);
    cadastro(lista);
    imprimir(lista);
}

bool cadastro(Lista *l)
{
    int opcao;
    printf("Digite 0 se deseja se cadastrar como hospede ou digite 1 para se cadastrar como anfitriao: \nDigita outro numero para parar :)\nOpcao: ");
    scanf(" %d", &opcao);

    if (opcao < 0 || opcao > 1)
        return false;

    Pessoa pessoa;
    printf("Usuário: ");
    scanf("%s", &pessoa.user);
    printf("Senha: ");
    scanf("%d", &pessoa.senha);
    printf("\n");

    switch (opcao)
    {
    case 0:
        cadastrar(l, pessoa.user, "Hospede", pessoa.senha);
        break;
    case 1:
        cadastrar(l, pessoa.user, "Anfitriao", pessoa.senha);
        break;
    }
    return false;
}
