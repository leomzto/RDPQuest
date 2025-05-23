#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"

int menu(void);

void listarSaves(void);
void salvarJogo(Personagem *p, int espaco);
Personagem carregarSave(int slot);
void novoJogo(Personagem p);
Personagem criarPersonagem(void);
void mostrarStatus(Personagem *p);

void iniciarBatalha(Personagem *p, Inimigo *i);
Inimigo gerarInimigos(void);

void desafiarMasmorra(Personagem *p, Masmorra *m);
Inimigo gerarInimigosMasmorra(int andar);

void barraVida(char *nome, float vida_atual, float vida_max);


#endif