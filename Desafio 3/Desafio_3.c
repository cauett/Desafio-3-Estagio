#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define BK 1000

struct Algoritmo 
{
    char nome[100];
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

void listar(struct Algoritmo *no) 
{
    while (no != NULL) {
        printf("Nome: %s |Comparacoes: %d |Movimentos: %d |Tempo: %.2f |\n\n", no -> nome, no -> count_comp, no -> count_mov, no -> tempo);
        no = no -> proximo;
    }
}

void Comparacoes(struct Algoritmo *primeiro, struct Algoritmo *segundo, struct Algoritmo *terceiro,
                 struct Algoritmo *quarto, struct Algoritmo *quinto, struct Algoritmo *sexto)
{
    FILE *Best;
    Best = fopen(/*local do arquivo*/, "w");
    
    int r = primeiro -> count_comp, b = segundo -> count_comp, d = terceiro -> count_comp,
        x = quarto -> count_comp, y = quinto -> count_comp, z = sexto -> count_comp;
        
        //Comparação
        if (r < b && r < d && r < x && r < y && r < z) {
            fprintf (Best, "Cocktail é o melhor em comparações\n");
        }
        else if (b < r && b < d && b < x && b < y && b < z) {
            fprintf (Best, "Counting é o melhor em comparações\n");
        }
        else if (d < r && d < b && d < x && d < y && d < z) {
            fprintf (Best, "Bucket é o melhor em comparações\n");
        }
        else if (x < r && x < b && x < d && x < y && x < z) {
            fprintf (Best, "Radix_Bucket é o melhor em comparações\n");
        }
        else if (y < r && y < b && y < d && y < x && y < z) {
            fprintf (Best, "Radix_Counting é o melhor em comparações\n");
        }
        else if (z < r && z < b && z < d && z < x && z < y) {
            fprintf (Best, "Heap é o melhor em comparações\n");
        }
        
    r = primeiro -> count_mov, b = segundo -> count_mov, d = terceiro -> count_mov,
    x = quarto -> count_mov, y = quinto -> count_mov, z = sexto -> count_mov;

        //Movimentação
        if (r < b && r < d && r < x && r < y && r < z) {
            fprintf (Best, "Cocktail é o melhor em movimentação\n");
        }
        else if (b < r && b < d && b < x && b < y && b < z) {
            fprintf (Best, "Counting é o melhor em movimentação\n");
        }
        else if (d < r && d < b && d < x && d < y && d < z) {
            fprintf (Best, "Bucket é o melhor em movimentação\n");
        }
        else if (x < r && x < b && x < d && x < y && x < z) {
            fprintf (Best, "Radix_Bucket é o melhor em movimentação\n");
        }
        else if (y < r && y < b && y < d && y < x && y < z) {
            fprintf (Best, "Radix_Counting é o melhor em movimentação\n");
        }
        else if (z < r && z < b && z < d && z < x && z < y) {
            fprintf (Best, "Heap é o melhor em movimentação\n");
        }

    r = primeiro -> tempo, b = segundo -> tempo, d = terceiro -> tempo,
    x = quarto -> tempo, y = quinto -> tempo, z = sexto -> tempo;
        
        //Tempo de execução
        if (r < b && r < d && r < x && r < y && r < z) {
            fprintf (Best, "Cocktail é o mais rápido\n");
        }
        else if (b < r && b < d && b < x && b < y && b < z) {
            fprintf (Best, "Counting é o mais rápido\n");
        }
        else if (d < r && d < b && d < x && d < y && d < z) {
            fprintf (Best, "Bucket é o mais rápido\n");
        }
        else if (x < r && x < b && x < d && x < y && x < z) {
            fprintf (Best, "Radix_Bucket é o mais rápido\n");
        }
        else if (y < r && y < b && y < d && y < x && y < z) {
            fprintf (Best, "Radix_Counting é o mais rápido\n");
        }
        else if (z < r && z < b && z < d && z < x && z < y) {
            fprintf (Best, "Heap é o mais rápido\n");
        }
        
