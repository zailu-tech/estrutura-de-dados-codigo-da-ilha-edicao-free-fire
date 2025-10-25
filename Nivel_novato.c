#include <stdio.h>  // Entrada e saída padrão
#include <stdlib.h>  //Alocação de memória
#include <string.h> // Biblioteca para manipulação de strings
#include <ctype.h> // Biblioteca para isdigit()

#define MAX_STR_LEN 50 // tamanho máximo de cada string/texto
#define TAM_MAX 10 // Tamanho máximo da lista estática

// Estrutura que representa um item na mochila
typedef struct{
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
} Item;

// Estrutura que representa a mochila
typedef struct{
    Item itens[TAM_MAX];
    int qntd;
} Mochila;

// Protótipos das funções
void inicializarMochila(Mochila *mochila); // Inicializa a mochila
void inserirItem(Mochila *mochila, const char* nome, const char* tipo, int quantidade); // Insere um item na mochila
void removerItem(Mochila *mochila, const char* nome); // Remove um item da mochila
void listarItem(const Mochila *mochila); // Lista os itens da mochila

// Função principal

int main(){
    // Declara a mochila
    Mochila mochila;
    inicializarMochila(&mochila);

    // Variáveis para o menu
    int opcao;
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;

    do
    {
        // Menu interativo
        printf("\n============================================\n");
        printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA \n");
        printf("===============================================\n");
        printf("Itens na Mochila: %d/10\n", mochila.qntd);
        printf("\n1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar itens na mochila\n");
        printf("0. Sair\n");

    // Lê a opção do usuário como string para evitar problemas com entradas inválidas
    char entrada[10];
    printf("Escolha uma opcao: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0;

    // Verifica se a entrada é um número válido
    int valido = 1;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            valido = 0;
            break;
        }
    }

    // Verifica se a entrada é um número válido
    if (!valido || strlen(entrada) == 0) {
        printf("\nOpcao invalida! Digite apenas numeros.\n");
        continue;
    }

    // Converte a entrada para inteiro
    opcao = atoi(entrada);

        switch(opcao){
            case 1: 
            printf("\n-- Adicionar Novo Item --\n");
            printf("\nNome do Item: ");
            fgets(nome, MAX_STR_LEN, stdin);
            nome[strcspn(nome, "\n")] = 0; // Remove o newline

            printf("Tipo do Item (arma, municao, cura, comida, etc): ");
            fgets(tipo, MAX_STR_LEN, stdin);
            tipo[strcspn(tipo, "\n")] = 0; // Remove o newline

            printf("Quantidade do Item: ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0;

            // Verifica se a entrada é um número válido
            valido = 1;
            for (int i = 0; entrada[i] != '\0'; i++) {
                if (!isdigit(entrada[i])) {
                    valido = 0;
                    break;
                }
            }
            if (!valido || strlen(entrada) == 0) {
                printf("\nQuantidade invalida! Digite apenas numeros.\n");
                continue;
            }
            quantidade = atoi(entrada);

            inserirItem(&mochila, nome, tipo, quantidade); // Insere o item na mochila
            listarItem(&mochila); // Mostra a mochila atualizada
            break;

            case 2:
            printf("-- Remover Item --\n");
            printf("\nNome do Item: ");
            fgets(nome, MAX_STR_LEN, stdin);
            nome[strcspn(nome, "\n")] = 0; // Remove a nova linha

            removerItem(&mochila, nome); // Remove o item da mochila
            listarItem(&mochila); // Mostra a mochila atualizada
            break;

            case 3:
            listarItem(&mochila); // Mostra a mochila atualizada
            break;

            printf("Pressione Enter para continuar...");
            getchar(); // Espera o usuário pressionar Enter

            case 0:
            printf("Saindo do programa...\n");
            break;
            default:
            printf("\nOpcao invalida! Tente novamente");
        }


    } while (opcao != 0);

}

// Implementação das funções

// Função para inicializar a mochila
void inicializarMochila(Mochila *mochila){
    mochila->qntd = 0; // Inicializa a quantidade de itens como 0
}

// Função para inserir um item na mochila
void inserirItem(Mochila *mochila, const char* nome, const char* tipo, int quantidade){

    // Verifica se a mochila está cheia
    if(mochila->qntd >= TAM_MAX){
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    // Adiciona o novo item na próxima posição disponível
    strncpy(mochila->itens[mochila->qntd].nome, nome, MAX_STR_LEN);
    strncpy(mochila->itens[mochila->qntd].tipo, tipo, MAX_STR_LEN);
    mochila->itens[mochila->qntd].quantidade = quantidade;
    mochila->qntd++;
    printf("\nItem '%s' adicionado com sucesso!\n", nome);
}

// Função para remover um item da mochila
void removerItem(Mochila *mochila, const char* nome){
    int i, pos = -1;

    // Procura o item pelo nome
    for(i = 0; i < mochila->qntd;i++){
        if(strcmp(mochila->itens[i].nome, nome) == 0){
            pos = i; // Encontrou o item, guarda a posição
            break; // Sai do loop
        }
    }
    // Tratamento de Erro: Se o loop terminar e pos continuar -1, o item não foi encontrado.
    if(pos == -1){
        printf("\nItem '%s' nao encontrado na mochila.\n", nome);
        return;
    }

    // Fechar a lacuna: Se removemos um item do meio da lista, criamos um "buraco".
    // O loop for começa na posição do item removido e copia cada item i+1
    for (i = pos; i < mochila->qntd - 1; i++){
        strcpy(mochila->itens[i].nome, mochila->itens[i + 1].nome);
        strcpy(mochila->itens[i].tipo, mochila->itens[i + 1].tipo);
        mochila->itens[i].quantidade = mochila->itens[i + 1].quantidade;
    }

    // Decrementa a quantidade de itens na mochila
    mochila->qntd--;
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// Função para listar os itens da mochila
void listarItem(const Mochila *mochila){

    // Verifica se a mochila está vazia
    if(mochila->qntd == 0){
        printf("\nA mochila esta vazia.\n");
        printf("\nPressione Enter para continuar...");
        getchar(); // pausa até o usuário apertar Enter
        return;
    }

    // Cabeçalho da tabela
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", mochila->qntd, TAM_MAX);
    printf("-----------------------------------------------------\n");
    printf("%-15s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-----------------------------------------------------\n");

    // Loop para imprimir cada item
    for(int i = 0; i < mochila->qntd; i++){
        printf("%-15s | %-15s | %-10d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
    }
    printf("-----------------------------------------------------\n");
    printf("\nPressione Enter para continuar...");
    getchar(); // pausa até o usuário apertar Enter
}