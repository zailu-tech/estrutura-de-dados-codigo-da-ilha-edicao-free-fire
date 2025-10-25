#include <stdio.h> // Entrada e saída padrão
#include <string.h> // Manipulação de strings (strcmp, strcpy, etc.)
#include <stdbool.h> // Para usar o tipo bool
#include <time.h> // Para medir o tempo de execução

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_STR_LEN 50  // Tamanho máximo de cada string (nome/tipo)
#define TAM_MAX 10 

typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
    int prioridade;
} Item;


// Estrutura da mochila estática (vetor)
typedef struct {
    Item itens[TAM_MAX];
    int qntd;
    bool ordenadoNome; // Flag que indica se está ordenado por nome
} Mochila;

// Inicializa a mochila (zera a quantidade)
void inicializarMochila(Mochila *mochila) {
    mochila->qntd = 0;
    mochila->ordenadoNome = false; // inicializa como desordenado
}

// Adiciona item no vetor
void inserirItemVetor(Mochila *mochila, const char* nome, const char* tipo, int quantidade,
    int prioridade) {

    if (mochila->qntd >= TAM_MAX) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    // copia com segurança e garante terminador nulo
    strncpy(mochila->itens[mochila->qntd].nome, nome, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].nome[MAX_STR_LEN - 1] = '\0';

    strncpy(mochila->itens[mochila->qntd].tipo, tipo, MAX_STR_LEN - 1);
    mochila->itens[mochila->qntd].tipo[MAX_STR_LEN - 1] = '\0';

    mochila->itens[mochila->qntd].quantidade = quantidade;
    mochila->itens[mochila->qntd].prioridade = prioridade;

    mochila->qntd++;
    mochila->ordenadoNome = false; // novo item quebra a ordenação por nome
    printf("\nItem '%s' adicionado com sucesso!\n", nome);
}

// / Função para remover um item da mochila
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
        mochila->itens[i].prioridade = mochila->itens[i + 1].prioridade; // Copia a prioridade
    }

    // Decrementa a quantidade de itens da mochila, pois um item foi removido
    mochila->qntd--;
    mochila->ordenadoNome = false; // remoção pode quebrar a ordenação
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
    printf("\n --- INVENTARIO ATUAL --- (%d/%d) ", mochila->qntd, TAM_MAX);
    printf("\n-------------------------------------------------------------\n");
    printf("%-15s | %-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("----------------------------------------------------------------\n");

    // Loop para percorrer todos os itens da mochila
    for (int i = 0; i < mochila->qntd; i++) {
        printf("%-15s | %-15s | %-10d | %-10d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade,
               mochila->itens[i].prioridade);
    }
               printf("-----------------------------------------------------------------\n");
               printf("\nPressione Enter para continuar...");
        getchar(); // pausa até o usuário apertar Enter
    
    }
    


// Função de ordenação por nome (Bubble Sort)

void bubbleSortNome(Mochila *mochila) {
    clock_t inicio, fim = clock(); // Marca o início do tempo de execução
    double tempo;           // Variável para armazenar o tempo decorrido
    inicio = clock(); // Marca o início do tempo de execução

     // Se a mochila tem menos de 2 itens, já está ordenada
    if (mochila->qntd < 2) {
        mochila->ordenadoNome = true;
        return;
    }

    // Implementação do Bubble Sort
    int comparacoes = 0;
    Item temp;
    for (int i = 0; i < mochila->qntd - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < mochila->qntd - i - 1; j++) {
            comparacoes++;
            // Compara o nome do item atual com o próximo
            if (strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0) {
                temp = mochila->itens[j]; // Salva o item atual temporariamente
                mochila->itens[j] = mochila->itens[j + 1]; // Coloca o próximo item no lugar do atual
                mochila->itens[j + 1] = temp; // Coloca o item atual na posição do próximo
                trocou = 1;
            }
            
        }

        if (!trocou) // Se não houve trocas na passagem, a lista já está ordenada
        break; 
    }

    fim = clock(); // Marca o fim do tempo de execução
    tempo =((double)(fim-inicio)) / CLOCKS_PER_SEC;
    mochila->ordenadoNome = true; // marca como ordenado por nome

    printf("\nMochila organizada por Nome.\n");
    printf("\nComparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    listarItensVetor(mochila);
}

