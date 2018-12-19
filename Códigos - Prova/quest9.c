#include <stdio.h>
#include <math.h>


/*

9) a) Construa um algoritmo que calcule a norma 1, norma 2 e norma infinito de qualquer vetor x.   
    b) Construa um algoritmo que calcule a distância entre dois vetores x e y usando a norma 1, 2 e infinito.
    c) Construa um algoritmo que calcule o produto interno e o do ângulo entre dois vetores x e y.
    d) Construa um algoritmo que calcule a norma 1, norma infinito e norma de Frobenius de duas matrizes A e B. Calcule a distância entre essas matrizes.

*/


//calcula a norma 1 de um vetor de tamanho n
float Norma1(float x[], int n)
{
	int i;
	float somatorio = 0;
	for(i=0;i<n;i++)
	{
		if(x[i] < 0)
			x[i] *= -1;
		somatorio += x[i];
	}

	return somatorio;
}

//calcula a norma 2 de um vetor de tamanho n
float Norma2(float x[], int n)
{
	int i;
	float somatorio = 0;

	for(i=0;i<n;i++)
	{
		somatorio += pow(x[i], 2);
	}

	return sqrt(somatorio);
}

//calcula a norma infinito de um vetor de tamanho n
float NormaInfinito(float x[], int n)
{
	float Maior = 0;
	int i;
	
	for(i=0;i<n;i++)
	{
		if(x[i]<0)
			x[i] *= -1;

		if(i==0)
			Maior = x[i];
		else
		{
			if(x[i] > Maior)
				Maior = x[i];
		}
	}

	return Maior;
}

//calcula a distancia entre dois vetores x e y de tamanho n permitindo escolher a norma
float DistanciaEntreDoisVetores(float x[], float y[], int n, char norma)
{
	float result[n];
	int i;
	for(i=0;i<n;i++)
		result[i] = x[i] - y[i];

	switch(norma)
	{
		case '1':
			return Norma1(result, n);
		case '2':
			return Norma2(result, n);
		case 'i':
			return NormaInfinito(result, n);
	}
}

//calcula o produto interno entre dois vetores x e y de tamanho n
float ProdutoInterno(float x[], float y[], int n)
{
	float somatorio =0;
	int i;
	for(i=0;i<n;i++)
	{
		somatorio += x[i]*y[i];
	}

	return somatorio;
}
//retorna o cos do angulo entre dois vetores
float CosDoAnguloEntreDoisVetores(float x[], float y[], int n)
{
	return ProdutoInterno(x, y, n)/(Norma2(x,n)*Norma2(y,n));
}

//calcula a norma de fobenius (usando um ponteiro para referir a matriz Arxc devido a questoes da linguagem)
float NormaFrobenius(float* matrizA, int r, int c)
{
	int i, j;
	float somatorio = 0;

	float A[r][c];
	int k = 0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			A[i][j] = *(matrizA + k); //equivale a fazer A[i][j] = matrizA[k]
			k++;
		}

	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			somatorio += pow(A[i][j], 2);

	return sqrt(somatorio);
}

//calcula a norma 1 de uma matriz A (referenciada por matrizA) de tamanho rxc
float Norma1Matriz(float* matrizA, int r, int c)
{
	float result[r], somatorio;
	int i, j;

	float A[r][c];
	int k = 0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			A[i][j] = *(matrizA + k);
			k++;
		}
	for(i=0;i<r;i++)
	{
		somatorio = 0; //iniciando com 0
		for(j=0;j<c;j++)
		{
			if(A[i][j]<0)
				A[i][j] *= -1; // modulo

			somatorio += A[i][j];
		}
		result[i] = somatorio; //vetor resultado tem a soma dos elementos em cada linha
	}

	return NormaInfinito(result, r);//e aqui usamos a norma infinito nesse vetor com as somas
}

//calcula a norma infinito da matriz A (referenciada por matrizA) de tamanho rxc
float NormaInfinitoMatriz(float* matrizA, int r, int c)
{
	float result[c], somatorio;
	int i, j;

	float A[r][c];
	int k = 0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			A[i][j] = *(matrizA + k);
			k++;
		}

	for(j=0;j<c;j++)
	{
		somatorio = 0;//iniciando com 0
		for(i=0;i<r;i++)		
		{
			if(A[i][j]<0)
				A[i][j] *= -1;//modulo

			somatorio += A[i][j]; //somatorio
		}
		result[j] = somatorio;// resultado tem todos os somatorios dos elementos de todas as colunas
	}
	return NormaInfinito(result, c);// e aqui usamos a norma infinito do vetor com as somas
}

