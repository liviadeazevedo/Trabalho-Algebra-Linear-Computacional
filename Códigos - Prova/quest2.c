#include <stdio.h>

/*

2) a) Construa um algoritmo em C que faça a multiplicação de uma matriz A(mxn) por uma matriz B(nxk) e que calcule o número total de flops.
    b) Exiba o resultado da multiplicação entre duas matrizes no Matlab.

*/


int main(void)
{
	// variaveis de controle
	int m, n, k, num_flops = 0;

	// obtendo dimencoes das matrizes
	printf("Entre com o valor de m\n");
	scanf("%d", &m);
	printf("Entre com o valor de n\n");
	scanf("%d", &n);
	printf("Entre com o valor de k\n");
	scanf("%d", &k);

	// matrizes operadoras
	float A[m][n], B[n][k], Result[m][k];

	// lendo A
	printf("Entre com a matriz A\n");
	int i, j;
	for(i = 0; i < m ; i++)
	{
		for(j = 0; j < n ; j++)
		{
			scanf("%f", &A[i][j]);
		}
	}

	printf("Entre com a matriz B\n");
	for(i = 0; i < n ; i++)
	{
		for(j = 0; j < k ; j++)
		{
			scanf("%f", &B[i][j]);
		}
	}

	// multiplicando Result = AB
	for(i = 0; i < m ; i++)
	{
		int l;
		for(l = 0; l < k ; l++)
		{
			float somatorio = 0;
			
			for(j = 0; j < n ; j++)
			{	
				somatorio += A[i][j]*B[j][l];// guardando o valor temporario
				num_flops += 2;// contando o numero de flops
			}
			Result[i][l] = somatorio;// após o calculo atribui o valor
		}
	}

	// imprimindo o resultado
	for(i = 0; i < m ; i++)
	{
		for(j = 0; j < k ; j++)
		{
			printf("resultado de AB:\n");
			printf("%f\n", Result[i][j]);
		}
	}

	// imprimindo o numero de flops
	printf("numero de flops:\n");
	printf("%d\n", num_flops);
}
