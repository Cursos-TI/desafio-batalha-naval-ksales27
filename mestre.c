#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Funções para inicialização e posicionamento (mantidas do código anterior)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// [Restante das funções de posicionamento de navios...]

// Funções para criar matrizes de habilidades
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cone: linhas inferiores têm mais colunas ativadas
            if (j >= (TAMANHO_HABILIDADE/2 - i/2) && 
                j <= (TAMANHO_HABILIDADE/2 + i/2)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz: linha central ou coluna central
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Octaedro: formato de losango
            int distVertical = abs(i - centro);
            int distHorizontal = abs(j - centro);
            if (distVertical + distHorizontal <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                      int linha, int coluna) {
    int offset = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tabLinha = linha - offset + i;
            int tabColuna = coluna - offset + j;
            
            // Verifica se está dentro do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAMANHO_TABULEIRO &&
                tabColuna >= 0 && tabColuna < TAMANHO_TABULEIRO) {
                
                // Aplica a habilidade (sem sobrescrever navios)
                if (habilidade[i][j] == 1 && tabuleiro[tabLinha][tabColuna] != NAVIO) {
                    tabuleiro[tabLinha][tabColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval com Habilidades:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // [Código para posicionar navios...]
    
    // Matrizes para habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Criar habilidades
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);      // Cone no centro
    aplicarHabilidade(tabuleiro, cruz, 2, 7);      // Cruz perto da borda
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);  // Octaedro em outra posição
    
    // Exibir tabuleiro com navios e habilidades
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
