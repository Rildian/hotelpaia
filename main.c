#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#define TAMANHO 50

// Struct pessoa
typedef struct pessoa{
    char user[TAMANHO];
    int senha;
    char tipo[TAMANHO];
} PESSOA;

// Lista encadeada
typedef struct no {
    PESSOA pessoa;
    struct no *prox;
} NO;

// Ponteiro para inicio e fim da lista
NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;

bool cadastro();

// CRUD
bool cadastrar(char *nome, char *tipo, int senha);                      // C
void lerArquivos();                                                     // R
bool atualizar(char *nome, char *novoNome, int s, int novaSenha);       // U
bool deletar(char *nome, int s);                                        // D

// Lista encadeada
void inserir(char *nome, int senha, char *tipo);
void remover(char *nome, int senha);
void atualizarLista(char *nome, char *novoNome, int s, int novaSenha);
void imprimir();

int main()
{
    lerArquivos();
    cadastro();
    imprimir();
}

void lerArquivos()
{
    // Iniciar arquivos necessarios
    // Usuarios
    FILE *arq = fopen("usuarios.txt", "r");
    if (arq == NULL) {
        arq = fopen("usuarios.txt", "w");
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
        if (fgets(buffer, sizeof(buffer), arq) == NULL) {
            fclose(arq);
            return;  // se eh nulo tem nada ou deu erro 
        }

        while (fgets(buffer, sizeof(buffer), arq) != NULL) {
            char usuario[50];
            char senha[50];
            char tipo[50];

            // Extrair data
            sscanf(buffer, "%49[^,],%49[^,],%49[^,]", usuario, senha, tipo);
            // Inserir
            inserir(usuario, atoi(senha), tipo);
        }
        fclose(arq);
    }
}

void inserir(char* nome, int senha, char *tipo)
{
    NO *novo = malloc(sizeof(NO));
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
    if (inicio == NULL)
    {
        inicio = novo;
        fim = novo;
    }
    // Add fim
    else
    {    
        fim->prox = novo;
        fim = novo;
    }

    tam++;
}

void imprimir() {
    int largura = TAMANHO - 20;
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("| %-*s |  %s      |\n", largura, "Usuarios", "Tipo");
    printf("|--------------------------------|------------|\n");

    
    NO *aux = inicio;
    
    while(aux != NULL) 
    {
        printf("| %-*s | %-*s |\n", largura, aux->pessoa.user, 10, aux->pessoa.tipo);
        aux = aux->prox;
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

bool cadastro()
{
    int opcao;
    printf("Digite 0 se deseja se cadastrar como hospede ou digite 1 para se cadastrar como anfitriao: \nDigita outro numero para parar :)\nOpcao: ");
    scanf(" %d",&opcao);
    
    if (opcao < 0 || opcao > 1)
        return false;

    PESSOA pessoa;
    printf("Usuário: ");
    scanf("%s", &pessoa.user);
    printf("Senha: ");
    scanf("%d",&pessoa.senha);
    printf("\n");


    switch (opcao) {
        case 0:
            cadastrar(pessoa.user, "Hospede", pessoa.senha);
            break;
        case 1:
            cadastrar(pessoa.user, "Anfitriao", pessoa.senha);
            break;
    }
    return false;
    
}

bool cadastrar(char *nome, char *tipo, int senha)
{
    FILE *arq  = fopen("usuarios.txt", "a");

    if (arq == NULL)
    {
        fprintf(stderr, "Nao conseguiu abrir o arquivo :(.\n)");
        return false;
    }
    
    if (strcmp(tipo, "Hospede") == 0)
        fprintf(arq, "%s, %d, %s\n", nome, senha, tipo);
    else if (strcmp(tipo, "Anfitriao") == 0)
        fprintf(arq, "%s, %d, %s\n", nome, senha, tipo);

    inserir(nome, senha, tipo);
    fclose(arq);

    return true;
}

bool deletar(char *nome, int s)
{
    FILE *arq = fopen("usuarios.txt", "r");
    FILE *tmp = fopen("usuariotemp.txt", "w");

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
    
    // Temporario vira o novo usuarios.txt
    if (remove("usuarios.txt") != 0 || rename("usuariotemp.txt", "usuarios.txt") != 0) {
        fprintf(stderr, "Erro ao substituir o arquivo.\n");
        exit(1);
    }
}

void remover(char *nome, int senha)
{
    if (inicio == NULL)
    {
        printf("Vazia!\n");
        return;
    }

    NO *aux = inicio;

    // Inicio
    if (strcmp(aux->pessoa.user, nome) == 0 && aux->pessoa.senha == senha)
    {
        inicio->prox = aux->prox;
        free(aux);
        tam--;
        return;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->prox->pessoa.user, nome) == 0 && aux->prox->pessoa.senha == senha)
        {   
            NO *lixo = aux->prox;
            // Fim
            if (aux->prox == fim)
            {
                fim = aux;
                aux->prox = NULL;
            }
            // Meio
            else
            {
                aux->prox = lixo->prox;
            }

            free(lixo);
            tam--;
            return;
        }
        aux = aux->prox;
    }
    // Não achou
    printf("Nao foi encontrado.\n");
}

bool atualizar(char *nome, char *novoNome, int s, int novaSenha)
{
    FILE *arq = fopen("usuarios.txt", "r");
    FILE *tmp = fopen("usuariotemp.txt", "w");

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
    
    // Temporario vira o novo usuarios.txt
    if (remove("usuarios.txt") != 0 || rename("usuariotemp.txt", "usuarios.txt") != 0) {
        fprintf(stderr, "Erro ao substituir o arquivo.\n");
        exit(1);
    }
    atualizarLista(nome, novoNome, s, novaSenha);
}

void atualizarLista(char *nome, char *novoNome, int s, int novaSenha)
{
    if (inicio == NULL)
    {
        printf("Vazia!\n");
        return;
    }
    
    NO *aux = inicio;

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