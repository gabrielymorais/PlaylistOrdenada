#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar cada música
typedef struct Musica {
    char titulo[100];            // String para armazenar o título da música (máximo 100 caracteres)
    char artista[100];           // String para armazenar o nome do artista (máximo 100 caracteres)
    int duracao;                 // Armazena a duração da música em segundos
    struct Musica* prev;         // Ponteiro para a música anterior (para a lista duplamente encadeada)
    struct Musica* next;         // Ponteiro para a próxima música (para a lista duplamente encadeada)
} Musica;                        // Define o tipo Musica

// Estrutura para a playlist
typedef struct {
    Musica* inicio;              // Ponteiro para a primeira música da playlist
    Musica* fim;                 // Ponteiro para a última música da playlist
    Musica* atual;               // Ponteiro para a música atual (que está sendo "tocada")
    int totalMusicas;            // Contador para o número total de músicas na playlist
    int duracaoTotal;            // Armazena a duração total de todas as músicas na playlist (em segundos)
} Playlist;                      // Define o tipo Playlist

// Função para inicializar a playlist
void inicializarPlaylist(Playlist* playlist) {
    playlist->inicio = NULL;     // Inicializa a playlist sem nenhuma música (ponteiro nulo para o início)
    playlist->fim = NULL;        // Inicializa o ponteiro de fim como nulo (playlist vazia)
    playlist->atual = NULL;      // Inicializa o ponteiro de música atual como nulo (sem música tocando)
    playlist->totalMusicas = 0;  // Inicializa o número de músicas como zero
    playlist->duracaoTotal = 0;  // Inicializa a duração total como zero
}

// Função para adicionar música no fim da playlist
void adicionarMusica(Playlist* playlist) {
    Musica* nova = (Musica*)malloc(sizeof(Musica));   // Aloca memória para uma nova música

    // Solicita os dados da música ao usuário
    printf("Digite o titulo da musica: ");            // Pede o título da música
    scanf(" %[^\n]", nova->titulo);                   // Lê o título da música
    printf("Digite o nome do artista: ");             // Pede o nome do artista
    scanf(" %[^\n]", nova->artista);                  // Lê o nome do artista
    printf("Digite a duracao da musica (em segundos): "); // Pede a duração da música em segundos
    scanf("%d", &nova->duracao);                      // Lê a duração da música

    nova->next = NULL;        // Como é uma nova música, não há próxima música ainda (ponteiro para NULL)
    nova->prev = NULL;        // Como será a última, também não há música anterior ainda

    // Insere a música no fim da playlist
    if (playlist->inicio == NULL) {   // Se a playlist estiver vazia (início nulo)
        playlist->inicio = nova;      // Define a nova música como o início da playlist
        playlist->fim = nova;         // E também como o fim (pois é a única)
        playlist->atual = nova;       // A música atual também será essa (primeira)
    } else {                          // Caso contrário (já há músicas na playlist)
        playlist->fim->next = nova;   // Define a nova música como a próxima da última música existente
        nova->prev = playlist->fim;   // Define a última música atual como a anterior da nova música
        playlist->fim = nova;         // Atualiza o ponteiro de fim para a nova música
    }

    playlist->totalMusicas++;               // Incrementa o contador de músicas
    playlist->duracaoTotal += nova->duracao; // Adiciona a duração da nova música ao total
    printf("\n");
    printf("| MUSICA ADICIONADA COM SUCESSO |\n");  // Confirma que a música foi adicionada
}

// Função para remover música pelo título
void removerMusica(Playlist* playlist, char* titulo) {
    Musica* temp = playlist->inicio;        // Começa a busca da música a ser removida do início da playlist

    while (temp != NULL) {                  // Percorre a playlist até encontrar a música ou o fim
        if (strcmp(temp->titulo, titulo) == 0) {  // Compara o título da música atual com o título dado
            // Caso seja o único nó
            if (temp->prev == NULL && temp->next == NULL) {
                playlist->inicio = NULL;    // Se for a única música, esvazia a playlist
                playlist->fim = NULL;
            }
            // Caso seja o primeiro nó
            else if (temp->prev == NULL) {
                playlist->inicio = temp->next;    // Atualiza o início para a próxima música
                playlist->inicio->prev = NULL;    // Remove o vínculo com a música removida
            }
            // Caso seja o último nó
            else if (temp->next == NULL) {
                playlist->fim = temp->prev;       // Atualiza o fim para a música anterior
                playlist->fim->next = NULL;       // Remove o vínculo com a música removida
            }
            // Caso esteja no meio
            else {
                temp->prev->next = temp->next;    // Conecta a música anterior à próxima
                temp->next->prev = temp->prev;    // Conecta a próxima à anterior
            }

            free(temp);                           // Libera a memória da música removida
            playlist->totalMusicas--;             // Decrementa o número total de músicas
            printf("\n");
            printf("| MUSICA REMOVIDA COM SUCESSO |\n"); // Confirma que a música foi removida
            return;                               // Sai da função após remover
        }
        temp = temp->next;                        // Avança para a próxima música
    }

    printf("| MUSICA NAO ENCONTRADA |\n");        // Exibe mensagem se a música não for encontrada
}

