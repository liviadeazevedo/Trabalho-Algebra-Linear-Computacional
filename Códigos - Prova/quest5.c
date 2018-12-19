#include <stdio.h>

/*

5) Construa um algoritmo que resolva um sistema triangular inferior de ordem k.

*/

int main(void)
{
	//variaveis de controle
	int k, num_flops = 0;

	//lendo a dimencao do sistema
	printf("valor de k\n");
	scanf("%d", &k);

	//criando os operadores
	float A[k][k], b[k], x[k];

	//lendo a matriz de coeficientes
	printf("ler matriz A\n");
	int i, j;
	for(i = 0; i < k ; i++)
	{
		
		for(j = 0; j < k ; j++)
		{
			scanf("%f", &A[i][j]);
		}
	}
	//kendo o vetor b
	printf("ler vetor b\n");
	for(i = 0; i < k ; i++)
	{
		scanf("%f", &b[i]);
	}

	//indo da primeira linha da matriz ate a ultima
	for(i = 0 ; i < k ; i++)
	{
		//indo da primeira coluna ate o termo da diagonal
		for(j = 0 ; j <= i  ; j++)
		{
			if(j<i)
			{
				//usando o proprio b para guardar os valores intermediarios
				b[i] -= A[i][j]*x[j];
				num_flops += 2;//contagem do numero de flops (subtracao e multiplicacao)
			}
			else
			{
				b[i] /= A[i][j];//dividindo pelo termo da diagonal
				num_flops += 1;//contagem do numero de flops (divisao)
			}
		}
		//encerrando a operacao da linha guardando o valor em x
		x[i] = b[i];
	}
	
	//imprimindo a solucao do sistema
	printf("valores de x\n");

	for(i = 0; i < k ; i++)
		printf("%4f\n", x[i]);

	//imprimindo o numero de flops
	printf("numero de flops:\n");
	printf("%d\n", num_flops);
}