// Função de ordenação por tipo (Insertion Sort)
void OrdenarPorTipo(Mochila *mochila){
    clock_t inicio, fim = clock(); // Marca o início do tempo de execução
    double tempo;           // Variável para armazenar o tempo decorrido
    inicio = clock(); // Marca o início do tempo de execução
    int comparacoes = 0;

    // Implementação do Insertion Sort
    for(int i = 1; i < mochila->qntd; i++){
        Item chave = mochila->itens[i];
        int j = i -1;
         
        // Move os elementos maiores que 'chave' para uma posição à frente
        while (j >= 0 && strcmp(mochila->itens[j].tipo, chave.tipo) > 0){ // desloca os elementos maiores para a direita
            mochila->itens[j + 1] = mochila->itens[j];  // Desloca o elemento para a direita
            j = j - 1; // Move para o próximo elemento
            comparacoes++; // Conta a comparação realizada
        }
        mochila->itens[j + 1] = chave;
        
    }

    // Finaliza a medição do tempo
    fim = clock(); // Marca o fim do tempo de execução
    tempo =((double)(fim-inicio)) / CLOCKS_PER_SEC;
    printf("\nItens ordenados por Tipo.");
    printf("\nComparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    listarItensVetor(mochila);
}
    
void OrdenarPorPrioridade(Mochila *mochila) { 
    clock_t inicio, fim = clock(); // Marca o início do tempo de execução
    double tempo;           // Variável para armazenar o tempo decorrido
    inicio = clock(); // Marca o início do tempo de execução

    int comparacoes = 0; // Contador de comparações realizadas
    for (int i = 0; i < mochila->qntd - 1; i++) {

        // Assume que o menor, por enquanto, é o elemento na posição 'i'.
        int indiceMenor = i;

        // laço interno: busca pelo menor elemento no resto do vetor (à direita de 'i').
        for (int j = i + 1; j < mochila->qntd; j++) {
            comparacoes ++;
            // Se encontrar um elemento ainda menor...
            if (mochila->itens[j].prioridade > mochila->itens[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }

        // Se o menor não for o elemento na posição 'i', faz a troca.
        if (indiceMenor != i) {
            // Realiza a troca.
            Item temp = mochila->itens[i];
            mochila->itens[i] = mochila->itens[indiceMenor];
            mochila->itens[indiceMenor] = temp;
        }
    }

    fim = clock(); // Marca o fim do tempo de execução
    tempo =((double)(fim-inicio)) / CLOCKS_PER_SEC; // Calcula o tempo de execução

    printf("\nItens ordenados por Prioridade.");
    printf("\nComparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    listarItensVetor(mochila);
}

// Função de busca binária (requer vetor ordenado)
void buscarItemBinaria(const Mochila *mochila, const char* nome) {

    int inicio = 0; // Índice inicial da busca
    int fim = mochila->qntd - 1; // // Índice final da busca
    int comparacoes = 0;  // Contador de comparações realizadas

     // Enquanto ainda houver elementos a serem verificados
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2; // Calcula o índice do elemento do meio
        comparacoes++;
         // Compara o item do meio com o nome procurado
        int cmp = strcmp(mochila->itens[meio].nome, nome);
        if (cmp == 0) {

             // Item encontrado
     printf("\n---------------------------------------------------------\n");
     printf("           COMPONENTE-CHAVE ENCONTRADO!            \n");
     printf("---------------------------------------------------------\n");
            printf("Nome: %s, Tipo: %s, Qtd: %d, Prioridade: %d\n",
                   mochila->itens[meio].nome,
                   mochila->itens[meio].tipo,
                   mochila->itens[meio].quantidade,
                   mochila->itens[meio].prioridade);
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
}
int main() {
    Mochila mochila;
    inicializarMochila(&mochila);
    int opcao;
    char nome[ MAX_STR_LEN ];
    char tipo[ MAX_STR_LEN ];
    int quantidade;
    int prioridade;

    do {
        printf("\n=============================================\n");
        printf("    PLANO DE FUGA - CODIGO DA ILHA            ");
        printf("\n=============================================\n");
        printf("ITENS NA MOCHILA (%d/%d)\n", mochila.qntd, TAM_MAX);
        printf("Status da ordenacao por Nome: %s\n", (mochila.ordenadoNome ? "Ordenado" : "Desordenado"));

         
        printf("\n1. Adicionar Componente\n");
        printf("2. Remover Componente\n");
        printf("3. Listar Componentes\n");
        printf("4. Ordenar Componentes por Nome/Tipo/Prioridade\n");
        printf("5. Busca Binaria por Nome\n");
        printf("0. ATIVAR TORRE (Sair)\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        // Processa a opção escolhida
        switch (opcao) {
            case 1: {
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Tipo (Estrutural, Eletronico, Energia): ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();

                printf("Prioridade de Montagem (1-5): ");
                scanf("%d", &prioridade);
                getchar();

                inserirItemVetor(&mochila, nome, tipo, quantidade, prioridade);
                break;
            }
            case 2: {
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerItemVetor(&mochila, nome);
                break;
            }
            case 3:
                listarItensVetor(&mochila);
                break;
            case 4: {
                // Menu de critérios de ordenação
                int criterio;
                printf("-- Estrategia de Organizacao ---\n");
                printf("1. Por Nome (Bubble Sort)\n");
                printf("2. Por Tipo (Insertion Sort)\n");
                printf("3. Por Prioridade (Selection Sort)\n");
                printf("0. Cancelar\n");
                printf("-----------------------------------------------\n");
                printf("Escolha o criterio: ");
                scanf("%d", &criterio);
                getchar();

                // Executa a ordenação conforme o critério escolhido
                if (criterio == 1) bubbleSortNome(&mochila);
                else if (criterio == 2) OrdenarPorTipo(&mochila);
                else if (criterio == 3) OrdenarPorPrioridade(&mochila);
                break;
            }
            case 5: {
                if(!mochila.ordenadoNome) {
                    printf("\nAVISO: A mochila nao esta ordenada por Nome.");
                    printf("Use a opcao 4 para organizar a mochila primeiro\n");
                    printf("\nPressione Enter para continuar...");
                    getchar(); // pausa até o usuário apertar Enter
                    break;
                }
                printf("\n--- Busca Binaria por Componente-Chave ---\n");
                printf("Nome do componente a buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarItemBinaria(&mochila, nome);
                printf("\nPressione Enter para continuar...");
                getchar(); // pausa até o usuário apertar Enter
                break;
                    
            }
            case 0:
                printf("\nAtivando a torre e escapando da ilha!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}




