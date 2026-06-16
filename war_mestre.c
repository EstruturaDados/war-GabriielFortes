#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define QUANT_MISSOES 2
#define VITORIAS_SEQUENCIA 0


//struct do territorio e seus atributos
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


typedef struct {
    char descricao[150];
    char nivel[30];
    int alvo;
    int vitorias; //0 não 1 sim
    int concluida; //1 sim 0 nao
} Missao;


//prototipos
void cleanBuffer();
void showTerritorios(Territorio *mapa, int quant);
int cadastroTerritorio(Territorio **mapa);
int simularAtaque(Missao *missoes, Territorio* mapa, int atacante, int defensor);
Missao* inicializarMissoes(Territorio *mapa, const int quantTerritorio);
int atribuirMissao(Missao *missoes);
int verificarMissao(
    Missao *missoes, 
    Territorio *mapa,  
    int atacante, 
    int defensor, 
    int vencedor,
    int missaoAtual
);


int main() {
    Territorio *mapa;
    Missao *missoes;

    srand(time(NULL));
    
    int opcao, quantTerritorios; 
    int atacante, defensor, vencedor;
    int missaoAtual;

    

    //chamando cadastra territorio, que retornar a quantidade de territorios cadastrados
    quantTerritorios = cadastroTerritorio(&mapa);

    missoes = inicializarMissoes(mapa, quantTerritorios);

    missaoAtual = atribuirMissao(missoes);

    showTerritorios(mapa, quantTerritorios);

    verificarMissao(missoes, mapa, 0, 0, 0, missaoAtual);

    //
    do {
        printf("\n\n****BATALHA****\n\n");

        printf("1 - Simular Ataque\n");
        printf("2 - Cadastrar Novos Territorios\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            do {
                printf("\n\nEscolha o numero do territorio atacante: ");
                scanf("%d", &atacante);
                cleanBuffer();

                printf("\nEscolha o numero do terriorio defensor: ");
                scanf("%d", &defensor);
                cleanBuffer();

                if (atacante == defensor) {

                    printf("Um territorio não pode ser o atacante e o defensor ao mesmo tempo.");
                    printf("Escolha novamente...");

                    atacante = 0;
                    defensor = 0;

                } else if (atacante > quantTerritorios || defensor > quantTerritorios) {

                    printf("\nSelecione territorios validos.");
                    
                    atacante = 0;
                    defensor = 0;
                }

            } while (atacante == 0 || defensor == 0);

            vencedor = simularAtaque(missoes, mapa, atacante, defensor);

            verificarMissao(missoes, mapa, atacante, defensor, vencedor, missaoAtual);

            showTerritorios(mapa, quantTerritorios);
            
            if (opcao != 0) {
                printf("\n\nPressione Enter para continuar...\n");
                getchar();
                break;
            }
        
        default:
            break;
        }

    } while (opcao != 0);


    free(mapa);
    free(missoes);
}


