#include "includes.h"

// adicionado em dungeon.c
void desafiarMasmorra(Personagem *p, Masmorra *m)
{
    int i;

    if(!m->ativa)
    {
        m->ativa = true;
        m->andar_atual = 0;
        m->andares_completos = 0;

        for(i = 0; i < NUM_ANDARES; i++)
            m->inimigos_masmorra[i] = gerarInimigosMasmorra(i);

        puts("\nEntrando na masmorra");
        animacaoCarregamento(10, '.', 0);
        limparTela(1);

        puts("\n\nVoce entrou!\nTome cuidado.");
    }

    while(m->andar_atual < NUM_ANDARES && m->ativa)
    {
        printf("\nExplorando - Andar [%d]/[%d]\n", m->andar_atual + 1, NUM_ANDARES);
        animacaoCarregamento(10, '.', 0);
        puts("\nInimigo encontrado!");

        Inimigo* inimigo_atual = &m->inimigos_masmorra[m->andar_atual];

        iniciarBatalha(p, inimigo_atual);

        if (p->vida > 0 && (*inimigo_atual).vida <= 0)
        {
            printf("\n%s derrotou o inimigo do andar %d!\n", p->nome, m->andar_atual + 1);
            m->andar_atual++;

            p->vida += p->classe.vida * 0.3;
            if (p->vida > p->classe.vida)
                p->vida = p->classe.vida;

            limparTela(1);
        }
        else if(p->vida <= 0)
        {
            m->ativa = false;
            return;
        }
    }

    if(m->andar_atual >= NUM_ANDARES)
    {
        puts("\nMasmorra finalizada!");
        m->ativa = false;
        p->vida = p->classe.vida;
        p->dano += 5;
    }
}
// adicionado em enemy.c
Inimigo gerarInimigosMasmorra(int andar)
{
    Inimigo inimigo = gerarInimigos();

    float dificuldade = 1.0 + (andar * 0.2);
    inimigo.vida *= dificuldade;
    inimigo.dano *= dificuldade;
    inimigo.defesa *= dificuldade;

    return inimigo;
}
