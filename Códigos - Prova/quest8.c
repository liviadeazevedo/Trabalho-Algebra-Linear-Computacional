#include<stdio.h>


/*

8)  a) Construa um algoritmo que para uma matriz A quadrada calcule L e U.
     b) Usando o que foi desenvolvido no item anterior, resolva um sistema Ax = b  
     c) Utilize a fatoração lu do Matlab para resolver alguns exemplos.

*/


int main()
{
	int n;
	scanf("%d", &n);
	float A[n][n], L[n][n], U[n][n], b[n];
	
	int i, j, k;
	//lendo A e montando a estrutura basica de L e U
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%f", &A[i][j]);

			if(i==j)
				L[i][j] = 1;
			if(i<j)
				L[i][j] = 0;

			U[i][j] = A[i][j];
		}
	}
	float copiaB[n];
	printf("\n");
	//lendo o vetor B e criando uma cópia para a prova real (apenas test case)
	for(i=0;i<n;i++)
	{
		scanf("%f", &b[i]);
	 	copiaB[i] = b[i];
	}

	//construindo as matrizes L e U
	for(k=0;k<n-1;k++)
	{
		for(i=k+1;i<n;i++)
		{
			L[i][k] = U[i][k]/U[k][k];
			U[i][k] = 0;
			for(j=k+1;j<n;j++)
			{
				U[i][j] -= L[i][k]*U[k][j];
			}
		}
	}
	
	//printando L
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%f ", L[i][j]);
		printf("\n");
	}

	printf("\n");

	//printando U
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%f ", U[i][j]);
		printf("\n");
	}

	printf("\n");

	float x[n], y[n];
	//calculando L*y=b substituicao pra tras
	for(i= 0;i<n;i++)
	{
		for(j= 0 ;j<=i;j++)
		{
			if(j<i)
			{
				b[i] -= L[i][j]*y[j];
			}
			if(i==j)
			{
				b[i] /= L[i][j];
			}
		}
		y[i] = b[i];
	}

	//calculando Ux = y por substituicao pra tras
	for(i= n-1;i>=0;i--)
	{
		for(j= n-1 ;j>=i;j--)
		{
			if(j>i)
			{
				y[i] -= U[i][j]*y[j];
			}
			if(i==j)
			{
				y[i] /= U[i][j];
			}
		}
		x[i] = y[i];
	}

/*	//printando b
	for(i=0;i<n;i++)
		printf("%f\n", b[i]);*/

	printf("\no resultado de Ax=b é: \n");

	for(i=0;i<n;i++)
		printf("%f\n", x[i]);
	printf("\n");

	//teste de prova real que aplica x à matriz A original (apenas test case)
/*	for(i=0;i<n;i++)
	{
	 	printf("%f    ", copiaB[i]);
	 	float acumulador = 0;
	 	for(j=0;j<n;j++)
		 	 acumulador += A[i][j]*x[j];
	 	 printf("%f\n", acumulador);
	}*/



}
