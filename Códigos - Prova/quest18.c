#include<stdio.h>
#include<math.h>

/*

18) Construa um algoritmo para calcular as raízes de um polinômio característico de uma matriz de ordem 2.

*/


float Delta(float A[2][2])
{
	//formula geral de um delta da formula de baskara aplicado no polinomio caracteristico de uma matriz generica 2x2
	return pow(A[0][0]+A[1][1],2) - 4*(-1)*(A[1][0]*A[0][1] - A[0][0]*A[1][1]);
}

int main()
{
	float A[2][2];

	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			scanf("%f", &A[i][j]);

	//vetor com as duas raizes
	float lambida [2];
	//calculando o delta da baskara
	float delta = Delta(A);
	if(delta>=0)//se maior que zero existe raiz real
	{
		//-b + raiz(dekta)/2a
		lambida[0] = ( (-(A[0][0]+A[1][1]) + sqrt( delta ) )/-2 );
		//-b - raiz(dekta)/2a
		lambida[1] = ( (-(A[0][0]+A[1][1]) - sqrt( delta ) )/-2 );

		printf("raiz 1: %f    raiz 2: %f\n", lambida[0], lambida[1]);
	}
	else
	{
		printf("delta negativo, não há raiz real");
	}

}
