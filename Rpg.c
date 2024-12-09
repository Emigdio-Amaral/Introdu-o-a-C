#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_INVENTARIO 10
#define MAX_RACAS 20
#define MAX_CLASSES 15
#define MAX_SOMBRIOS 50

// Definições de Estruturas

typedef struct {
    char nome[50];
    int bonusForca;
    int bonusInteligencia;
    int bonusDestreza;
    int bonusVida;
    int bonusMana;
    void (*habilidadeEspecial)(struct Personagem*);
} Raca;

typedef struct {
    char nome[50];
    int vidaBase;
    int manaBase;
    int ataqueBase;
    int defesaBase;
    void (*habilidadeClasse)(struct Personagem*);
} Classe;

typedef struct Personagem {
    char nome[50];
    Raca raca;
    Classe classe;
    int nivel;
    int experiencia;
    int vida;
    int mana;
    int forca;
    int inteligencia;
    int destreza;
    int defesa;
    int ouro;
    int pontosDeHabilidade;
    char inventario[MAX_INVENTARIO][50];
    int itensInventario;
    int danoCriticoStreak;
    struct Personagem* sombrio[MAX_SOMBRIOS];
} Personagem;

// Funções de Inicialização

void habilidadeVampiro(Personagem* p) {
    if (p->danoCriticoStreak >= 5) {
        printf("A habilidade do Vampiro falhou! Você foi derrotado após 5 danos críticos consecutivos.\n");
        p->vida = 0;
    } else {
        printf("Vampiro usa sua habilidade de imortalidade!\n");
    }
}

void habilidadeNecromante(Personagem* p) {
    if (p->nivel > 1) {
        printf("Necromante usa sua habilidade de reviver inimigos mortos! Você pode reviver até %d inimigos.\n", p->nivel * 10);
        for (int i = 0; i < p->nivel * 10; i++) {
            if (i < MAX_SOMBRIOS) {
                p->sombrio[i] = malloc(sizeof(Personagem));
                printf("Subordinado %d revivido!\n", i + 1);
            }
        }
    } else {
        printf("Necromante precisa de pelo menos nível 2 para reviver inimigos!\n");
    }
}

void definirRacas(Raca racas[]) {
    Raca listaRacas[] = {
        {"Humano", 1, 1, 1, 20, 10, NULL},
        {"Elfo", 0, 2, 2, 15, 15, NULL},
        {"Anão", 2, 0, 1, 30, 5, NULL},
        {"Orc", 3, 0, 0, 40, 0, NULL},
        {"Gnomo", 0, 2, 1, 10, 20, NULL},
        {"Meio-Elfo", 1, 1, 2, 20, 15, NULL},
        {"Troll", 3, 0, 0, 50, 0, NULL},
        {"Sereia", 0, 2, 2, 15, 20, NULL},
        {"Vampiro", 2, 2, 1, 25, 25, habilidadeVampiro},
        {"Lobisomem", 3, 0, 1, 35, 0, NULL},
        {"Dragão", 5, 3, 0, 100, 50, NULL},
        {"Demônio", 4, 2, 1, 70, 20, NULL},
        {"Fada", 1, 3, 2, 10, 30, NULL},
        {"Goblin", 0, 2, 3, 10, 10, NULL},
        {"Minotauro", 4, 0, 1, 50, 10, NULL},
        {"Centauro", 3, 1, 2, 40, 10, NULL},
        {"Duende", 0, 3, 2, 15, 15, NULL},
        {"Espírito", 1, 3, 0, 5, 50, NULL},
        {"Abissal", 4, 1, 0, 60, 10, NULL}
    };
    for (int i = 0; i < MAX_RACAS; i++) {
        racas[i] = listaRacas[i];
    }
}

