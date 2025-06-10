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

// Função para verificar se a posição do navio reto é válida
bool posicaoRetoValida(int linha, int coluna, bool horizontal, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
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

// Função para verificar se a posição do navio diagonal é válida
bool posicaoDiagonalValida(int linha, int coluna, bool diagonalPrincipal, int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Verifica se o navio cabe no tabuleiro
    if (diagonalPrincipal) {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return false;
    }
    
    // Verifica se não há sobreposição com outros navios
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (diagonalPrincipal) {
            if (tabuleiro[linha + i][coluna + i] != 0) return false;
        } else {
            if (tabuleiro[linha + i][coluna - i] != 0) return false;
        }
    }
    
    return true;
}

// Função para posicionar um navio reto no tabuleiro
void posicionarNavioReto(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool horizontal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (horizontal) {
            tabuleiro[linha][coluna + i] = 3;
        } else {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Função para posicionar um navio diagonal no tabuleiro
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool diagonalPrincipal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (diagonalPrincipal) {
            tabuleiro[linha + i][coluna + i] = 3;
        } else {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // %2d para alinhar os números
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa o tabuleiro com água (0s)
    inicializarTabuleiro(tabuleiro);
    
    // Define as coordenadas dos navios (fixas no código)
    // Navios retos
    int linhaNavio1 = 2, colunaNavio1 = 3;  // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7;  // Navio vertical
    
    // Navios diagonais
    int linhaNavio3 = 1, colunaNavio3 = 1;  // Diagonal principal (para baixo e direita)
    int linhaNavio4 = 0, colunaNavio4 = 8;  // Diagonal secundária (para baixo e esquerda)
    
    // Posiciona os navios retos (com validação)
    if (posicaoRetoValida(linhaNavio1, colunaNavio1, true, tabuleiro)) {
        posicionarNavioReto(tabuleiro, linhaNavio1, colunaNavio1, true);
    } else {
        printf("Posição inválida para o navio horizontal!\n");
        return 1;
    }
    
    if (posicaoRetoValida(linhaNavio2, colunaNavio2, false, tabuleiro)) {
        posicionarNavioReto(tabuleiro, linhaNavio2, colunaNavio2, false);
    } else {
        printf("Posição inválida para o navio vertical!\n");
        return 1;
    }
    
    // Posiciona os navios diagonais (com validação)
    if (posicaoDiagonalValida(linhaNavio3, colunaNavio3, true, tabuleiro)) {
        posicionarNavioDiagonal(tabuleiro, linhaNavio3, colunaNavio3, true);
    } else {
        printf("Posição inválida para o navio diagonal principal!\n");
        return 1;
    }
    
    if (posicaoDiagonalValida(linhaNavio4, colunaNavio4, false, tabuleiro)) {
        posicionarNavioDiagonal(tabuleiro, linhaNavio4, colunaNavio4, false);
    } else {
        printf("Posição inválida para o navio diagonal secundário!\n");
        return 1;
    }
    
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
