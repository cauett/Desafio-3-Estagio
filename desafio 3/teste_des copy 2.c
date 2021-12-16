#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define BK 1000

struct Algoritmo 
{
    char nome;
    int count_comp;
    int count_mov;
    float tempo;

    struct Algoritmo *proximo;
};

struct Bucketss
{
    int qtd;
    int balde[BK];
};

void SacodeHeap(int m, int *lista1) 
{
    int z, i = 2;
    
    while (i <= m) 
    {
        if (i < m && lista1[i] < lista1[i + 1]) {
            i++;
        }
        if (lista1[i/2] >= lista1[i]) {
            break;
        }
        z = lista1[i / 2];
        lista1[i / 2] = lista1[i];
        lista1[i] = z;
        i *= 2;
    }
}

void inserirHeap(int m, int *lista1)  
{
    int i = m + 1;

    while (i > 1 && lista1[i / 2] < lista1[i]) 
    {
        int z = lista1[i / 2];

        lista1[i / 2] = lista1[i];
        lista1[i] = z;
        i = i / 2;
    }
}

void Heap(struct Algoritmo *sexto, int *lista1, int x) 
{
    FILE *Heap_Test;
    Heap_Test = fopen("C:\\Users\\cauet_ferreira\\Desktop\\heapSort.txt", "w");

    int i, help_hand, m, z,
        comp = 0, mov = 0;
    clock_t tempo_exe;

    tempo_exe = clock();
    for (m = 1; m < x; m++) {
        mov++;
        inserirHeap(m, lista1);
        comp++;
    }
    for (m = x; m > 1; m--) {
        mov++;
        z = lista1[1];
        lista1[1] = lista1[m];
        lista1[m] = z;
        SacodeHeap(m - 1, lista1);
    }
    tempo_exe = clock() - tempo_exe;

    sexto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    sexto -> count_comp = comp;
    sexto -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Heap_Test, "%d|", lista1[i]);
    }
    
    char teste[100] = "\n\nNome do Algoritmo: Heap Sort";

    fwrite(teste, 1, strlen(teste), Heap_Test);
    fprintf(Heap_Test, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            sexto -> count_comp, sexto -> count_mov, sexto -> tempo);

    sexto -> nome = teste;

    close(Heap_Test);
}
  
void Radix_counting(struct Algoritmo *quinto, int *lista1, int x) 
{
    FILE *Radix_counting;
    Radix_counting = fopen("C:\\Users\\cauet_ferreira\\Desktop\\radixCounting.txt", "w");

    int i, j = 1, *help_hand,
        maior = lista1[0],
        comp = 0, mov = 0;
    clock_t tempo_exe;

    help_hand = (int *) calloc(x, sizeof(int));
    
    tempo_exe = clock();
    for (i = 0; i < x; i++) {
        if (lista1[i] > maior) {
            maior = lista1[i];
            comp++;
        }
    }
    int count[maior + 1];

    for (i = 0; i <= maior; i++) {
        count[i] = 0;
        mov++;
    }
    for (i = 0; i < x; i++) {
        count[lista1[i]]++;          //estoca numeros
        mov++;
    }
    for (i = 1; i <= maior; i++) {
        count[i] = count[i] + count[i - 1];       //atualiza o contador
        mov++;
    }
    for (i = x - 1; i >= 0; i--) {
        help_hand[--count[lista1[i]]] = lista1[i];      //ordena tudo
        mov++;
    }
    for (i = 0; i < x; i++) {
        lista1[i] = help_hand[i];        //envia ordenado para o array original
        mov++;
    }
    tempo_exe = clock() - tempo_exe;
    free(help_hand);

    quinto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    quinto -> count_comp = comp;
    quinto -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Radix_counting, "%d|", lista1[i]);
    }
    
    char teste[100] = "\n\nNome do Algoritmo: Radix Sort -> Subalgoritmo: Counting";

    fwrite(teste, 1, strlen(teste), Radix_counting);
    fprintf(Radix_counting, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            quinto -> count_comp, quinto -> count_mov, quinto -> tempo);

    quinto -> nome = teste;

    close(Radix_counting);
}