void definirClasses(Classe classes[]) {
    Classe listaClasses[] = {
        {"Guerreiro", 100, 30, 25, 10, NULL},
        {"Mago", 60, 50, 5, 5, NULL},
        {"Arqueiro", 80, 40, 20, 10, NULL},
        {"Clérigo", 70, 45, 10, 20, NULL},
        {"Ladrão", 75, 35, 25, 15, NULL},
        {"Barbaro", 120, 20, 35, 15, NULL},
        {"Feiticeiro", 65, 60, 10, 5, NULL},
        {"Druida", 80, 45, 15, 10, NULL},
        {"Assassino", 85, 35, 30, 20, NULL},
        {"Cavaleiro", 110, 25, 20, 30, NULL},
        {"Bardo", 75, 40, 15, 20, NULL},
        {"Necromante", 65, 55, 5, 10, habilidadeNecromante},
        {"Caçador", 90, 35, 20, 15, NULL},
        {"Ilusionista", 50, 70, 10, 10, NULL},
        {"Gladiador", 95, 30, 25, 20, NULL}
    };
    for (int i = 0; i < MAX_CLASSES; i++) {
        classes[i] = listaClasses[i];
    }
}

void criarPersonagem(Personagem *p, Raca racas[], Classe classes[]) {
    printf("Digite o nome do seu personagem: ");
    scanf("%s", p->nome);

    printf("\nEscolha uma raça:\n");
    for (int i = 0; i < MAX_RACAS; i++) {
        printf("%d. %s\n", i + 1, racas[i].nome);
    }
    int escolhaRaca;
    scanf("%d", &escolhaRaca);
    p->raca = racas[escolhaRaca - 1];

    printf("\nEscolha uma classe:\n");
    for (int i = 0; i < MAX_CLASSES; i++) {
        printf("%d. %s\n", i + 1, classes[i].nome);
    }
    int escolhaClasse;
    scanf("%d", &escolhaClasse);
    p->classe = classes[escolhaClasse - 1];

    p->nivel = 1;
    p->experiencia = 0;
    p->vida = p->classe.vidaBase + p->raca.bonusVida;
    p->mana = p->classe.manaBase + p->raca.bonusMana;
    p->forca = 10 + p->raca.bonusForca;
    p->inteligencia = 10 + p->raca.bonusInteligencia;
    p->destreza = 10 + p->raca.bonusDestreza;
    p->defesa = p->classe.defesaBase;
    p->ouro = 100;
    p->itensInventario = 0;
    p->pontosDeHabilidade = 0;
    p->danoCriticoStreak = 0;

    printf("\nPersonagem %s criado com sucesso!\n", p->nome);
}

void exibirStatus(Personagem *p) {
    printf("\n===== Status do Personagem =====\n");
    printf("Nome: %s\n", p->nome);
    printf("Raça: %s\n", p->raca.nome);
    printf("Classe: %s\n", p->classe.nome);
    printf("Nível: %d\n", p->nivel);
    printf("Experiência: %d\n", p->experiencia);
    printf("Vida: %d\n", p->vida);
    printf("Mana: %d\n", p->mana);
    printf("Força: %d\n", p->forca);
    printf("Inteligência: %d\n", p->inteligencia);
    printf("Destreza: %d\n", p->destreza);
    printf("Defesa: %d\n", p->defesa);
    printf("Ouro: %d\n", p->ouro);
    printf("Itens no inventário: %d\n", p->itensInventario);
    printf("===============================\n");
}
// Funções de Combate

typedef struct {
    char nome[50];
    int vida;
    int ataque;
    int defesa;
    int recompensaOuro;
    int experienciaGanha;
} Inimigo;

