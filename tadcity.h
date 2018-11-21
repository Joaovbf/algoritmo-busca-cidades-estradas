/*
	Autor: Guilherme Souza Mattos
	Objetivo:

*/
#ifndef _TADCITY_H // Guardas de cabecalho - Impedem inclusoes ciclicas.
#define _TADCITY_H

// ------------------------------------------------------------------------
//	Inclusao das bibliotecas nativas da linguagem.
// ------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// ------------------------------------------------------------------------
//	Definicao das estruturas, constantes e variaveis globais
//	da biblioteca.
// ------------------------------------------------------------------------

// Definir uma estrutura para estrada.
typedef struct estrada {
	struct cidade *pontoA;
	struct cidade *pontoB;
	int custo;
} tipo_Estrada;

// Definir uma estrutura para cidade.
typedef struct cidade {
	char nome[64];
	struct estrada conexoes[3];
} tipo_Cidade;


// ------------------------------------------------------------------------
//	Prototipo das funcoes.
// ------------------------------------------------------------------------
tipo_Cidade* geraCidades();
void geraEstradas(tipo_Cidade *vetorCidades, int numeroDeCidades);
#endif
