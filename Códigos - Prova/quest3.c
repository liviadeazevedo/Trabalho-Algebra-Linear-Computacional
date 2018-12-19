#include <stdio.h>
#include <math.h>

/*

3) Construa um algoritmo que calcule o determinante de uma matriz A(2x2) e de uma matriz B(3x3).

*/


//funcao que calcula um determinante de uma matriz 2x2
float Det2x2(float A[2][2])
{
	return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}

//funcao que calcula um determinante de uma matriz 3x3 por la place usando a 2x2
float Det3x3 (float B[3][3])
{
	float DetB = 0;
	int i;
	for(i=0;i<3;i++)
	{
		float subB[2][2];
		int l,c;
		for(l=0;l<2;l++)//forma a matriz 2x2 que resta dos isolamentos
		{
			for(c=0;c<3;c++)
			{
				if(c<i)
					subB[l][c] = B[l+1][c];// deduzidas a partir de observacoes
				if(c>i)
					subB[l][c-1] = B[l+1][c];// deduzidas a partir de observacoes
				if(c==i)
					continue;
			}
		}
		//formula de do determinante de la place
		DetB += ( pow( (-1),((i+1)+1) ) * Det2x2(subB) * B[i][0]);
	}

	return DetB;
}

int main(void)
{
	//variaveis de controle
	int i, j;
	printf("Entre com uma matriz 2x2\n");
	float A[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			scanf("%f", &A[i][j]);*

	//imprimindo o primeiro resultado
	printf("Resultado do determinante 2x2 : %f\n", Det2x2(A));
	printf("Entre com uma matriz 3x3\n");
	float B[3][3];

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf("%f", &B[i][j]);
	
	//imprimindo o segundo resultado
	printf("Resultado do determinante 3x3 : %f\n", Det3x3(B));
}
