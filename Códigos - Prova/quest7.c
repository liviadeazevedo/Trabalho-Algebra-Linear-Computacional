#include <stdio.h>

/*

7) Construa um algoritmo que identifique se uma matriz quadrada é uma matriz banda e que informe também se uma matriz é tridiagonal.

*/


int main()
{
	int n;
	printf("Qual a ordem da matriz?\n");
	scanf("%d", &n);

	float A[n][n];
	int i, j;

    printf("Qual a matriz?\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%f", &A[i][j]);
		}
	}

	int EhBanda = 1;
	int c;
	int EhPivo0 = 0;
	int PrimeiraDiagonal0;

	for(c=1;c<n;c++)
	{
		if(A[c][0] == 0.0 && A[0][c] == 0.0)
		{
			EhPivo0 = 1;
			if(A[PrimeiraDiagonal0][0] != 0)
                PrimeiraDiagonal0 = c;
		}
		else
		{
			EhPivo0 = 0;
			PrimeiraDiagonal0 = -1;
		}

		if(EhPivo0)
		{
			if(c == n-1)
			{
				i = c;
				j = 0;
			}
			else
			{
				i = c+1;
				j = 1;
			}
			for(;i<n;i++)
			{
				if(A[i][j] != 0.0 || A[j][i] != 0.0)
				{
					EhPivo0 = 0;
					PrimeiraDiagonal0 = -1;
					break;
				}
				j++;
			}
			if(EhPivo0)
			{
				continue;
			}
		}

	}

	if(EhPivo0)
		EhBanda = 1;
	else
		EhBanda = 0;

	if(EhBanda)
	{
		printf("e banda\n");
        if(PrimeiraDiagonal0==2)
            printf("também e tridiagonal\n");
	}
	else
	{
		printf("nao e banda\n");
	}


}