//calculando a distancia entre duas matrizes A e B (permitindo escolher a norma)
float DistanciaEntreDuasMatrizes(float* matrizA, float* matrizB, int r, int c, char norma)
{
	float result[r][c];
	int i,j;

	float A[r][c], B[r][c];
	int k = 0;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			A[i][j] = *(matrizA + k);
			B[i][j] = *(matrizB + k);
			k++;
		}

	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			result[i][j] = A[i][j] - B[i][j];//subtracao das matrizes elemento a elemento

	switch(norma)
	{
		case '1':
			return Norma1Matriz(&result[0][0], r, c);//chamando a funcao para a norma
		case 'f':
			return NormaFrobenius( &result[0][0] , r, c);//chamando a funcao para a norma
		case 'i':
			return NormaInfinitoMatriz(&result[0][0] ,r,c);//chamando a funcao para a norma
	}
}

int main()
{
	//lendo tamanho do vetor
	int n;
	printf("Digite a dimencao do vetor x: ");
	scanf("%d", &n);

	float x[n];
	//lendo vetor x
	int i, j;
	printf("Digite o vetor x: ");
	for(i=0;i<n;i++)
		scanf("%f", &x[i]);

	//calculando as normas do vetor
	printf("norma 1 de x: %f\n", Norma1(x, n) );
	printf("norma 2 de x: %f\n", Norma2(x, n) );
	printf("norma infinito de x: %f\n", NormaInfinito(x, n) );
	printf("\n");

	//lendo o vetor y
	float y[n];
	printf("Digite um vetor y de dimencao %d", n);
	for(i=0;i<n;i++)
		scanf("%f", &y[i]);

	//calculando as distancias entre x e y variando as normas
	printf("distancia entre x e y com norma 1: %f\n", DistanciaEntreDoisVetores(x, y, n, '1') );
	printf("distancia entre x e y com norma 2: %f\n", DistanciaEntreDoisVetores(x, y, n, '2') );
	printf("distancia entre x e y com norma infinito: %f\n", DistanciaEntreDoisVetores(x, y, n, 'i') );
	printf("\n");

	//calculando o produto interno e o angulo entre os vetores
	printf("produto interno entre dois vetores : %f\n", ProdutoInterno(x, y, n) );
	printf("angulo entre x e y : %f\n", acos(CosDoAnguloEntreDoisVetores(x, y, n)) );
	printf("\n");

	//repetindo todo o processo para as matrizes (exceto o angulo e o produto interno)
	int r,c;
    //forcando que a matriz seja quadrada
    printf("Digite a dimencao de A e B: ");
	scanf("%d", &r);
	c = r;
	float A[r][c], B[r][c];

	printf("Digite a matriz A: ");
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			scanf("%f", &A[i][j]);
	
    printf("Digite a matriz B: ");
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			scanf("%f", &B[i][j]);

	
	printf("norma 1 de A: %f\n", Norma1Matriz(&A[0][0], r, c) );
	printf("norma 1 de B: %f\n", Norma1Matriz(&B[0][0], r, c) );

	printf("\n");

	printf("norma frobenius de A: %f\n", NormaFrobenius(&A[0][0], r, c) );
	printf("norma frobenius de B: %f\n", NormaFrobenius(&B[0][0], r, c) );

	printf("\n");

	printf("norma infinito de A: %f\n", NormaInfinitoMatriz(&A[0][0], r, c) );
	printf("norma infinito de B: %f\n", NormaInfinitoMatriz(&B[0][0], r, c) );

	printf("\n\n");

	printf("distancia entre A e B com norma 1: %f\n", DistanciaEntreDuasMatrizes(&A[0][0], &B[0][0], r, c, '1') );
	printf("distancia entre A e B com norma de Forbenius: %f\n", DistanciaEntreDuasMatrizes(&A[0][0], &B[0][0], r, c, 'f') );
	printf("distancia entre A e B com norma infinito: %f\n", DistanciaEntreDuasMatrizes(&A[0][0], &B[0][0], r, c, 'i') );

}
