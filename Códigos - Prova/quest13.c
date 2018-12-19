#include<stdio.h>


/*

13) Construa um algoritmo que avalie se uma matriz é ortogonal.

*/


int main()
{
	int n;
	printf("Qual a ordem da matriz?\n");
	scanf("%d", &n);

	float A[n][n], At[n][n];
	int i, j;
	printf("Qual a matriz A?\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%f", &A[i][j]);
			At[j][i] = A[i][j];
		}

	int EhOrtogonal = 1;

    float Result[n][n];
    for(i = 0; i < n ; i++)
	{
		int l;
		for(l = 0; l < n ; l++)
		{
			float somatorio = 0;

			for(j = 0; j < n ; j++)
			{
				somatorio += A[i][j]*At[j][l];
			}
			Result[i][l] = somatorio;
		}
	}


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
            if(i==j)
            {
                if(Result[i][j]!=1)
                {
                    EhOrtogonal = 0;
                    break;
                }
            }
            else
            {
                if(Result[i][j]!=0)
                {
                    EhOrtogonal = 0;
                    break;
                }
            }
        }
        if(EhOrtogonal == 0)
            break;
    }

	if(EhOrtogonal)
		printf("é ortogonal\n");
	else
		printf("não é ortogonal\n");

}
