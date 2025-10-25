#include <stdio.h>    // Entrada e saída padrão
#include <stdlib.h>   // Alocação de memória (malloc, free)
#include <string.h>   // Manipulação de strings (strcmp, strcpy, etc.)a

#define MAX_STR_LEN 50  // Tamanho máximo de cada string (nome/tipo)
#define TAM_MAX 10      // Capacidade máxima da mochila estática

// ======================
// ESTRUTURAS DE DADOS
// ======================

// Estrutura que representa um item
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
} Item;

// Estrutura da mochila estática (vetor)
typedef struct {
    Item itens[TAM_MAX];
    int qntd;
} Mochila;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =============================
// FUNÇÕES LISTA ESTÁTICA (VETOR)
// =============================

// Inicializa a mochila (zera a quantidade)
void inicializarMochila(Mochila *mochila) {
    mochila->qntd = 0;
}

// Adiciona item no vetor
void inserirItemVetor(Mochila *mochila, const char* nome, const char* tipo, int quantidade) {

    // O if verifica se a quantidade atual (qtd) já é igual ou maior que o limite máximo (10)
    if (mochila->qntd >= TAM_MAX) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    // Copia o nome do item passado como parâmetro para o vetor da mochila
    strncpy(mochila->itens[mochila->qntd].nome, nome, MAX_STR_LEN);

    // Copia o tipo do item passado como parâmetro para o vetor da mochila
    strncpy(mochila->itens[mochila->qntd].tipo, tipo, MAX_STR_LEN);

     // Atribui a quantidade ao item
    mochila->itens[mochila->qntd].quantidade = quantidade;

    // Incrementa a quantidade de itens na mochila
    mochila->qntd++;

    printf("\nItem '%s' adicionado com sucesso!\n", nome);
}

// / Função para remover um item da mochila (versão com vetor)
void removerItemVetor(Mochila *mochila, const char* nome) {

    //  'pos' guarda a posição do item a remover
    int pos = -1;

    // Percorre a mochila para encontrar o item com o nome especificado
    for (int i = 0; i < mochila->qntd; i++) {

        // Compara o nome do item atual com o nome informado
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i; // Se encontrou, guarda a posição
            break; 
        }
    }

     // Se 'pos' ainda for -1, o item não foi encontrado
    if (pos == -1) {
        printf("\nItem '%s' nao encontrado.\n", nome);
        return;
    }
 
    // Se encontrou o item, "fecha a lacuna" movendo todos os itens posteriores uma posição para trás
    for (int i = pos; i < mochila->qntd - 1; i++) {
        strcpy(mochila->itens[i].nome, mochila->itens[i + 1].nome); // Copia o nome do próximo item
        strcpy(mochila->itens[i].tipo, mochila->itens[i + 1].tipo); // Copia o tipo do próximo item
        mochila->itens[i].quantidade = mochila->itens[i + 1].quantidade; // Copia a quantidade
    }

    // Decrementa a quantidade de itens da mochila, pois um item foi removido
    mochila->qntd--;
    printf("\nItem '%s' removido com sucesso!\n", nome);
}

