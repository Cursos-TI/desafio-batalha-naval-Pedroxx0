#include <stdio.h>

int main() {

    int tabuleiro[10][10];
    char linha[10] = {'A','B','C','D','E','F','G','H','I','J'};

    // Inicializa o tabuleiro com água (0)
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Posiciona navio horizontal (linha C, colunas 5 a 7)
    for(int j = 4; j < 7; j++) {
        tabuleiro[2][j] = 3;
    }

    // Posiciona navio vertical (coluna 8, linhas F a H)
    for(int i = 5; i < 8; i++) {
        tabuleiro[i][7] = 3;
    }

    // Imprime cabeçalho das colunas
    printf("   ");
    for(int j = 0; j < 10; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    // Imprime o tabuleiro com letras nas linhas
    for(int i = 0; i < 10; i++) {
        printf("%c  ", linha[i]);
        for(int j = 0; j < 10; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}