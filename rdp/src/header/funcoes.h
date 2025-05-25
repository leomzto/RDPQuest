#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"

// menus
    int menu(void);
    void jogo(Personagem p);

// personagem
    Personagem criarPersonagem(void);
    void mostrarStatus(Personagem *p);
    
// procurar monstros
    void iniciarBatalha(Personagem *p, Inimigo *i);
    Inimigo gerarInimigos(void);
        
// desafiar masmorras
    void desafiarMasmorra(Personagem *p, Masmorra *m);
    Inimigo gerarInimigosMasmorra(int andar);

// save_load
    void listarSaves(void);
    void salvarJogo(Personagem *p, int espaco);
    Personagem carregarSave(int slot);

// funcionalidades
    void barraVida(char *nome, float vida_atual, float vida_max);
    
// utilidades
    void limparBuffer(void);
    void limparTela(int tempo);
    void animacaoCarregamento(int tempo, char caractere, int espera);

#endif