void Radix_bucket(struct Algoritmo *quarto, int *lista1, int x) 
{
    FILE *Radix_bucket;
    Radix_bucket = fopen("C:\\Users\\cauet_ferreira\\Desktop\\radixBucket.txt", "w");

    int i, j = 1, *help_hand,
        maior = lista1[0],
        comp = 0, mov = 0;
    clock_t tempo_exe;

    help_hand = (int *) calloc(x, sizeof(int));
    
    tempo_exe = clock();
    for (i = 0; i < x; i++) {
        if (lista1[i] > maior) {
            maior = lista1[i];
            comp++;
        }
    }
    while (maior / j > 0) {
        int bucket[BK] = {0};

        for (i = 0; i < x; i++) {
            bucket[(lista1[i] / j) % BK]++;
            mov++;
        } 
        for (i = 1; i < BK; i++) {
            bucket[i] += bucket[i - 1];
            mov++;
        }
        for (i = x - 1; i >= 0; i--) {
            help_hand[--bucket[(lista1[i] / j) % BK]] = lista1[i];
            mov++;
        }
        for (i = 0; i < x; i++) {
            lista1[i] = help_hand[i];
            mov++;
        }
        j *= BK;
    }
    tempo_exe = clock() - tempo_exe;
    free(help_hand);

    quarto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    quarto -> count_comp = comp;
    quarto -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Radix_bucket, "%d|", lista1[i]);
    }
    
    char teste[100] = "\n\nNome do Algoritmo: Radix Sort -> Subalgoritmo: Bucket";

    fwrite(teste, 1, strlen(teste), Radix_bucket);
    fprintf(Radix_bucket, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            quarto -> count_comp, quarto -> count_mov, quarto -> tempo);

    quarto -> nome = teste;

    close(Radix_bucket);
}

void insertion(int *lista1, int x) 
{
    int i, j, aux;

    for (i = 1; i < x; i++) {
        aux = lista1[i];
        j = i - 1;
        while (j >= 0 && lista1[j] > aux) {
            lista1[j + 1] = lista1[j];
            j = j - 1;
        }
        lista1[j + 1] = aux;
    }
}

void Bucket(struct Algoritmo *terceiro, int *lista1, int x) 
{
    FILE *Bucket_Test;
    Bucket_Test = fopen("C:\\Users\\cauet_ferreira\\Desktop\\bucket.txt", "w");

    int i, j, maior, menor, numBaldes, count, 
        comp = 0, mov = 0;
    clock_t tempo_exe;
    struct Bucketss *xy;

    maior = menor = lista1[0]; 

    tempo_exe = clock();
    for (i = 1; i < x; i++) {
        if (lista1[i] > maior) { maior = lista1[i]; comp++;}
        if (lista1[i] < menor) { menor = lista1[i]; comp++;}
        mov++;
    }

    numBaldes = (maior - menor) / BK + 1;
    xy = (struct Bucketss *) malloc(numBaldes * sizeof(struct Bucketss));
    for (i = 0; i < numBaldes; i++) {
        xy[i].qtd = 0;
        mov++;
    }

    for (i = 0; i < x; i++) {
        count = (lista1[i] - menor) / BK;
        xy[count].balde[xy[count].qtd] = lista1[i];
        xy[count].qtd++;
        mov++;
    }

    count = 0;
    for (i = 0; i < numBaldes; i++) {
        insertion(xy[i].balde, xy[i].qtd);
        for (j = 0; j < xy[i].qtd; j++) {
            lista1[count] = xy[i].balde[j];
            count++;
        }
        mov++;
    }
    tempo_exe = clock() - tempo_exe;

    terceiro -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    terceiro -> count_comp = comp;
    terceiro -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Bucket_Test, "%d|", lista1[i]);
    }
    
    char teste[100] = "\n\nNome do Algoritmo: Bucket Sort";

    fwrite(teste, 1, strlen(teste), Bucket_Test);
    fprintf(Bucket_Test, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            terceiro -> count_comp, terceiro -> count_mov, terceiro -> tempo);

    terceiro -> nome = teste;

    free(xy);
    close(Bucket_Test);
}

void Counting(struct Algoritmo *segundo, int *lista1, int x) 
{
    FILE *Counting_Test;
    Counting_Test = fopen("C:\\Users\\cauet_ferreira\\Desktop\\counting.txt", "w");

    int i, max = lista1[0],
        help_hand[x], comp = 0, mov = 0;
    clock_t tempo_exe;
    
    tempo_exe = clock();
    for (i = 1; i < x; i++) 
    {
        if (lista1[i] > max)         //encontra o maior elemento
        {
            max = lista1[i];
            comp++;
            mov++;
        }
    }

    int count[max + 1];
    
    for (i = 0; i <= max; i++)       //inicializa com zeros
    {
        count[i] = 0;
        mov++;
    }
    for (i = 0; i < x; i++) 
    {
        count[lista1[i]]++;          //estoca numeros
        mov++;
    }
    for (i = 1; i <= max; i++) 
    {
        count[i] = count[i] + count[i - 1];       //atualiza o contador
        mov++;
    }
    for (i = x - 1; i >= 0; i--) 
    {
        help_hand[--count[lista1[i]]] = lista1[i];      //ordena tudo
        mov++;
    }
    for (i = 0; i < x; i++) 
    {
        lista1[i] = help_hand[i];        //envia ordenado para o array original
        mov++;
    }
    tempo_exe = clock() - tempo_exe;

    segundo -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    segundo -> count_comp = comp;
    segundo -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Counting_Test, "%d|", lista1[i]);
    }

    char teste[100] = "\n\nNome do Algoritmo: Counting Sort";

    fwrite(teste, 1, strlen(teste), Counting_Test);
    fprintf(Counting_Test, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            segundo -> count_comp, segundo -> count_mov, segundo -> tempo);

    segundo -> nome = teste;

    close(Counting_Test);
}

