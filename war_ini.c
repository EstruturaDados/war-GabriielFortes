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
        printf("Nenhum mapa cadastrado");
        return;
    }

    printf("Territórios cadastrados\n\n");

    //printando os atributos dos territorios
    for (int i = 0; i < quant; i++) {
        printf("Territorio %d\n\n", i + 1);
        printf("Nome: %s", mapa[i].nome);
        printf("Cor: %s", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }
}


int main() {
    Territorio mapa[5];  //cadastro de 5 territorios

    printf("Cadastro de Territorios\n\n");

    //loop coletando os atributos do cmd
    for (int i = 0; i < 5; i++) {
        printf("Território %d\n", i+1);

        printf("Digite o nome: \n");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);

        printf("Digite a cor: \n");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);

        printf("Numero de tropas: \n\n");
        scanf("%d", &mapa[i].tropas);
        cleanBuffer();  //limpando lixo apos o inteiro
    }

    //chamando a função mostrar territorios
    showTerritorios(mapa, (sizeof(mapa) / sizeof(mapa[0])));  //sizeof retorna o tamanho de bytes                                                 //todos os bytes / bytes[0] = 5
}