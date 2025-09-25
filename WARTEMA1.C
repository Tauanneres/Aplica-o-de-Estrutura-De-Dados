// =============================================================================
// JOGO DO WAR TEMA 1 ESTRUTURADO - DESAFIO FINAL: MISSÕES ESTRATÉGICAS
// Um projeto para consolidar os conceitos de C com um jogo clássico.
// =============================================================================

// --- Bibliotecas  ---
// A gente vai precisar delas pra tudo: I/O, alocação de memória, strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estruturas de Dados ---
// A base do nosso jogo: o que define um território.
typedef struct {
    char nome[30];
    char cor[10]; // Cor do jogador que domina
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// É uma boa prática declarar todas as funções aqui no começo.
// Ajuda a organizar e a entender o que o programa faz.

// Funções de Setup e Gerenciamento
void inicializarMapa(Territorio** mapa, int* tamanhoMapa);
void liberarMemoria(Territorio* mapa, int tamanhoMapa, char* missaoP1, char* missaoP2);

// Funções de Missão
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, int tamanhoMapa, const char* corJogador);

// Funções de Jogo
void exibirMapa(const Territorio* mapa, int tamanhoMapa);
void atacar(Territorio* atacante, Territorio* defensor);
void turnoJogador(const char* nomeJogador, const char* corJogador, Territorio* mapa, int tamanhoMapa);

// =============================================================================
// FUNÇÃO PRINCIPAL (main)
// O coração do programa. Ela orquestra as chamadas para as outras funções.
// =============================================================================
int main() {
    // Primeiro de tudo, vamos inicializar o gerador de números aleatórios.
    // Fazemos isso uma única vez para garantir que os "dados" rolem diferente a cada jogo.
    srand(time(NULL));

    Territorio* mapa = NULL;
    int tamanhoMapa = 0;
    char* missaoJogador1 = NULL;
    char* missaoJogador2 = NULL;

    // --- Setup do Jogo ---
    printf("======================================\n");
    printf("    BEM-VINDO AO WAR ESTRUTURADO!\n");
    printf("======================================\n\n");

    inicializarMapa(&mapa, &tamanhoMapa);

    // Definindo o arsenal de missões possíveis.
    const char* missoes[] = {
        "Conquistar o Continente Norte", // Territórios 0 e 1
        "Conquistar as Ilhas do Sul",   // Territórios 2 e 3
        "Eliminar todas as tropas Verdes",
        "Eliminar todas as tropas Azuis",
        "Manter 8 tropas no Forte da Colina" // Território 4
    };
    int totalMissoes = 5;

    // Alocando espaço para as missões dos jogadores.
    // Usamos 100 chars, um tamanho seguro para as missões que criamos.
    missaoJogador1 = (char*)malloc(100 * sizeof(char));
    missaoJogador2 = (char*)malloc(100 * sizeof(char));
    
    // Verificando se a memória foi alocada com sucesso. Crucial!
    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro fatal: Falha ao alocar memoria para as missoes!\n");
        // Se falhou, temos que liberar o que já foi alocado antes de sair.
        free(mapa);
        free(missaoJogador1);
        free(missaoJogador2);
        return 1;
    }

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("--- Missao Jogador 1 (Azul): %s\n", missaoJogador1);
    printf("--- Missao Jogador 2 (Verde): %s\n\n", missaoJogador2);

    // --- Loop Principal do Jogo ---
    int turno = 1;
    int vencedor = 0; // 0 = sem vencedor, 1 = P1 venceu, 2 = P2 venceu

    while (vencedor == 0 && turno <= 10) { // Vamos limitar a 10 turnos por enquanto
        printf("\n<<<<<<<<<<<<<<<<< TURNO %d >>>>>>>>>>>>>>>>>\n", turno);

        // Turno do Jogador 1
        turnoJogador("Jogador 1", "Azul", mapa, tamanhoMapa);
        if (verificarMissao(missaoJogador1, mapa, tamanhoMapa, "Azul")) {
            vencedor = 1;
            break; // Se venceu, sai do loop
        }

        // Turno do Jogador 2
        turnoJogador("Jogador 2", "Verde", mapa, tamanhoMapa);
        if (verificarMissao(missaoJogador2, mapa, tamanhoMapa, "Verde")) {
            vencedor = 2;
            break;
        }

        turno++;
    }

    // --- Fim de Jogo ---
    printf("\n======================================\n");
    printf("            FIM DE JOGO!\n");
    printf("======================================\n");

    if (vencedor == 1) {
        printf("O Jogador 1 (Azul) cumpriu sua missao e venceu o jogo!\n");
    } else if (vencedor == 2) {
        printf("O Jogador 2 (Verde) cumpriu sua missao e venceu o jogo!\n");
    } else {
        printf("Ninguem cumpriu a missao em 10 turnos. O jogo empatou!\n");
    }
    
    exibirMapa(mapa, tamanhoMapa);

    // --- Limpeza ---
    // A regra de ouro: se você alocou com malloc/calloc, você deve liberar com free.
    liberarMemoria(mapa, tamanhoMapa, missaoJogador1, missaoJogador2);
    printf("\nMemoria liberada com sucesso. Jogo encerrado.\n");

    return 0;
}