void Cocktail(struct Algoritmo *primeiro, int *lista1, int x)
{
    FILE *Cocktail_Test;
    Cocktail_Test = fopen("C:\\Users\\cauet_ferreira\\Desktop\\cocktail.txt", "w");

    int i, help_hand, tam = x - 1, 
        verif = 0, verif_back = 0,
        comp = 0, mov = 0;
    clock_t tempo_exe;

    tempo_exe = clock();
    while(verif == 0 && verif_back < tam) 
    {
        verif_back = 1;

        for (i = 0; i < tam; i++) 
        {
            if (lista1[i] > lista1[i + 1])          //analisa da direita
            {
                help_hand = lista1[i];
                lista1[i] = lista1[i + 1];
                lista1[i + 1] = help_hand;

                verif_back = 0;

                comp++;
            }
            mov++;
        }

        tam -= 1;
    
        for (i = tam; i > 0; i--) 
        {
            if (lista1[i] < lista1[i - 1])        //analisa da esquerda
            {
                help_hand = lista1[i];
                lista1[i] = lista1[i - 1];
                lista1[i - 1] = help_hand;

                verif_back = 0;

                comp++;
            }
            mov++;
        }
    }
    tempo_exe = clock() - tempo_exe;

    primeiro -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    primeiro -> count_comp = comp;
    primeiro -> count_mov = mov;

    int count = 0;

    for (i = 0; i < x; i++) {
        fprintf(Cocktail_Test, "%d|", lista1[i]);
        count = count + 1;
    } 
    printf("\nNums: %d\n", count);
    
    char teste[100] = "\n\nNome do Algoritmo: Cocktail Sort";

    fwrite(teste, 1, strlen(teste), Cocktail_Test);
    fprintf(Cocktail_Test, "\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            primeiro -> count_comp, primeiro -> count_mov, primeiro -> tempo);

    primeiro -> nome = teste;

    close(Cocktail_Test);
}

int main() 
{
    int i, x, choice;
    printf("Qual o tamanho do vetor? \n");
    scanf("%d", &x);             //recebe tamanho do vetor
    system("cls");

    int *lista1[x];

    srand(time(NULL));
    for (i = 0; i < x; i++) {
        lista1[i] = rand() % x * x/RAND_MAX;          //randomiza elementos
    }

    while (choice != 0) {
        printf("\n1 - Cocktail Sort\n"
                "2 - Counting Sort\n"
                "3 - Bucket Sort\n"
                "Radix Sort ->"
                "\n\t4 - Com bucket"
                "\n\t5 - Com counting\n"
                "6 - Heap Sort\n"
                "\n0 - Sair do programa\n");
        printf("\nEscolha uma opcao: \n");
        scanf("%d", &choice);
        system("cls");

        if (choice == 1) {
            struct Algoritmo *primeiro = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));   //nó
            Cocktail(primeiro, lista1, x);              //chama função
            printf("\nOrdenado em Cocktail!\n");     //notifica se rodou
            free(primeiro);    //libera a memória alocada
        }
        else if (choice == 2) {
            struct Algoritmo *segundo = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
            Counting(segundo, lista1, x);
            printf("\nOrdenado em Counting!\n");
            free(segundo);
        }
        else if (choice == 3) {
            struct Algoritmo *terceiro = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
            Bucket(terceiro, lista1, x);
            printf("\nOrdenado em Bucket!\n");
            free(terceiro);
        }
        else if (choice == 4) {
            struct Algoritmo *quarto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
            Radix_bucket(quarto, lista1, x);
            printf("\nOrdenado em Radix -> Subalgoritmo: Bucket!\n");
            free(quarto);
        }
        else if (choice == 5) {
            struct Algoritmo *quinto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
            Radix_counting(quinto, lista1, x);
            printf("\nOrdenado em Radix -> Subalgoritmo: Counting!\n");
            free(quinto);
        }
        else if (choice == 6) {
            struct Algoritmo *sexto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
            Heap(sexto, lista1, x);
            printf("\nOrdenado em Heap!\n");
            free(sexto);
        }
        else if (choice == 7) {
            for (i = 0; i < x; i++) {
                printf("%d|", lista1[i]);
            }
        }
    }

    return 0;
}
