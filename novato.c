#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para inicializar o tabuleiro com 0s (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se a posição do navio é válida
bool posicaoValida(int linha, int coluna, bool horizontal, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Verifica se o navio cabe no tabuleiro
    if (horizontal) {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    }
    
    // Verifica se não há sobreposição com outros navios
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (horizontal) {
            if (tabuleiro[linha][coluna + i] != 0) return false;
        } else {
            if (tabuleiro[linha + i][coluna] != 0) return false;
        }
    }
    
    return true;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool horizontal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (horizontal) {
            tabuleiro[linha][coluna + i] = 3;
        } else {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água (0s)
    inicializarTabuleiro(tabuleiro);
    
    // Define as coordenadas dos navios (poderiam ser recebidas como input)
    int linhaNavio1 = 2, colunaNavio1 = 3;  // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7;  // Navio vertical
    
    // Posiciona o navio horizontal (valida antes de posicionar)
    if (posicaoValida(linhaNavio1, colunaNavio1, true, tabuleiro)) {
        posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, true);
    } else {
        printf("Posição inválida para o navio horizontal!\n");
        return 1;
    }
    
    // Posiciona o navio vertical (valida antes de posicionar)
    if (posicaoValida(linhaNavio2, colunaNavio2, false, tabuleiro)) {
        posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, false);
    } else {
        printf("Posição inválida para o navio vertical!\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
