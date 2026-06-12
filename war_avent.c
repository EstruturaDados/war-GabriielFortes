#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct do territorio e seus atributos
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


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


int simularAtaque(Territorio* mapa, int atacante, int defensor) {
    int apostaAtacante = (rand() % 100);
    int apostaDefensor = (rand() % 100);

    //trazendo os indices reais
    atacante--;
    defensor--;

    if (mapa[atacante].tropas == 0 || mapa[defensor].tropas == 0) {
        printf("\nNão e possivel simular ataques sem tropas ou derrotados, escolha novos terriorios.\n");
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


int main() {
    Territorio *mapa;
    srand(time(NULL));
    
    int opcao, quantTerritorios; 
    int atacante, defensor, vencedor;


    //chamando cadastra territorio, que retornar a quantidade de territorios cadastrados
    quantTerritorios = cadastroTerritorio(&mapa);

    showTerritorios(mapa, quantTerritorios);

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

            simularAtaque(mapa, atacante, defensor);
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
}