// Lista todos os itens
void listarItensVetor(const Mochila *mochila) {

    // Verifica se a mochila está vazia
    if (mochila->qntd == 0) {
        printf("\nA mochila esta vazia.\n");
        printf("\nPressione Enter para continuar...");  // Mensagem de pausa
        getchar(); // Espera o usuário pressionar Enter
        return; // Sai da função, não há itens para listar
    }

    // Imprime o cabeçalho da tabela
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", mochila->qntd, TAM_MAX);
    printf("%-15s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

    // Loop para percorrer todos os itens da mochila
    for (int i = 0; i < mochila->qntd; i++) {
        printf("%-15s | %-15s | %-10d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
    }
}

// Ordena os itens pelo nome (Bubble Sort)
void ordenarItens(Mochila *mochila) {

    // Variável temporária para fazer a troca de posições dos itens
    Item temp;

    // Loop externo percorre cada posição da lista até a penúltima
    for (int i = 0; i < mochila->qntd - 1; i++) {

        // Loop interno percorre da primeira posição até a última não ordenada
        for (int j = 0; j < mochila->qntd - i - 1; j++) {

              // Compara o nome do item atual com o próximo
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {

                temp = mochila->itens[j]; // Salva o item atual temporariamente
                mochila->itens[j] = mochila->itens[j + 1]; // Coloca o próximo item no lugar do atual
                mochila->itens[j + 1] = temp; // Coloca o item atual na posição do próximo
            }
            }
        }
          printf("\nItens ordenados com sucesso (Bubble Sort).\n");
    }
 

// Função de busca sequencial
void buscarItemSequencial(const Mochila *mochila, const char* nome) {

    // Contador para registrar o número de comparações feitas
    int comparacoes = 0;

    // Percorre todos os itens da mochila
    for (int i = 0; i < mochila->qntd; i++) {
        // Incrementa o contador a cada comparação
        comparacoes++;

        // Verifica se o nome do item atual é igual ao nome procurado
        if (strcmp(mochila->itens[i].nome, nome) == 0) {

            // Item encontrado, exibe os detalhes
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   mochila->itens[i].nome,
                   mochila->itens[i].tipo,
                   mochila->itens[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
    }

     // Se chegar aqui, o item não foi encontrado
    printf("\nItem '%s' nao encontrado.\n", nome);

    // Exibe o número total de comparações feitas
    printf("\nComparacoes: %d\n",comparacoes);
}

// Função de busca binária (requer vetor ordenado)
void buscarItemBinaria(const Mochila *mochila, const char* nome) {

    int inicio = 0; // Índice inicial da busca
    int fim = mochila->qntd - 1; // // Índice final da busca
    int comparacoes = 0;  // Contador de comparações realizadas

     // Enquanto ainda houver elementos a serem verificados
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2; // Calcula o índice do elemento do meio
        comparacoes++;  // Incrementa o contador de comparações

         // Compara o item do meio com o nome procurado
        int cmp = strcmp(mochila->itens[meio].nome, nome);
        if (cmp == 0) {

             // Item encontrado
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   mochila->itens[meio].nome,
                   mochila->itens[meio].tipo,
                   mochila->itens[meio].quantidade);
            
             // Exibe quantas comparações foram feitas
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;

            // Se o item do meio é menor que o procurado
            // Então, o item procurado está na esquerda
        } else if (cmp < 0) {
            inicio = meio + 1;

            // Se o item do meio é maior que o procurado
            // Então, o item procurado está na direita
        } else {
            fim = meio - 1;
        }
    }

    // Se chegar aqui, o item não foi encontrado
    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Comparacoes: %d\n",comparacoes);
}

// ======================
// FUNÇÕES LISTA ENCADEADA
// ======================

// Função para inserir um novo item na (lista encadeada)
void inserirNovoItem(No **cabeca, const char* nome, const char* tipo, int quantidade) {
     // Cria um novo nó na memória
    No *novoNo = (No*) malloc(sizeof(No));
    // Verifica se a alocação falhou
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    // Copia os dados para o novo nó
    strcpy(novoNo->dados.nome, nome);
    strcpy(novoNo->dados.tipo, tipo);
    novoNo->dados.quantidade = quantidade;

    // Faz o novo nó apontar para o primeiro nó atual da lista
    novoNo->proximo = *cabeca;

    // Atualiza a cabeça da lista para ser o novo nó da lista
    *cabeca = novoNo;

    printf("\nItem '%s' inserido com sucesso!\n", nome);
}

// Função remover item da lista
void removerItemLista(No** cabeca, const char* nome) {
    No* atual = *cabeca; // Começa pelo primeiro nó
    No* anterior = NULL; // Guarda o nó anterior ao atual

    // Percorre a lista até encontrar o item
    while (atual != NULL && strcmp(atual->dados.nome, nome) == 0) {
        anterior = atual;  // Atualiza o nó anterior
        atual = atual->proximo; // Vai para o próximo nó
    }

     // Caso o item não seja encontrado
    if (atual == NULL) {
        printf("\nItem '%s' nao encontrado!\n", nome);
        return;
    }

     // O item está no primeiro nó
    if (anterior == NULL) {
        *cabeca = atual->proximo; // Atualiza a cabeça

    } else {
         // Item no meio ou final
        anterior->proximo = atual->proximo; // Remove da lista
    }

    free(atual); // Libera a memória do nó
    printf("\nItem '%s' removido com sucesso!\n", nome);
    return;
}

// Função para listar itens da lista
void listarItensLista(const No *cabeca) {

    // Verifica se a cabeça (inicio da lista está vazia).
    if (cabeca == NULL) {
        printf("\nA mochila esta vazia.\n");
        return;
    }
    
    // Imprime cabeçalho da tabela
    printf("\n--- ITENS NA MOCHILA (LISTA ENCADEADA) ---\n");
    printf("%-15s | %-15s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("---------------------------------------------\n");

     // Percorre todos os nós da lista
    while (cabeca != NULL) {
        printf("%-15s | %-15s | %-10d\n",
               cabeca->dados.nome,
               cabeca->dados.tipo,
               cabeca->dados.quantidade);
        cabeca = cabeca->proximo; // Passa para o próximo nó da lista
    }
}

// Função que busca um item na lista encadeada
void buscarItemLista(const No *cabeca, const char* nome) {
    int comparacoes = 0; // Contador de comparações realizadas

     // Percorre todos os nós da lista
    while (cabeca != NULL) {

        // Conta cada comparação feita
        comparacoes++;

        // Verifica se o nome do item atual é igual ao procurado
        if (strcmp(cabeca->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s), Quantidade: %d\n",
                   cabeca->dados.nome,
                   cabeca->dados.tipo,
                   cabeca->dados.quantidade);

             // Mostra o número de comparações realizadas
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
        // Passa para o próximo nó da lista
        cabeca = cabeca->proximo;
    }
    printf("\nItem '%s' nao encontrado\n", nome);
    printf("\nComparacoes: %d\n", comparacoes);
}

// ======================
// MENUS
// ======================

// Função: menuListaEstatica
// Objetivo: Fornece um menu interativo para manipulação 
// da mochila usando um vetor estático. Permite ao usuário:
//  - Adicionar itens
//  - Remover itens
//  - Listar itens
//  - Ordenar itens (Bubble Sort)
//  - Buscar itens (sequencial e binária)
//  - Utiliza um vetor estático para armazenar os itens, limitando a quantidade máxima.
// O menu permanece ativo até o usuário escolher voltar.
// ========================================================

void menuListaEstatica() {
    Mochila mochila; // Cria uma variável 'mochila' do tipo Mochila (vetor estático)
    inicializarMochila(&mochila); // Inicializa a mochila

    int opcao;  // Variável para armazenar a opção escolhida pelo usuário
    char nome[30], tipo[20]; // Variáveis para armazenar temporariamente o nome e tipo do item
    int quantidade; // Variável para armazenar a quantidade do item

    // Início do loop que mantém o menu ativo até o usuário escolher sair
    do {
        printf("\n==== MOCHILA (VETOR ESTATICO) ====\n");
        printf("\n1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar (Bubble Sort)\n");
        printf("5. Buscar Sequencial\n");
        printf("6. Buscar Binaria\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
               // Se opção 1: adicionar item
                printf("Nome: "); fgets(nome, sizeof(nome), stdin); // Lê o nome do item
                nome[strcspn(nome, "\n")] = 0; // Remove o '\n' no final da string


                printf("Tipo: "); 
                fgets(tipo, sizeof(tipo), stdin); // Lê o tipo do item
                tipo[strcspn(tipo, "\n")] = 0; // Remove o '\n' no final da string

                printf("Quantidade: "); scanf("%d", &quantidade); // Lê a quantidade do item
                getchar();  // Limpa o '\n' deixado pelo scanf

                inserirItemVetor(&mochila, nome, tipo, quantidade); // Chama a função que insere o item na mochila
                break;
           
            case 2:
             // Se opção 2: remover item
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin);  // Lê o nome do item a ser removido
                nome[strcspn(nome, "\n")] = 0; // Remove '\n

                removerItemVetor(&mochila, nome); // Chama função que remove o item da mochila
                break;

            // Se opção 3: listar itens
            case 3:
                listarItensVetor(&mochila);  // Chama função que exibe todos os itens da mochila
                break;

            // Se opção 4: ordenar itens
            case 4:
                ordenarItens(&mochila); // Chama função que ordena os itens usando Bubble Sort
                break;

            // Se opção 5: buscar item sequencial
            case 5:
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin); // Lê o nome do item a ser buscado
                nome[strcspn(nome, "\n")] = 0;  // Remove '\n
        
                buscarItemSequencial(&mochila, nome); // Chama função que realiza busca sequencial
                break;

            // Se opção 6: buscar item binário
            case 6:
                ordenarItens(&mochila); // Primeiro ordena os itens (necessário para busca binária)
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin); // Lê o nome do item a ser buscado
                nome[strcspn(nome, "\n")] = 0; // Remove '\n

                buscarItemBinaria(&mochila, nome); // Chama função que realiza busca binária
                break;
        }
    } while (opcao != 0);  // Continua o loop enquanto a opção for diferente de 0
}