// Função para mostrar a playlist completa
void mostrarPlaylist(Playlist* playlist) {
    Musica* temp = playlist->inicio;// Começa do início da playlist
    if (temp == NULL) {// Se a playlist estiver vazia
        printf("| A PLAYLIST ESTA VAZIA |\n");
        return;
    }
    printf("Playlist completa:\n");
    while (temp != NULL) { // Percorre todas as músicas da playlist
        printf("\n");
        printf("Titulo: %s | Artista: %s | Duracao: %d segundos\n", temp->titulo, temp->artista, temp->duracao);
        printf("\n");

        temp = temp->next;// Avança para a próxima música
    }

    printf("\n");
    printf("Total de musicas: %d\n", playlist->totalMusicas);  // Exibe o total de músicas
    printf("Duração total: %d segundos\n", playlist->duracaoTotal);  // Exibe a duração total
    printf("\n");
}

// Função para avançar para a próxima música
void proximaMusica(Playlist* playlist) {
    if (playlist->atual != NULL && playlist->atual->next != NULL) {  // Verifica se há próxima música
        playlist->atual = playlist->atual->next;// Atualiza a música atual para a próxima
        printf("\n");
        printf("Tocando agora: %s - %s\n", playlist->atual->titulo, playlist->atual->artista);  // Exibe a nova música
        printf("\n");

    } else {
        printf("\n");
        printf("| NAO HA PROXIMA MUSICA |\n");        
    }
}

// Função para voltar para a música anterior
void musicaAnterior(Playlist* playlist) {
    if (playlist->atual != NULL && playlist->atual->prev != NULL) { // Verifica se há música anterior
        playlist->atual = playlist->atual->prev; // Atualiza a música atual para a anterior
        printf("Tocando agora: %s - %s\n", playlist->atual->titulo, playlist->atual->artista); // Exibe a música anterior
    } else {
        printf("\n");
        printf("| NAO HA MUSICA ANTERIOR |\n");   
    }
}


// Função para ordenar as músicas pelo tempo de duração (Selection Sort)
void ordenarPorDuracao(Playlist* playlist) {
    // Função que ordena a playlist por duração (usando o algoritmo de seleção).
    // Recebe um ponteiro para a estrutura da playlist.
    
    if (playlist->inicio == NULL) {
        // Verifica se a playlist está vazia.
        printf("| A PLAYLIST ESTA VAZIA |\n");
        return;
    }

    Musica* i = playlist->inicio;
    // Ponteiro 'i' aponta para o início da playlist e percorre cada música.
    // Será utilizado para controlar a parte "ordenada" da lista.

    while (i != NULL) {
        // Laço externo: percorre a lista até o final (até que i seja NULL).
        Musica* menor = i;
        // Ponteiro 'menor' inicialmente aponta para 'i'.
        // Será usado para encontrar a música com a menor duração a partir de 'i'.
        
        Musica* j = i->next;
        // Ponteiro 'j' inicia do próximo nó após 'i', para comparar as músicas subsequentes.
        
        while (j != NULL) {
            // Laço interno: percorre o restante da lista a partir de 'j' para encontrar a música com menor duração.
            if (j->duracao < menor->duracao) {
                // Se a duração da música atual (j) for menor que a duração da música em 'menor',
                // atualizamos o ponteiro 'menor' para apontar para a música 'j'.
                menor = j;
            }
            j = j->next;
            // Avança para a próxima música na lista.
        }

        if (menor != i) {
            // Se 'menor' não for igual a 'i', significa que encontramos uma música com menor duração que 'i',
            // então faremos a troca dos dados entre 'i' e 'menor'.
            
            // Variáveis temporárias para armazenar os dados de 'i' antes da troca.
            char tempTitulo[100], tempArtista[100];
            int tempDuracao;

            // Copia os dados da música 'i' para as variáveis temporárias.
            strcpy(tempTitulo, i->titulo);
            strcpy(tempArtista, i->artista);
            tempDuracao = i->duracao;

            // Copia os dados da música 'menor' para a música 'i' (realizando a troca).
            strcpy(i->titulo, menor->titulo);
            strcpy(i->artista, menor->artista);
            i->duracao = menor->duracao;

            // Copia os dados temporários (que eram de 'i') para 'menor'.
            strcpy(menor->titulo, tempTitulo);
            strcpy(menor->artista, tempArtista);
            menor->duracao = tempDuracao;
        }
        i = i->next;
        // Avança para a próxima música (nó) na lista e repete o processo.
    }

    printf("| PLAYLIST ORDENADA POR DURACAO |\n");
}


int main() {
    Playlist minhaPlaylist;
    inicializarPlaylist(&minhaPlaylist);
    
    int opcao;
    char titulo[100];

    do {
        printf("\n+--------------------------------------+\n");
        printf("|            PLAYLIST MENU             |\n");
        printf("+--------------------------------------+\n");
        printf("|  1. Adicionar Musica                 |\n");
        printf("|  2. Remover Musica                   |\n");
        printf("|  3. Mostrar Playlist                 |\n");
        printf("|  4. Avancar para a proxima musica    |\n");
        printf("|  5. Voltar para a musica anterior    |\n");
        printf("|  6. Ordenar musicas por duracao      |\n");
        printf("|  0. Sair                             |\n");
        printf("+--------------------------------------+\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcao);
     
        switch(opcao) {
            case 1:
                adicionarMusica(&minhaPlaylist);
                break;
            case 2:
                printf("Digite o titulo da musica a ser removida: ");
                scanf(" %[^\n]", titulo);
                removerMusica(&minhaPlaylist, titulo);
                break;
            case 3:
                mostrarPlaylist(&minhaPlaylist);
                break;
            case 4:
                proximaMusica(&minhaPlaylist);
                break;
            case 5:
                musicaAnterior(&minhaPlaylist);
                break;
            case 6:
                ordenarPorDuracao(&minhaPlaylist);
                break;
            case 0:
                printf("Saindo --> \n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
