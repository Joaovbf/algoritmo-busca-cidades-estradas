#include "tadcity.h"

void geraCidades(int numeroDeCidades){
    srand((unsigned) time(NULL));

    int i, j;
    tipo_Cidade *vetorCidades = (tipo_Cidade*)malloc(numeroDeCidades * sizeof(tipo_Cidade));

    if (vetorCidades == NULL){
        printf("Erro: alocacao de memoria\n");
        exit(0);
    }

    for (i = 0; i < numeroDeCidades; i++){
        setbuf(stdin, NULL);
        printf("Informe nome da cidade: ");
        fgets(vetorCidades[i].nome, 64, stdin);
        vetorCidades[i].nome[strcspn(vetorCidades[i].nome, "\n")] = 0;//remove \n da variavel

        printf("Informe com quantas cidades essa cidade se relaciona: ");
        scanf("%d", &vetorCidades[i].numeroDeConexoes);

        vetorCidades[i].conexoes = (tipo_Estrada*)malloc(vetorCidades[i].numeroDeConexoes * sizeof(tipo_Estrada));
        if (vetorCidades == NULL){
            printf("Erro: alocacao de memoria\n");
            exit(0);
        }

       for(j = 0; j < vetorCidades[i].numeroDeConexoes; j++){ // Instancia todas as conexoes com o valor simbolico impossivel de -1 que demonstra vazio
            vetorCidades[i].conexoes[j].custo = -1;
       }
    }
    for (i = 0; i < numeroDeCidades; i++){
        printf("%d:%s\n", i, vetorCidades[i].nome);
    }
    geraEstradas(vetorCidades, numeroDeCidades);
}

void geraEstradas(tipo_Cidade *vetorCidades, int numeroDeCidades){
    srand((unsigned) time(NULL));

    int i, j, k, posicao;
    tipo_Estrada estrada;
    int sucesso_criar = 0; //Retorna 1 se conseguiu criar conexao e 0 se nao;

    for (i = 0; i < numeroDeCidades; i++){
        for(j = 0; j < vetorCidades[i].numeroDeConexoes; j++){
            if(vetorCidades[i].conexoes[j].custo == -1){
                while(sucesso_criar == 0){

                    printf("Informe a posiacao da cidade que sera conectada a %d* posicao da cidade %s: ",j+1, vetorCidades[i].nome);
                    scanf("%d", &posicao);
                    estrada.custo = rand() % 1000;
                    estrada.pontoA = &vetorCidades[i];
                    estrada.pontoB = &vetorCidades[posicao];

                    for(k = 0; k < vetorCidades[posicao].numeroDeConexoes; k++){
                        if(vetorCidades[posicao].conexoes[k].custo == -1){
                            vetorCidades[i].conexoes[j] = estrada;
                            vetorCidades[posicao].conexoes[k] = estrada;
                            sucesso_criar = 1;
                            k = vetorCidades[posicao].numeroDeConexoes;
                        }
                    }
                }
            }
            sucesso_criar = 0;
        }
    }
    salvarArquivo(vetorCidades, numeroDeCidades);
}

void salvarArquivo(tipo_Cidade *vetorCidades, int numeroDeCidades){

    int verificador;//verificar se todos elementos foram escritos

    FILE *arq = fopen("Relações.bin", "wb");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo \n");
        exit(1);
    }

    verificador = fwrite(vetorCidades,sizeof(tipo_Cidade),numeroDeCidades, arq);//escreve no arquivo e retorna quantos elementos foram escritos
    if (verificador != numeroDeCidades){
        printf("erro na escrita");
        exit(1);
    }

    fclose(arq);
}

tipo_Cidade* lerArquivo(int numeroDeCidades){

    tipo_Cidade *vetorCidades = (tipo_Cidade*)malloc(numeroDeCidades * sizeof(tipo_Cidade));
    int verificador;//verifica se todos elementos foram lidos

    FILE *arq = fopen("Relações.bin", "rb");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo \n");
        exit(1);
    }

    verificador = fread(vetorCidades, sizeof(tipo_Cidade), numeroDeCidades, arq);//ler arquivo e retorna quantas elementos foram lidos
    if (verificador != numeroDeCidades){
        printf("erro na leitura");
        exit(1);
    }

    fclose(arq);
    return vetorCidades;
}