    close(Best);
}

void SacodeHeap(int m, int *lista7) 
{
    int z, i = 2;
    
    while (i <= m) 
    {
        if (i < m && lista7[i] < lista7[i + 1]) {
            i++;
        }
        if (lista7[i / 2] >= lista7[i]) {
            break;
        }
        z = lista7[i / 2];
        lista7[i / 2] = lista7[i];
        lista7[i] = z;
        i *= 2;
    }
}

void inserirHeap(int m, int *lista7)  
{
    int i = m + 1;

    while (i > 1 && lista7[i / 2] < lista7[i]) 
    {
        int z = lista7[i / 2];

        lista7[i / 2] = lista7[i];
        lista7[i] = z;
        i = i / 2;
    }
}

void Heap(struct Algoritmo *sexto, int *lista1, int x) 
{
    FILE *Heap_Test;
    Heap_Test = fopen(/*local do arquivo*/, "w");

    int i, help_hand, m, z, lista7[x],
        comp = 0, mov = 0;
    clock_t tempo_exe;

    for (i = 0; i < x; i++) {
        lista7[i] = lista1[i];
    }

    tempo_exe = clock();
    for (m = 1; m < x; m++) {
        mov++;
        inserirHeap(m, lista7);
    }
    for (m = x; m > 1; m--) {
        mov++;
        z = lista7[1];
        lista7[1] = lista7[m];
        lista7[m] = z;
        SacodeHeap(m - 1, lista7);
        comp++;
    }
    tempo_exe = clock() - tempo_exe;

    sexto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    sexto -> count_comp = comp;
    sexto -> count_mov = mov;
    
    if (lista7[0] > 10) {
        lista7[0] = NULL;
    }
    for (i = 0; i < x; i++) {
        fprintf(Heap_Test, "%d|", lista7[i]);
    }
    
    strcpy(sexto -> nome, "Heap Sort");
    fprintf(Heap_Test, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            sexto -> nome, sexto -> count_comp, sexto -> count_mov, sexto -> tempo);

    close(Heap_Test);
}
  
void Radix_counting(struct Algoritmo *quinto, int *lista1, int x) 
{
    FILE *Radix_counting;
    Radix_counting = fopen(/*local do arquivo*/, "w");

    int i, j = 1, *help_hand, lista6[x],
        maior = lista6[0],
        comp = 0, mov = 0;
    clock_t tempo_exe;

    for (i = 0; i < x; i++) {
        lista6[i] = lista1[i];
    }

    help_hand = (int *) calloc(x, sizeof(int));
    
    tempo_exe = clock();
    for (i = 0; i < x; i++) {
        if (lista6[i] > maior) {
            maior = lista6[i];
            comp++;
        }
    }
    int count[maior + 1];

    for (i = 0; i <= maior; i++) {
        count[i] = 0;
        mov++;
    }
    for (i = 0; i < x; i++) {
        count[lista6[i]]++;          //estoca numeros
        mov++;
    }
    for (i = 1; i <= maior; i++) {
        count[i] = count[i] + count[i - 1];       //atualiza o contador
        mov++;
    }
    for (i = x - 1; i >= 0; i--) {
        help_hand[--count[lista6[i]]] = lista6[i];      //ordena tudo
        mov++;
    }
    for (i = 0; i < x; i++) {
        lista6[i] = help_hand[i];        //envia ordenado para o array original
        mov++;
    }
    tempo_exe = clock() - tempo_exe;
    free(help_hand);

    quinto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    quinto -> count_comp = comp;
    quinto -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Radix_counting, "%d|", lista6[i]);
    }
    
    strcpy(quinto -> nome, "Radix Sort -> Subalgoritmo: Counting");
    fprintf(Radix_counting, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            quinto -> nome, quinto -> count_comp, quinto -> count_mov, quinto -> tempo);

    close(Radix_counting);
}

