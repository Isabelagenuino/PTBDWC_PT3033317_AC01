#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/* Programa que recebe um tamanho de vetor como parâmetro, aloca
memória para este vetor e preenche-o com números inteiros crescentes,
com intervaloes pseudoaletórios.
Mede o tempo para gerar o vetor e o imprime.
Realiza buscas sequencial e binária por NCHAVES valores no vetor e mede o tempo de cada busca.
Imprime os tempos de busca.
Teste com vários tamanhos até obter tempos entre um e dez segundos para a geração do vetor.
*/

int compara_int(const void *i1, const void *i2) { // Compara dois inteiros
// Retorna zero se iguais, negativo se *i1 < *i2 e positivo se *i1 > *i2
    return *(int *)i1 - *(int *)i2;
}

#define NCHAVES 5

int busca_sequencial(unsigned int *vetor, size_t n, unsigned int chave) {
    for (size_t i = 0; i < n; i++) {
        if (vetor[i] == chave) {
            return i; // Retorna o índice se encontrado
        }
    }
    return -1; // Retorna -1 se não encontrado
}

int main(int argc, char *argv[]) {
    clock_t inicio, fim;
    double segs_seq, segs_bin;
    if (argc <= 1) {
        printf("Passe como parâmetro o numero de elementos do vetor\n");
        exit(1);
    }
    size_t n = strtoll(argv[1], 0, 10);
    unsigned int *inteiros = malloc(n * sizeof(unsigned int));
    printf("Criando vetor de %llu (%g) inteiros em %llx\n", n, (double)n, inteiros);
    int interv_max = 20;
    if(argc > 2) // O segundo parâmetro é o intervalo máximo + 1
        interv_max = atoi(argv[2]);
    printf("Intervalo ate' %d\n", interv_max);
    size_t i=0;
    inicio = clock(); // Marca o tempo de início    srand(1); // Reinicia a sequência, para ter sempre o mesmo vetor
    inteiros[0] = rand() % interv_max;
    for (i = 1; i < n; i+=1) { // Cria vetor de inteiros com intervalo pseudoaleatório
        inteiros[i] = inteiros[i-1] + rand() % interv_max;
        if(inteiros[i] < inteiros[i-1]) {
            printf("Estourou inteiro maximo. Vetor nao ordenado.;\n");
            exit(1);
        }
    }
    fim = clock(); // Marca o tempo final
    // Calcula o tempo decorrido em segundos
    double segs_geracao= ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo para gerar o vetor: %g segundos\n", segs_geracao);

    // Busca Sequencial
    inicio = clock();
    for (int j = 0; j < NCHAVES; j++) {
        unsigned int chave_busca_seq = inteiros[rand() % n]; // Escolhe chaves aleatórias dentro do vetor
        busca_sequencial(inteiros, n, chave_busca_seq);
    }
    fim = clock();
    segs_seq = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo para %d buscas sequenciais: %g segundos\n", NCHAVES, segs_seq);

    // Busca Binária
    inicio = clock();
    for (int j = 0; j < NCHAVES; j++) {
        unsigned int chave_busca_bin = inteiros[rand() % n]; // Escolhe chaves aleatórias dentro do vetor
        bsearch(&chave_busca_bin, inteiros, n, sizeof(unsigned int), compara_int);
    }
    fim = clock();
    segs_bin = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo para %d buscas binárias: %g segundos\n", NCHAVES, segs_bin);

    free(inteiros); // Libera a memória alocada
    return 0;
}
/* int rand(void) gera uma sequência pseudoaleatória de números inteiros.
O maior valor possível é RAND_MAX, que no gcc para Windows é 32767.
Se quiser um valor de zero a max, use rand() % (max+1)
Chame void srand(int semente), antes da primeira chamada de rand(), para que
ela gere outras sequências.
Para gerar um valor mais aleatório, use uma semente extraída da hora do
sistema, usando seus campos menos significativos.
Não use rand() para aplicações que exijam números realmente aleatórios,
como, por exemplo, criptografia. Há hardwares específicos para isto.
*/
