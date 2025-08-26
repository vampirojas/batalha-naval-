#include <stdio.h>

#define TAM_TAB 10       // Tamanho do tabuleiro
#define TAM_HAB 5        // Tamanho das matrizes de habilidade

// Função para exibir o tabuleiro
void exibirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    for(int i = 0; i < TAM_TAB; i++) {
        for(int j = 0; j < TAM_TAB; j++) {
            if(tab[i][j] == 0) printf("~ ");  // Água
            else if(tab[i][j] == 3) printf("N "); // Navio
            else if(tab[i][j] == 5) printf("* "); // Área afetada pela habilidade
        }
        printf("\n");
    }
}

// Função para criar a matriz de habilidade em cone
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for(int i = 0; i < TAM_HAB; i++) {
        for(int j = 0; j < TAM_HAB; j++) {
            // A condição cria a forma de cone com topo na linha 0
            if(j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para criar a matriz de habilidade em cruz
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for(int i = 0; i < TAM_HAB; i++) {
        for(int j = 0; j < TAM_HAB; j++) {
            if(i == TAM_HAB/2 || j == TAM_HAB/2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para criar a matriz de habilidade em octaedro (losango)
void criarOctaedro(int oct[TAM_HAB][TAM_HAB]) {
    for(int i = 0; i < TAM_HAB; i++) {
        for(int j = 0; j < TAM_HAB; j++) {
            if(j >= (TAM_HAB/2 - i) && j <= (TAM_HAB/2 + i) && i <= TAM_HAB/2)
                oct[i][j] = 1; // Parte superior
            else if(j >= (i - TAM_HAB/2) && j <= (3*TAM_HAB/2 - i -1) && i > TAM_HAB/2)
                oct[i][j] = 1; // Parte inferior
            else
                oct[i][j] = 0;
        }
    }
}

// Função para sobrepor a habilidade no tabuleiro
void aplicarHabilidade(int tab[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int linOrigem, int colOrigem) {
    int meio = TAM_HAB / 2;
    for(int i = 0; i < TAM_HAB; i++) {
        for(int j = 0; j < TAM_HAB; j++) {
            int tabI = linOrigem - meio + i;
            int tabJ = colOrigem - meio + j;
            // Garante que a sobreposição esteja dentro do tabuleiro
            if(tabI >= 0 && tabI < TAM_TAB && tabJ >= 0 && tabJ < TAM_TAB) {
                if(hab[i][j] == 1 && tab[tabI][tabJ] != 3) {
                    tab[tabI][tabJ] = 5; // Marca área afetada
                }
            }
        }
    }
}

int main() {
    int tab[TAM_TAB][TAM_TAB] = {0}; // Inicializa tabuleiro com água
    
    // Exemplo de navios
    tab[2][2] = 3;
    tab[5][5] = 3;

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Criação das habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades em pontos de origem definidos
    aplicarHabilidade(tab, cone, 1, 4);      // Cone no topo central
    aplicarHabilidade(tab, cruz, 6, 2);      // Cruz no meio esquerdo
    aplicarHabilidade(tab, octaedro, 7, 7);  // Octaedro no canto inferior direito

    // Exibe tabuleiro final
    exibirTabuleiro(tab);

    return 0;
}
