/**
 * Simulation for a 4-set-associative Datacache with size 4 KiB.
 * One cacherow has 128 Byte, addresses have 32 Bit.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH (32)
#define SIZE (WIDTH*WIDTH)
//An Adresse 0x48000
int a[SIZE];
//An Adresse 0x52000
int b[SIZE];

struct block {
    char *tag;
    //int hasData;
    //char data[128];
};

char *int_to_binary(char *, int, int);
void indexing(int *, int *, int *, struct block *[], char *, char *);
void check_cache(int, int *, int *, int *, struct block *[], char *);

int main() {

    struct block menge0[4];
    struct block menge1[4];
    struct block menge2[4];
    struct block menge3[4];
    struct block menge4[4];
    struct block menge5[4];
    struct block menge6[4];
    struct block menge7[4];

    struct block *mengen[8];

    mengen[0] = menge0;
    mengen[1] = menge1;
    mengen[2] = menge2;
    mengen[3] = menge3;
    mengen[4] = menge4;
    mengen[5] = menge5;
    mengen[6] = menge6;
    mengen[7] = menge7;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            mengen[i][j].tag = malloc(28);
        }
    }

    time_t t;
    srand((unsigned) time(&t));
    int hits = 0;
    int misses = 0;
    int gotHit = 0;
    char *str = malloc(33);

    /*for (int i = 0; i < WIDTH * WIDTH; i++) {
        str[0] = '\0';
        int_to_binary(str, 294912 + 4 * i, 32);
        char *tmp = malloc(28);
        strncpy(tmp, str, 28);
        tmp[27] = '\n';
        indexing(&gotHit, &hits, &misses, mengen, tmp, str);

        str[0] = '\0';
        tmp[0] = '\0';
        int_to_binary(str, 335872 + 4 * i, 32);
        strncpy(tmp, str, 28);
        tmp[27] = '\n';
        indexing(&gotHit, &hits, &misses, mengen, tmp, str);
        printf("%i\t%s\n", i, str);
        free(tmp);
    }*/

    for (unsigned i = 0; i < WIDTH; ++i) {
        for (unsigned j = 0; j < WIDTH; ++j) {
            str[0] = '\0';
            int_to_binary(str, 294912 + j * WIDTH * 4 + 4 * i, 32);
            char *tmp = malloc(28);
            strncpy(tmp, str, 28);
            tmp[27] = '\n';
            indexing(&gotHit, &hits, &misses, mengen, tmp, str);

            str[0] = '\0';
            tmp[0] = '\0';
            int_to_binary(str, 335872 + j * WIDTH * 4 + 4 * i, 32);
            strncpy(tmp, str, 28);
            tmp[27] = '\n';
            indexing(&gotHit, &hits, &misses, mengen, tmp, str);
            printf("%i\t%s\n", j * WIDTH + i, str);
            free(tmp);
        }
    }
    printf("Hits: %i (%f%%), Misses: %i (%f%%)\n", hits, (hits / 2048.0) * 100.0, misses, (misses / 2048.0) * 100.0);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            free(mengen[i][j].tag);
        }
    }
    free(str);
}

void indexing(int *gotHit, int *hits, int *misses, struct block *mengen[], char *tmp, char *str) {
    if (str[27] == '0' && str[28] == '0' && str[30] == '0') {
        check_cache(0, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '0' && str[28] == '0' && str[30] == '1') {
        check_cache(1, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '0' && str[28] == '1' && str[30] == '0') {
        check_cache(2, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '0' && str[28] == '1' && str[30] == '1') {
        check_cache(3, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '1' && str[28] == '0' && str[30] == '0') {
        check_cache(4, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '1' && str[28] == '0' && str[30] == '1') {
        check_cache(5, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '1' && str[28] == '1' && str[30] == '0') {
        check_cache(6, gotHit, hits, misses, mengen, tmp);
    }
    else if (str[27] == '1' && str[28] == '1' && str[30] == '1') {
        check_cache(7, gotHit, hits, misses, mengen, tmp);
    }
}

void check_cache(int menge, int *gotHit, int *hits, int *misses, struct block *mengen[], char *tmp) {
    for (int k = 0; k < 4; k++) {
        if (mengen[menge][k].tag != NULL) {
            if (strcmp(mengen[menge][k].tag, tmp) == 0) {
                *hits += 1;
                *gotHit = 1;
            }
        }
    }
    if (*gotHit == 0) {
        *misses += 1;
        int block = rand() % 4;
        strcpy(mengen[menge][block].tag, tmp);
    }
    *gotHit = 0;
}

char *int_to_binary(char *str, int n, int size) {
    int k;
    for (int c = size - 1; c >= 0; c--) {
        k = n >> c;
        if (k & 1) strcat(str, "1");
        else strcat(str, "0");
        if (c % 4 == 0 && c != 0) strcat(str, " ");
    }
    return str;
}