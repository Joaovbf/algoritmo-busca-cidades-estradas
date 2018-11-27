#include "tadcity.c"

int main(){
    int i,j, aux, numeroDeCidades;
    printf("Informe o numero de cidades: ");
    scanf("%d", &numeroDeCidades);
    geraCidades(numeroDeCidades);
    tipo_Cidade *lista = lerArquivo(numeroDeCidades);

    for(i = 0; i < numeroDeCidades; i++){
            printf("%d ", i);
        for(j = 0; j < lista[i].numeroDeConexoes; j++){

            printf("%s <-> %s ", lista[i].conexoes[j].pontoA->nome, lista[i].conexoes[j].pontoB->nome);
        }
        printf("\n");
    }

    return 0;

}
