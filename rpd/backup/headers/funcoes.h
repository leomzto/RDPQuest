#ifndef FUNCOES_H
#define FUNCOES_H

#include "includes.h"

int menu(void);
void novoJogo(Personagem p);
Personagem criarPersonagem(void);
void iniciarBatalha(Personagem *p, Inimigo *i);
Inimigo gerarInimigos(void);
void desafiarMasmorra(Personagem *p, Masmorra *m);
Inimigo gerarInimigosMasmorra(int andar);
void mostrarStatus(Personagem *p);
void barraVida(char *nome, float vida_atual, float vida_max);

#endif