void Radix_bucket(struct Algoritmo *quarto, int *lista1, int x) 
{
    FILE *Radix_bucket;
    Radix_bucket = fopen(/*local do arquivo*/, "w");

    int i, j = 1, *help_hand, lista5[x],
        maior = lista5[0],
        comp = 0, mov = 0;
    clock_t tempo_exe;

    for (i = 0; i < x; i++) {
        lista5[i] = lista1[i];
    }

    help_hand = (int *) calloc(x, sizeof(int));
    
    tempo_exe = clock();
    for (i = 0; i < x; i++) {
        if (lista5[i] > maior) {
            maior = lista5[i];
            comp++;
        }
    }
    while (maior / j > 0) {
        int bucket[BK] = {0};

        for (i = 0; i < x; i++) {
            bucket[(lista5[i] / j) % BK]++;
            mov++;
        } 
        for (i = 1; i < BK; i++) {
            bucket[i] += bucket[i - 1];
            mov++;
        }
        for (i = x - 1; i >= 0; i--) {
            help_hand[--bucket[(lista5[i] / j) % BK]] = lista5[i];
            mov++;
        }
        for (i = 0; i < x; i++) {
            lista5[i] = help_hand[i];
            mov++;
        }
        comp++;
        j *= BK;
    }
    tempo_exe = clock() - tempo_exe;
    free(help_hand);

    quarto -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    quarto -> count_comp = comp;
    quarto -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Radix_bucket, "%d|", lista5[i]);
    }
    
    strcpy(quarto -> nome, "Radix Sort -> Subalgoritmo: Bucket");
    fprintf(Radix_bucket, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            quarto -> nome, quarto -> count_comp, quarto -> count_mov, quarto -> tempo);

    close(Radix_bucket);
}

void insertion(int *lista4, int x) 
{
    int i, j, aux;

    for (i = 1; i < x; i++) {
        aux = lista4[i];
        j = i - 1;
        while (j >= 0 && lista4[j] > aux) {
            lista4[j + 1] = lista4[j];
            j = j - 1;
        }
        lista4[j + 1] = aux;
    }
}

void Bucket(struct Algoritmo *terceiro, int *lista1, int x) 
{
    FILE *Bucket_Test;
    Bucket_Test = fopen(/*local do arquivo*/, "w");

    int i, j, k, lista4[x], 
        comp = 0, mov = 0;
    clock_t tempo_exe;
    struct Bucketss *xy;
    xy = malloc(x * sizeof(struct Bucketss));    
    
    for (i = 0; i < x; i++) {
        lista4[i] = lista1[i];
    }
    
    tempo_exe = clock();
    for (i = 0; i < x; i++) {
        xy[i].qtd = 0;
    }
    for (i = 0; i < x; i++) {
        j = (x) - 1;
        while(1) {
            if (j < 0) { break; }
            if (lista4[i] >= j * 10) { 
                xy[j].balde[xy[j].qtd] = lista4[i];
                (xy[j].qtd)++;
                mov++;
                comp++;
                break;
            }
            j--;
        }
    }
    for (i = 0; i < x; i++) {
        if (xy[i].qtd) { insertion(xy[i].balde, xy[i].qtd); 
                        comp++;}
    }
    i = 0;
    
    for (j = 0; j < x; j++) {
        for (k = 0; k < xy[j].qtd; k++) {
            lista4[i] = xy[j].balde[k];
            mov++;
            i++;
        }
    }
    tempo_exe = clock() - tempo_exe;

    terceiro -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    terceiro -> count_comp = comp;
    terceiro -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Bucket_Test, "%d|", lista4[i]);
    }
    
    strcpy(terceiro -> nome, "Bucket Sort");
    fprintf(Bucket_Test, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            terceiro -> nome, terceiro -> count_comp, terceiro -> count_mov, terceiro -> tempo);

    free(xy);
    close(Bucket_Test);
}

void Counting(struct Algoritmo *segundo, int *lista1, int x) 
{
    FILE *Counting_Test;
    Counting_Test = fopen(/*local do arquivo*/, "w");

    int i, max = lista1[0],
        help_hand[x], comp = 0, mov = 0, lista3[x];
    clock_t tempo_exe;

    for (i = 0; i < x; i++) {
        lista3[i] = lista1[i];
    }
    
    tempo_exe = clock();
    for (i = 1; i < x; i++) 
    {
        if (lista3[i] > max)         //encontra o maior elemento
        {
            max = lista3[i];
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
        count[lista3[i]]++;          //estoca numeros
        mov++;
    }
    for (i = 1; i <= max; i++) 
    {
        count[i] = count[i] + count[i - 1];       //atualiza o contador
    }
    for (i = x - 1; i >= 0; i--) 
    {
        help_hand[--count[lista3[i]]] = lista3[i];      //ordena tudo
        mov++;
    }
    for (i = 0; i < x; i++) 
    {
        lista3[i] = help_hand[i];        //envia ordenado para o array original
    }
    tempo_exe = clock() - tempo_exe;

    segundo -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    segundo -> count_comp = comp;
    segundo -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Counting_Test, "%d|", lista3[i]);
    }

    strcpy(segundo -> nome, "Counting Sort");
    fprintf(Counting_Test, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            segundo -> nome, segundo -> count_comp, segundo -> count_mov, segundo -> tempo);

    close(Counting_Test);
}

