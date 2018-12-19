#include <stdio.h>

/*

4) Construa um algoritmo que resolva um sistema triangular superior de ordem k.

*/

int main(void)
{
	//variaveis de controle
	int k, num_flops = 0;

	//lendo a dimencao do sistema
	printf("valor de k\n");
	scanf("%d", &k);

	//criando operadores
	float A[k][k], b[k], x[k];

	//leitura da natriz de coeficientes
	printf("ler matriz A\n");
	int i, j;
	for(i = 0; i < k ; i++)
	{
		for(j = 0; j < k ; j++)
		{
			scanf("%f", &A[i][j]);
		}
	}

	//leitura do vetor b
	printf("ler vetor b\n");
	for(i = 0; i < k ; i++)
	{
		scanf("%f", &b[i]);
	}

	//seguindo da ultima linha ate a primeira
	for(i = k-1 ; i >= 0 ; i--)
	{
		//seguindo da ultima coluna ate a coluna de mesmo numero da linha
		for(j = k-1 ; j >= i ; j--)
		{
			if(j>i)
			{
				//utilizando o proprio b para guardar os resultados intermediarios
				b[i] -= A[i][j]*x[j];
				num_flops += 2;//contagem do numero de flops (subtracao e multiplicacao)
			}
			else
			{
				//enverrando a operacao da linha com a divisao
				b[i] /= A[i][j];
				num_flops += 1;//contagem do numero de flops (divisao)
			}
		}
		x[i] = b[i];//guardando o resultado em x
	}

	//imprimindo a solucao
	printf("valores de x\n");
	for(i = 0; i < k ; i++)
		printf("%f\n", x[i]);

	//imprimindo o numero de flops
	printf("numero de flops:\n");
	printf("%d\n", num_flops);
}