// =============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// =============================================================================

/**
 * @brief Prepara o estado inicial do mapa do jogo.
 * @param mapa Ponteiro para o ponteiro do mapa (para podermos alocar aqui dentro).
 * @param tamanhoMapa Ponteiro para a variável de tamanho (para atualizarmos o valor).
 */
void inicializarMapa(Territorio** mapa, int* tamanhoMapa) {
    *tamanhoMapa = 5;
    // Alocamos memória para o nosso vetor de territórios.
    *mapa = (Territorio*)malloc(*tamanhoMapa * sizeof(Territorio));

    // Se a alocação falhar, o programa não pode continuar.
    if (*mapa == NULL) {
        printf("Erro fatal: Nao foi possivel alocar memoria para o mapa!\n");
        exit(1); // exit(1) encerra o programa imediatamente.
    }

    // Criando os territórios manualmente para nosso jogo.
    strcpy((*mapa)[0].nome, "Planicies Centrais");
    strcpy((*mapa)[0].cor, "Azul");
    (*mapa)[0].tropas = 5;

    strcpy((*mapa)[1].nome, "Montanhas do Norte");
    strcpy((*mapa)[1].cor, "Azul");
    (*mapa)[1].tropas = 3;

    strcpy((*mapa)[2].nome, "Costa Selvagem");
    strcpy((*mapa)[2].cor, "Verde");
    (*mapa)[2].tropas = 5;

    strcpy((*mapa)[3].nome, "Pântano do Sul");
    strcpy((*mapa)[3].cor, "Verde");
    (*mapa)[3].tropas = 3;

    strcpy((*mapa)[4].nome, "Forte da Colina");
    strcpy((*mapa)[4].cor, "Neutro");
    (*mapa)[4].tropas = 10;
}

/**
 * @brief Libera toda a memória que foi alocada dinamicamente.
 * @param mapa Ponteiro para o mapa.
 * @param missaoP1 Missão do jogador 1.
 * @param missaoP2 Missão do jogador 2.
 */
void liberarMemoria(Territorio* mapa, int tamanhoMapa, char* missaoP1, char* missaoP2) {
    // A ordem de verificação e liberação é importante para evitar erros.
    if (mapa != NULL) {
        free(mapa);
    }
    if (missaoP1 != NULL) {
        free(missaoP1);
    }
    if (missaoP2 != NULL) {
        free(missaoP2);
    }
}

/**
 * @brief Sorteia uma missão do vetor de missões e a copia para o jogador.
 * @param destino Ponteiro para a string que vai receber a missão.
 * @param missoes Vetor de strings com as missões disponíveis.
 * @param totalMissoes O número total de missões no vetor.
 */
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * @brief Verifica se a condição de vitória de uma missão foi alcançada.
 * @param missao A string da missão a ser verificada.
 * @param mapa O estado atual do jogo.
 * @param tamanhoMapa Tamanho do mapa.
 * @param corJogador Cor do jogador que está sendo verificado.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(const char* missao, const Territorio* mapa, int tamanhoMapa, const char* corJogador) {
    // A lógica aqui é simples, baseada na string da missão.
    // Em um jogo real, isso seria bem mais complexo, talvez com códigos de missão.
    if (strcmp(missao, "Conquistar o Continente Norte") == 0) {
        return (strcmp(mapa[0].cor, corJogador) == 0 && strcmp(mapa[1].cor, corJogador) == 0);
    }
    if (strcmp(missao, "Conquistar as Ilhas do Sul") == 0) {
        return (strcmp(mapa[2].cor, corJogador) == 0 && strcmp(mapa[3].cor, corJogador) == 0);
    }
    if (strcmp(missao, "Eliminar todas as tropas Verdes") == 0) {
        for (int i = 0; i < tamanhoMapa; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) return 0; // Achou um verde, missão não cumprida.
        }
        return 1; // Não achou nenhum verde, missão cumprida.
    }
    if (strcmp(missao, "Eliminar todas as tropas Azuis") == 0) {
        for (int i = 0; i < tamanhoMapa; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) return 0; // Achou um azul, missão não cumprida.
        }
        return 1; // Não achou nenhum azul, missão cumprida.
    }
    if (strcmp(missao, "Manter 8 tropas no Forte da Colina") == 0) {
        return (strcmp(mapa[4].cor, corJogador) == 0 && mapa[4].tropas >= 8);
    }

    return 0; // Se a missão não for reconhecida, retorna 0.
}

