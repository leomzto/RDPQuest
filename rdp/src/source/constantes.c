#include "includes.h"

// adicionado em player.c
const Classe CLASSES[] = {
    {"suprema", 1000.0f, 1000.0f, 1000.0f},
    {"Guerreiro", 120.0f, 20.0f, 15.0f},
    {"Mago", 80.0f, 30.0f, 5.0f},
    {"Arqueiro", 100.0f, 25.0f, 10.0f},
    {"Paladino", 130.0f, 18.0f, 20.0f},
    {"Barbaro", 160.0f, 28.0f, 12.0f},
    {"Ladino", 90.0f, 22.0f, 8.0f}
};

// adicionado em enemy.c
const Inimigo INIMIGOS[] = {
    {"Esqueleto", 50.0f, 10.0f, 5.0f, 25.0f},
    {"Esqueleto Guerreiro", 80.0f, 15.0f, 8.0f, 15.0f},
    {"Orc", 120.0f, 20.0f, 10.0f, 20.0f},
    {"Chefe Orc", 200.0f, 30.0f, 15.0f, 5.0f},
    {"Goblin", 40.0f, 12.0f, 4.0f, 25.0f},
    {"Goblin Chefe", 90.0f, 18.0f, 6.0f, 10.0f},
    {"Dragao Jovem", 300.0f, 40.0f, 20.0f, 3.0f},
    {"Dragao Anciao", 600.0f, 70.0f, 35.0f, 1.0f},
    {"Slime", 30.0f, 8.0f, 2.0f, 30.0f},
    {"Slime Rei", 150.0f, 18.0f, 10.0f, 5.0f},
    {"Demonio", 100.0f, 25.0f, 10.0f, 7.0f},
    {"Lorde Demonio", 500.0f, 50.0f, 25.0f, 0.5f}
};
