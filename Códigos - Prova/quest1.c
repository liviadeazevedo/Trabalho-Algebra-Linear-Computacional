#include <stdio.h>

/*

1) a) Construa um algoritmo em C que faça a multiplicação de uma matriz de tamanho mxn por um vetor de tamanho nx1. Insira no seu código o cálculo do número total de flops. 
    b) Exiba o resultado da multiplicação entre uma matriz e um vetor no Matlab.

*/

int main(void)
{
	// variaveis de controle
	int m, n, num_flops = 0;

	// obtendo dimencao da maitriz
	printf("Entre com o numero de linhas\n");
	scanf("%d", &m);
	printf("entre com o numero de colunas\n");
	scanf("%d", &n);

	// criando os fatores a serem multiplicados
	float A[m][n], b[n], Result[m];

	printf("Entre com a matriz A\n");
	int i, j;
	for(i = 0; i < m ; i++)
	{
		for(j = 0; j < n ; j++)
		{
			scanf("%f", &A[i][j]);
		}
	}

	printf("Entre com o vetor b\n");
	for(i = 0; i < n ; i++)
	{
		scanf("%f", &b[i]);
	}


	// aplicando a multiplicacao de Result = Ab
	for(i = 0; i < m ; i++)
	{
		float somatorio = 0;
		for(j = 0; j < n ; j++)
		{
			somatorio += A[i][j]*b[j];// guardando o valor temporario
			num_flops += 2;// contando o numero de flops
		}
		Result[i] = somatorio;// após o calculo atribui o valor
	}

	// imprimindo o resultado
	for(i = 0; i < m ; i++)
	{
		printf("resultado de Ab:\n");
		printf("%f\n", Result[i]);
	}

	// imprimindo numero de flops
	printf("numero de flops:\n");
	printf("%d\n", num_flops);
}