/**
 * @brief Exibe o estado atual de todos os territórios no mapa.
 * @param mapa Ponteiro para o mapa (const para garantir que não vamos modificar nada).
 * @param tamanhoMapa Número de territórios.
 */
void exibirMapa(const Territorio* mapa, int tamanhoMapa) {
    printf("\n----------- MAPA DO MUNDO -----------\n");
    for (int i = 0; i < tamanhoMapa; i++) {
        printf("[%d] %-20s | Dominado por: %-7s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-------------------------------------\n");
}

/**
 * @brief Simula um ataque de um território para outro.
 * @param atacante Ponteiro para o território que ataca.
 * @param defensor Ponteiro para o território que defende.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Rolagem de dados simples: um dado para cada.
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf(">>> Combate: %s (%d tropas) ataca %s (%d tropas)!\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("... Dado do Atacante: %d\n", dadoAtacante);
    printf("... Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("!!! VITORIA DO ATACANTE! %s foi conquistado!\n", defensor->nome);
        // O defensor perde todas as tropas.
        defensor->tropas = 0;
        // O atacante move metade de suas tropas (mínimo 1) para o novo território.
        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas == 0) tropasMovidas = 1;
        
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
        // O território conquistado muda de cor.
        strcpy(defensor->cor, atacante->cor);

    } else {
        printf("--- VITORIA DO DEFENSOR! O ataque foi repelido.\n");
        // O atacante perde 1 tropa na derrota.
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

/**
 * @brief Controla as ações de um jogador durante seu turno.
 * @param nomeJogador Nome do jogador atual.
 * @param corJogador Cor do jogador atual.
 * @param mapa Ponteiro para o mapa do jogo.
 * @param tamanhoMapa Tamanho do mapa.
 */
void turnoJogador(const char* nomeJogador, const char* corJogador, Territorio* mapa, int tamanhoMapa) {
    int idAtacante, idDefensor;

    printf("\n--- TURNO DE: %s (%s) ---\n", nomeJogador, corJogador);
    exibirMapa(mapa, tamanhoMapa);

    // Lógica de ataque
    printf("Escolha o territorio para atacar (ou -1 para pular): ");
    scanf("%d", &idAtacante);

    if (idAtacante == -1) {
        printf("%s decidiu nao atacar.\n", nomeJogador);
        return;
    }

    printf("Escolha o territorio alvo: ");
    scanf("%d", &idDefensor);

    // Validações do ataque
    if (idAtacante < 0 || idAtacante >= tamanhoMapa || idDefensor < 0 || idDefensor >= tamanhoMapa) {
        printf("Erro: ID de territorio invalido!\n");
        return;
    }
    if (strcmp(mapa[idAtacante].cor, corJogador) != 0) {
        printf("Erro: Voce so pode atacar com um territorio seu!\n");
        return;
    }
    if (strcmp(mapa[idDefensor].cor, corJogador) == 0) {
        printf("Erro: Voce nao pode atacar um territorio que ja e seu!\n");
        return;
    }
    if (mapa[idAtacante].tropas < 2) {
        printf("Erro: Voce precisa de pelo menos 2 tropas para iniciar um ataque!\n");
        return;
    }

    // Se tudo estiver certo, o ataque acontece.
    atacar(&mapa[idAtacante], &mapa[idDefensor]);
}