// Função: menuListaEncadeada
// Objetivo: Fornece um menu interativo para manipulação 
// da mochila usando uma lista encadeada. Permite ao usuário:
//  - Adicionar itens
//  - Remover itens
//  - Listar itens
//  - Buscar itens
//  - Utiliza uma lista encadeada (dinâmica), permitindo crescimento
//    ilimitado enquanto houver memória disponível.
// O menu permanece ativo até o usuário escolher voltar.
// ========================================================
void menuListaEncadeada() {
    No *mochila = NULL; // Cria a cabeça da lista encadeada (início da lista) e inicializa como NULL
    int opcao;   // Variável para armazenar a opção do usuário
    char nome[30], tipo[20]; // Variáveis para armazenar temporariamente nome e tipo do item
    int quantidade; // Variável para armazenar a quantidade do item

    // Início do loop que mantém o menu ativo até o usuário escolher sair
    do {
        printf("\n==== MOCHILA (LISTA ENCADEADA) ====\n");
        printf("\n1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            // Se opção 1: adicionar item
            case 1:
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin); // Lê o nome do item
                nome[strcspn(nome, "\n")] = 0;  // Remove '\n' do final da string


                printf("Tipo: "); 
                fgets(tipo, sizeof(tipo), stdin); // Lê o tipo do item
                tipo[strcspn(tipo, "\n")] = 0; // Remove '\n'

                printf("Quantidade: "); 
                scanf("%d", &quantidade);  // Lê a quantidade do item
                getchar(); // Limpa '\n' do buffer

                inserirNovoItem(&mochila, nome, tipo, quantidade);  // Chama função que insere um novo nó na lista
                break;

            case 2:
            // Se opção 2: remover item
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin); // Lê o nome do item a ser removido
                nome[strcspn(nome, "\n")] = 0; // Remove '\n'

                removerItemLista(&mochila, nome); // Chama função que remove o item da lista
                break;

            case 3:
            // Se opção 3: listar itens
                listarItensLista(mochila); // Chama função que percorre a lista e exibe todos os itens
                break;

            case 4:
            // Se opção 4: buscar item
                printf("Nome: "); 
                fgets(nome, sizeof(nome), stdin); // Lê o nome do item a ser buscado
                nome[strcspn(nome, "\n")] = 0; // Remove '\n'

                buscarItemLista(mochila, nome); // Chama função que percorre a lista e busca o item
                break;
        }
    } while (opcao != 0); // Continua o loop enquanto o usuário não escolher 0

    // Libera a memória de todos os nós da lista antes de sair
    No *temp; // Variável auxiliar para armazenar o nó a ser liberado
    while (mochila != NULL) { // Enquanto houver nós na lista
        temp = mochila;  // Armazena o nó atual
        mochila = mochila->proximo; // Avança para o próximo nó
        free(temp); // Libera a memória do nó atual
    }
    }


// ======================
// FUNÇÃO PRINCIPAL
// ======================

int main() {
    
    int opcao;

    // Início do loop do menu principal. Continua até o usuário escolher sair
     do {
        printf("\n===== MOCHILA DE SOBREVIVENCIA =====\n");
        printf("\n1. Mochila (Vetor Estático)\n");
        printf("2. Mochila (Lista Encadeada)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        // Estrutura para decidir qual ação executar com base na escolha
        switch (opcao) {
            
            // Se o usuário escolheu 1
            // Chama a função que abre o menu da mochila usando vetor estático
            case 1:
                menuListaEstatica();
                break;

            // Se o usuário escolheu 2
            // Chama a função que abre o menu da mochila usando lista encadeada 
            case 2:
                menuListaEncadeada();
                break;
            
            // Se o usuário escolheu 0
            // Mensagem de saída
            case 0:
                printf("Saindo do programa...\n");
                break;
            
            // Caso o usuário digite qualquer número diferente de 0,1 ou 2
            // Mensagem de erro
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);  // Continua repetindo o menu enquanto a opção não for 0

    return 0; // Finaliza o programa retornando 0 (sucesso)
}

