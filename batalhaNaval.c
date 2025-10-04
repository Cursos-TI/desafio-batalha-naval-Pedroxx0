#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro principal (10x10)
#define TAM_HAB 5    // Tamanho das matrizes de habilidades (5x5)

// Função que aplica uma habilidade ao tabuleiro, sobrepondo a matriz de habilidade
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origem_i, int origem_j) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Calcula a posição real no tabuleiro com base na origem
            int linha = origem_i - TAM_HAB / 2 + i;
            int coluna = origem_j - TAM_HAB / 2 + j;

            // Verifica se está dentro dos limites do tabuleiro
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                // Se a célula da habilidade for 1 e o tabuleiro tiver água (0), marca como área afetada (5)
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

// Função que cria uma matriz em forma de cone
void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Preenche com 1 formando um cone com vértice no topo
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função que cria uma matriz em forma de cruz
void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Preenche linha e coluna centrais com 1
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função que cria uma matriz em forma de octaedro (losango)
void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Preenche com 1 formando um losango centrado
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função que imprime o tabuleiro com legendas visuais
void imprimirTabuleiro(int tabuleiro[TAM][TAM], char linha[TAM]) {
    // Imprime cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    // Imprime cada linha com a letra correspondente
    for (int i = 0; i < TAM; i++) {
        printf("%c  ", linha[i]);
        for (int j = 0; j < TAM; j++) {
            // Exibe os símbolos conforme o conteúdo da célula
            if (tabuleiro[i][j] == 0)
                printf(" ~ ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf(" N ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf(" * ");  // Área afetada por habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];  // Tabuleiro principal
    char linha[TAM] = {'A','B','C','D','E','F','G','H','I','J'};  // Rótulos das linhas

    // Inicializa o tabuleiro com água (valor 0)
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;

    // Posiciona os navios no tabuleiro (valor 3)
    for (int j = 4; j < 7; j++) tabuleiro[2][j] = 3;         // Navio horizontal em C5 a C7
    for (int i = 5; i < 8; i++) tabuleiro[i][7] = 3;         // Navio vertical em F8 a H8
    for (int i = 0; i < 5; i++) tabuleiro[i][i] = 3;         // Navio diagonal principal A1 a E5
    for (int i = 0; i < 5; i++) tabuleiro[i][9 - i] = 3;     // Navio diagonal secundária A10 a E6

    // Cria as matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 6, 2);      // Aplica cone com origem em G3
    aplicarHabilidade(tabuleiro, cruz, 4, 4);      // Aplica cruz com origem em E5
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);  // Aplica octaedro com origem em H8

    // Exibe o tabuleiro final com navios e áreas afetadas
    imprimirTabuleiro(tabuleiro, linha);

    return 0;
}