//limpa lixo do scanf
void cleanBuffer () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//loop pra mostrar os territorios cadastrados
void showTerritorios(Territorio *mapa, int quant) {
    //verifica de mapa e null e quant maior que 0
    if (mapa == NULL || quant <= 0) {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }

    printf("Territorios cadastrados\n\n");

    //printando os atributos dos territorios
    for (int i = 0; i < quant; i++) {
        printf("%d- Nome: %s Cor: %s Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


//recebendo ponteiro do ponteiro da main, pra fazer a alocação logo após o cadastro
int cadastroTerritorio(Territorio **mapa) {
    
    int quantTerritorios;

    printf("Cadastro de Territorios\n\n");
    
    printf("Quantos territoritos ira cadastrar?\n");
    scanf("%d", &quantTerritorios);
    cleanBuffer();

    //alocando memoria
    *mapa = calloc(quantTerritorios, sizeof(**mapa));

    if (*mapa == NULL) {
        printf("Erro ao alocar memória");
        exit(1);
    }

    //cadastro
    for (int i = 0; i < quantTerritorios; i++) {
        printf("\nTerritorio %d\n", i+1);

        printf("\nDigite o nome: \n");
        fgets((*mapa)[i].nome, sizeof((*mapa)[i].nome), stdin);

        printf("\nDigite a cor: \n");
        fgets((*mapa)[i].cor, sizeof((*mapa)[i].cor), stdin);

        printf("\nNumero de tropas: \n");
        scanf("%d", &(*mapa)[i].tropas);
        cleanBuffer();  //limpando lixo apos o inteiro
    }

    //retornando a quantidade de territorios pra main
    return quantTerritorios;
}


int simularAtaque(Missao *missoes, Territorio* mapa, int atacante, int defensor) {
    int apostaAtacante = (rand() % 6);
    int apostaDefensor = (rand() % 6);

    //trazendo os indices reais
    atacante--;
    defensor--;

    if (mapa[atacante].tropas == 0 || mapa[defensor].tropas == 0) {
        printf("\nNão e possivel simular ataques com territorios sem tropas ou derrotados, escolha novos terriorios.\n");
        return 0;
    }

    if (apostaAtacante > apostaDefensor) {
        printf("\nAtaque bem sucedido. O defensor perdeu 1 tropa.\n");

        mapa[defensor].tropas--;

        if (mapa[defensor].tropas == 0) {
            printf("O defensor foi derrotado pelo territorio %s\n", mapa[atacante].nome);
        }

        return atacante;

    } else if (apostaAtacante < apostaDefensor) {
        printf("\nAtaque mau sucedido. O atacante perdeu uma 1 tropa.\n");

        mapa[atacante].tropas--;
        
        if (mapa[atacante].tropas == 0) {
            printf("O atacante foi derrotado. pelo territorio %s\n", mapa[defensor].nome);
        }

        return defensor;
    } else {
        printf("\nEmpate, nenhuma tropa perdida.\n");
        return 0;
    }

        if (mapa[atacante].tropas == 0 || mapa[defensor].tropas == 0) {
        printf("\nNão e possivel simular ataques sem tropas, escolha novos terriorios.\n");
        return 0;
    }

}


Missao* inicializarMissoes(Territorio *mapa, const int quantTerritorio) {
    
    const int sortTerritorio = rand() % quantTerritorio;
    char auxiliar;
    Missao *missoes = calloc(QUANT_MISSOES, sizeof(*missoes));

    if (missoes == NULL) {
        printf("\nErro ao alocar memoria.");
        exit(1);
    }

    sprintf(
        missoes[0].descricao,
        "Derrotar o territorio %s", 
        mapa[sortTerritorio].nome
    );
    
    strcpy(missoes[0].nivel, "2 - Medio");
    missoes[0].alvo = sortTerritorio; //territorio
    missoes[0].vitorias = 0;

    strcpy(missoes[1].descricao, "Ganhar 3 ataques em sequencia.");
    strcpy(missoes[1].nivel, "3 - Dificil");
    missoes[1].alvo = 0; //Numero de vitorias
    missoes[1].vitorias = 0;

    return missoes;

}


int atribuirMissao(Missao *missoes) {

    int missaoSorteada = rand() % QUANT_MISSOES;

    printf("\n\n+++MISSAO SORTEADA+++\n");
    printf("%s", missoes[missaoSorteada].descricao);

    return missaoSorteada;

}


int verificarMissao(Missao *missoes, Territorio *mapa, int atacante, int defensor, int vencedor, int missaoAtual) {
    
    printf("\n\nMISSOES\n");
    printf("%s\n", missoes[missaoAtual].descricao);

    if (missoes[missaoAtual].concluida != 1) {

        if (missaoAtual == 1 ) {
            if (vencedor != missoes[missaoAtual].alvo && mapa[vencedor].tropas == 0) {
                printf("Missão concluida. territorio derrotado.", missaoAtual);     
                missoes[missaoAtual].concluida = 1;
            } else {
                printf("\nStatus: Em andamento.");
            }
        } else if (missaoAtual == 2) {

            if (vencedor == atacante) {
        
                missoes[missaoAtual].vitorias++;

                if (missoes[missaoAtual].vitorias == 3) {
                    missoes[missaoAtual].concluida = 1;
                    printf("Missao concluida, 3 ataques em sequencia.");
                } else {
                    printf("Missao em andamento %d vitorias em sequencia.", missoes[missaoAtual].vitorias);
                }
            } else {
                printf("\nStatus: Em andamento.");
            }
        } else {
            printf(" Concluida.");
        }
    } 

    return 0;
}