void Cocktail(struct Algoritmo *primeiro, int *lista1, int x)
{
    FILE *Cocktail_Test;
    Cocktail_Test = fopen(/*local do arquivo*/, "w");

    int i, help_hand, tam = x - 1, lista2[x],
        verif = 0, verif_back = 0,
        comp = 0, mov = 0;
    clock_t tempo_exe;

    for (i = 0; i < x; i++) {
        lista2[i] = lista1[i];
    }

    tempo_exe = clock();
    while(verif == 0 && verif_back < tam) 
    {
        verif_back = 1;

        for (i = 0; i < tam; i++) 
        {
            if (lista2[i] > lista2[i + 1])          //analisa da direita
            {
                help_hand = lista2[i];
                lista2[i] = lista2[i + 1];
                lista2[i + 1] = help_hand;

                verif_back = 0;
                comp++;
            }
        }
        tam -= 1;
    
        for (i = tam; i > 0; i--) 
        {
            if (lista2[i] < lista2[i - 1])        //analisa da esquerda
            {
                help_hand = lista2[i];
                lista2[i] = lista2[i - 1];
                lista2[i - 1] = help_hand;

                verif_back = 0;
                comp++;
            }
        }
        mov++;
    }
    tempo_exe = clock() - tempo_exe;

    primeiro -> tempo = ((double)tempo_exe)/(CLOCKS_PER_SEC/1000);
    primeiro -> count_comp = comp;
    primeiro -> count_mov = mov;

    for (i = 0; i < x; i++) {
        fprintf(Cocktail_Test, "%d|", lista2[i]);
    } 

    strcpy(primeiro -> nome, "Cocktail Sort");
    fprintf(Cocktail_Test, "\n\nNome: %s\nContador de Comparacoes: %d"
            "\nContador de Movimentos: %d\nTempo de Execucao em ms: %f", 
            primeiro -> nome, primeiro -> count_comp, primeiro -> count_mov, primeiro -> tempo);

    close(Cocktail_Test);
}

int main() 
{
    struct Algoritmo *primeiro = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));   //nós
    struct Algoritmo *segundo = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
    struct Algoritmo *terceiro = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
    struct Algoritmo *quarto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
    struct Algoritmo *quinto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));
    struct Algoritmo *sexto = (struct Algoritmo*) malloc(sizeof(struct Algoritmo));

    int i, x, choice;
    printf("Qual o tamanho do vetor? \n");
    scanf("%d", &x);             //recebe tamanho do vetor
    system("cls");

    int *lista1[x];

    srand(time(NULL));
    for (i = 0; i < x; i++) {
        lista1[i] = rand() % x * x/RAND_MAX;          //pseudorandomiza elementos
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
            Cocktail(primeiro, lista1, x);              //chama função
            printf("\nOrdenado em Cocktail!\n");     //notifica se rodou
        }
        else if (choice == 2) {
            Counting(segundo, lista1, x);
            printf("\nOrdenado em Counting!\n");
        }
        else if (choice == 3) {
            Bucket(terceiro, lista1, x);
            printf("\nOrdenado em Bucket!\n");
        }
        else if (choice == 4) {
            Radix_bucket(quarto, lista1, x);
            printf("\nOrdenado em Radix -> Subalgoritmo: Bucket!\n");
        }
        else if (choice == 5) {
            Radix_counting(quinto, lista1, x);
            printf("\nOrdenado em Radix -> Subalgoritmo: Counting!\n");
        }
        else if (choice == 6) {
            Heap(sexto, lista1, x);
            printf("\nOrdenado em Heap!\n");
        }
        else if (choice == 7) {
            for (i = 0; i < x; i++) {
                printf("%d|", lista1[i]);
            }
        }
    }
    primeiro -> proximo = segundo;
    segundo -> proximo = terceiro;
    terceiro -> proximo = quarto;
    quarto -> proximo = quinto;
    quinto -> proximo = sexto;
    sexto -> proximo = NULL;

    Comparacoes(primeiro, segundo, terceiro, quarto, quinto, sexto);
    listar(primeiro);

    free(primeiro), (segundo), (terceiro);
    free(quarto), (quinto), (sexto);

    return 0;
}