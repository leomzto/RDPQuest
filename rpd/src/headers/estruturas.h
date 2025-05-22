#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>
#include "defines.h"

typedef struct {
    char nome[20];
    float vida, dano, defesa;
} Classe;

typedef struct {
    char nome[50];
    Classe classe;
    float vida, dano, defesa;
    float vida_max, dano_max, defesa_max;
} Personagem;

typedef struct {
    char nome[50];
    float vida, dano, defesa;
    float chances_de_aparecer;
} Inimigo;

typedef struct {
    int andar_atual;
    int andares_completos;
    bool ativa;
    Inimigo inimigos_masmorra[NUM_ANDARES];
} Masmorra;

#endif
