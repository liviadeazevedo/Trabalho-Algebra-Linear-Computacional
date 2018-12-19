#include<stdio.h>


/*

14) Construa um algoritmo que resolva o sistema Ax = b usando a fatoração QR. Considere A uma matriz de ordem 2. Seu algoritmo deve exibir ao final as matrizes Q e R.

*/


int main()
{
	//operadores de tamanho 2x2 (especificadona questao)
	float A[2][2], R[2][2];
	//lendo amatriz A
	int i, j, k;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			scanf("%f", &A[i][j]);
	//lendo o vetor b
	float b[2];
	for(i=0;i<2;i++)
		scanf("%f", &b[i]);

	//incializando o rotator com angulo de 45 graus
	float Q[2][2] = { {1, -1}, {1, 1} };

	// fazendo o calculo da patriz R = Qt.A	
	for(i=0;i<2;i++)
	{
		for(k=0;k<2;k++)
		{		
			float somatorio = 0;
			for(j=0;j<2;j++)
			{
				// ler nota 1 ao fim do código
				somatorio += Q[j][i] * A[j][k];
			}
			R[i][k] = somatorio;
		}
	}

	float Qtb[2];//vetor que gardara a multiplicacao da matriz Qt pelo vetor b
	for(i=0;i<2;i++)
	{
		float somatorio = 0;
		for(j=0;j<2;j++)
			somatorio += Q[j][i]*b[j];//simulando transposta de novo

		Qtb[i] = somatorio;
	}

	float x[2];

	//triangular inferior adaptado (R.x = Qt.b)
	for(i=1;i>=0;i--)
	{
		float somatorio = Qtb[i];
		for(j=1;j>=i;j--)
		{
			if(i==j)
				somatorio /= R[i][j];
			if(j>i)
				somatorio -= R[i][j]*x[j];
		}		
		x[i] = somatorio;
	}

	//imprimindo as matrizes
	printf("matriz Q: \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
			printf("%f ", Q[i][j]);
		printf("\n");
	}

	printf("\n");

	printf("matriz R: \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
			printf("%f ", R[i][j]);
		printf("\n");
	}
	
	printf("\n");
	
	//imprimindo a solucao
	printf("vetor solução x: \n");
	for(i=0;i<2;i++)
		printf("%f\n", x[i]);
}
//nota 1:
/* a formula seria R = Qt*A, mas inverter a posição de i e j no acesso a Q 
  é o suficiente para simular a transposição de Q */


