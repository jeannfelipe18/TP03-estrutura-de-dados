#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"


Estrada *getEstrada(const char *arquivo) {

	FILE *entrada;
	entrada = fopen("arquivo_teste01.txt", "r"); 
	
	if (entrada == NULL) {

        printf("Erro ao abrir o arquivo.\n");
        exit(1);

    }

	Estrada *novaEstrada = (Estrada *)malloc(sizeof(Estrada));
	
	if(novaEstrada == NULL) {

		printf("Erro ao criar uma nova estrada.\n");
		exit(1);

	}
	
	fscanf(entrada, "%d\n", &novaEstrada->T); 
	fscanf(entrada, "%d\n", &novaEstrada->N);
	
	if(novaEstrada->T < 3 || novaEstrada->T > 1000000) return NULL;

	if(novaEstrada->N < 2 || novaEstrada->N > 10000) return NULL;
		
	novaEstrada->C = (Cidade *)malloc(novaEstrada->N * sizeof(Cidade));
	
	int index;
	
	for(index = 0; index < novaEstrada->N; index++) {

		Cidade *cidadeAtual = (Cidade *)malloc(sizeof(Cidade));

		fscanf(entrada, "%d %[^\n]s", &cidadeAtual->Posicao, cidadeAtual->Nome);
		
		if(cidadeAtual->Posicao > novaEstrada->T) return NULL;

		novaEstrada->C[index] = *cidadeAtual;	
		
	}
	
	return novaEstrada;

}

void mostrarEstrada(Estrada *estradaAtual) {

	for(int index = 0; index < estradaAtual->N; index++) {
		
		printf("%d %s\n", estradaAtual->C[index].Posicao, estradaAtual->C[index].Nome);
		
	}

}

void sortEstradaPorDist(Estrada *estradaAtual) {
		
	for(int i = 0; i < estradaAtual->N; i++) {
			
		for(int j = i+1; j < estradaAtual->N; j++) {
			
			if(estradaAtual->C[i].Posicao > estradaAtual->C[j].Posicao) {
				
				Cidade temp = estradaAtual->C[i];
				estradaAtual->C[i] = estradaAtual->C[j];
				estradaAtual->C[j] = temp;
				
			}
			
		}
			
	}
	
}

double calcularMenorVizinhanca(const char *arquivo) {
	
	Estrada *estradaAtual = getEstrada("arquivo_teste01.txt");
	
	sortEstradaPorDist(estradaAtual);
	
	double minValue = estradaAtual->T+1;
	
	for(int i = 0; i < estradaAtual->N; i++) {
		
		double val = 0;
		
		if(i == 0) { // Se é a primeira cidade
		
			val += estradaAtual->C[i].Posicao; // calculando vizinhança pela esquerda da primeira cidade			
			
			val += (double)(estradaAtual->C[i+1].Posicao - estradaAtual->C[i].Posicao)/2; // calculando vizinhança pela direita da primeira cidade

		} else { // Se não for a primeira cidade
			
			val += (double)(estradaAtual->C[i].Posicao - estradaAtual->C[i-1].Posicao)/2;  
			
			if(i == estradaAtual->N-1) {
				
				val += (double)(estradaAtual->T - estradaAtual->C[i].Posicao); 
				
			} else {
				
				val += (double)(estradaAtual->C[i+1].Posicao - estradaAtual->C[i].Posicao)/2; 
				
			}
			
		}
		
		if(val < minValue) {
			minValue = val;
		}
		
	}
	
	return minValue;
	
}

char *cidadeMenorVizinhanca(const char *arquivo) {
	
	Estrada *estradaAtual = getEstrada("arquivo_teste01.txt");
	
	sortEstradaPorDist(estradaAtual);
	
	double minValue = estradaAtual->T+1;
	char *minCidade;
	
	for(int i = 0; i < estradaAtual->N; i++) {
		
		double val = 0;
		
		if(i == 0) {
		
			val += estradaAtual->C[i].Posicao;			
			
			val += (double)(estradaAtual->C[i+1].Posicao - estradaAtual->C[i].Posicao)/2; 

		} else {
			
			val += (double)(estradaAtual->C[i].Posicao - estradaAtual->C[i-1].Posicao)/2; 
			
			if(i == estradaAtual->N-1) {
				
				val += (double)(estradaAtual->T - estradaAtual->C[i].Posicao); 
				
			} else {
				
				val += (double)(estradaAtual->C[i+1].Posicao - estradaAtual->C[i].Posicao)/2; 
				
			}
			
		}		
		
		if(val < minValue) {
			minValue = val;
			minCidade = estradaAtual->C[i].Nome;
		}
			
	}
	
	return minCidade;
	
}
	

int main() {
	
	Estrada *testando = getEstrada("arquivo_teste01.txt");
	
	mostrarEstrada(testando);
	
	printf("\n");
	printf("tamanho da estrada = %d\n", testando->T);
	printf("quantidade de cidades = %d\n", testando->N);
	printf("menor vizinhanca = %.2lf\n", calcularMenorVizinhanca("arquivo_teste01.txt"));
	printf("cidade = %s\n", cidadeMenorVizinhanca("arquivo_teste01.txt"));

	return 0;
	
}