void iniciarCombate(Personagem* p, Inimigo* inimigo) {
    printf("\n=== Combate Iniciado ===\n");
    printf("Você está enfrentando %s!\n", inimigo->nome);

    while (p->vida > 0 && inimigo->vida > 0) {
        printf("\nSeu HP: %d | HP do inimigo (%s): %d\n", p->vida, inimigo->nome, inimigo->vida);
        printf("Escolha uma ação:\n1. Atacar\n2. Usar habilidade especial\n3. Fugir\n");
        int acao;
        scanf("%d", &acao);

        switch (acao) {
            case 1: {
                int dano = p->forca - inimigo->defesa;
                if (dano < 0) dano = 0;
                printf("Você ataca e causa %d de dano!\n", dano);
                inimigo->vida -= dano;

                if (rand() % 100 < 10) { // 10% de chance de golpe crítico
                    int critico = dano * 2;
                    printf("Golpe Crítico! Você causa mais %d de dano!\n", critico);
                    inimigo->vida -= critico;
                    p->danoCriticoStreak++;
                } else {
                    p->danoCriticoStreak = 0; // Resetar streak se não for crítico
                }
                break;
            }
            case 2:
                if (p->raca.habilidadeEspecial != NULL) {
                    p->raca.habilidadeEspecial(p);
                }
                if (p->classe.habilidadeClasse != NULL) {
                    p->classe.habilidadeClasse(p);
                }
                break;
            case 3:
                printf("Você tenta fugir...\n");
                if (rand() % 100 < 50) { // 50% de chance de fuga
                    printf("Você conseguiu fugir do combate!\n");
                    return;
                } else {
                    printf("Você falhou na tentativa de fuga!\n");
                }
                break;
            default:
                printf("Ação inválida!\n");
                break;
        }

        // Ataque do inimigo
        if (inimigo->vida > 0) {
            int dano = inimigo->ataque - p->defesa;
            if (dano < 0) dano = 0;
            printf("O inimigo ataca e causa %d de dano!\n", dano);
            p->vida -= dano;
        }
    }

    if (p->vida <= 0) {
        printf("Você foi derrotado...\n");
    } else if (inimigo->vida <= 0) {
        printf("Você derrotou %s!\n", inimigo->nome);
        p->ouro += inimigo->recompensaOuro;
        p->experiencia += inimigo->experienciaGanha;
        printf("Você ganhou %d ouro e %d experiência!\n", inimigo->recompensaOuro, inimigo->experienciaGanha);
    }
}

// Exploração e Eventos Aleatórios

void explorar(Personagem* p) {
    printf("\n=== Explorando ===\n");

    int evento = rand() % 100;
    if (evento < 40) { // 40% de chance de encontrar inimigos
        Inimigo inimigo = {"Lobo Selvagem", 30, 10, 5, 15, 20};
        printf("Você encontrou um %s!\n", inimigo.nome);
        iniciarCombate(p, &inimigo);
    } else if (evento < 70) { // 30% de chance de encontrar tesouro
        int ouroEncontrado = rand() % 50 + 10;
        printf("Você encontrou um baú com %d moedas de ouro!\n", ouroEncontrado);
        p->ouro += ouroEncontrado;
    } else { // 30% de chance de eventos aleatórios
        printf("Você encontrou um viajante misterioso...\n");
        if (rand() % 100 < 50) {
            printf("Ele te dá um item raro!\n");
            if (p->itensInventario < MAX_INVENTARIO) {
                strcpy(p->inventario[p->itensInventario++], "Item Raro");
            } else {
                printf("Seu inventário está cheio!\n");
            }
        } else {
            printf("O viajante desaparece sem deixar rastros.\n");
        }
    }
}

// Sistema de Subir de Nível

void verificarNivel(Personagem* p) {
    int experienciaNecessaria = p->nivel * 100;
    if (p->experiencia >= experienciaNecessaria) {
        p->nivel++;
        p->pontosDeHabilidade += 5;
        p->vida += 20;
        p->mana += 10;
        p->forca += 2;
        p->inteligencia += 2;
        p->destreza += 2;
        printf("\nParabéns! Você subiu para o nível %d!\n", p->nivel);
    }
}

// Função Principal

int main() {
    srand(time(NULL));

    Raca racas[MAX_RACAS];
    Classe classes[MAX_CLASSES];
    Personagem jogador;

    definirRacas(racas);
    definirClasses(classes);
    criarPersonagem(&jogador, racas, classes);

    int jogando = 1;
    while (jogando) {
        exibirStatus(&jogador);
        printf("\nO que você deseja fazer?\n1. Explorar\n2. Descansar\n3. Sair\n");
        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                explorar(&jogador);
                verificarNivel(&jogador);
                break;
            case 2:
                printf("Você descansa e recupera sua vida e mana.\n");
                jogador.vida = jogador.classe.vidaBase + jogador.raca.bonusVida;
                jogador.mana = jogador.classe.manaBase + jogador.raca.bonusMana;
                break;
            case 3:
                jogando = 0;
                printf("Saindo do jogo. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        if (jogador.vida <= 0) {
            printf("Game Over. Seu personagem morreu.\n");
            jogando = 0;
        }
    }

    return 0;
}

// Combate e exploração foram ajustados para os novos requisitos
