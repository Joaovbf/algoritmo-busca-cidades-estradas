#include "tadcity.h"

tipo_Cidade* geraCidades(){
    srand((unsigned) time(NULL));

    int numeroDeCidades, i, j;
    tipo_Cidade *vetorCidades = NULL;

    printf("informe o numero de cidades");
    scanf("%d", &numeroDeCidades);

    vetorCidades = malloc(numeroDeCidades * sizeof(tipo_Cidade));
    if (vetorCidades == NULL){
        printf("Erro: alocacao de memoria\n");
        exit(0);
    }

    for (i = 0; i < numeroDeCidades; i++){
        vetorCidades[i].nome[0] = (65 + rand() % 26);
        vetorCidades[i].nome[1] = (65 + rand() % 26);
        printf("%c%c\n", vetorCidades[i].nome[0], vetorCidades[i].nome[1]);
        for(j = 0; j < 3; j++){ // Instancia todas as conexoes com o valor simbólico impossível de -1 que demonstra vazio
            vetorCidades[i].conexoes[j].custo = -1;
        }
    }

    geraEstradas(vetorCidades, numeroDeCidades);
    return vetorCidades;
}
void geraEstradas(tipo_Cidade *vetorCidades, int numeroDeCidades){
    srand((unsigned) time(NULL));

    int i, j, k, aux, custo;
    tipo_Estrada estrada;
    int sucesso_criar = 0; //Retorna 1 se conseguiu criar conexao e 0 se nao;

    for (i = 0; i < numeroDeCidades; i++){

        for(j = 0; j < 3; j++){
            if(vetorCidades[i].conexoes[j].custo == -1){//-1 é o valor de custo impossivel que demonstra que aquela posição está vazia
                while(sucesso_criar == 0){
                    aux = rand() % numeroDeCidades;
                    estrada.custo = rand() % 1000;
                    estrada.pontoA = &vetorCidades[i];
                    estrada.pontoB = &vetorCidades[aux];

                    for(k = 0; k < 3; k++){
                        if(vetorCidades[aux].conexoes[k].custo == -1){ //-1 é o valor de custo impossivel que demonstra que aquela posição está vazia
                            vetorCidades[i].conexoes[j] = estrada;
                            vetorCidades[aux].conexoes[j] = estrada;
                            sucesso_criar = 1;
                            k = 3;
                        }
                    }
                }
            }
            sucesso_criar = 0;
        }
    }
}

