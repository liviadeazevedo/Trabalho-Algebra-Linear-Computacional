#include <stdio.h>
#include <math.h>


/*

6) a) Construa um algoritmo que avalie que receba uma matriz A(mxn) e calcule uma matriz C que é o produto da matriz A transposta pela própria matriz A. Encontre o fator de Cholesky da matriz C. Use o comando chol do matlab para exibir o fator de Cholesky.
    b) Usando o que foi desenvolvido no item anterior, resolva um sistema Ax = b  

*/


int main()
{
    int m,n,k,i,j;
    double somatorio = 0;

    printf("Qual a dimensao m da matriz?\n");
    scanf("%d",&m);
    printf("Qual a dimensao n da matriz?\n");
    scanf("%d",&n);

    printf("Qual a matriz?(de preferência uma matriz inversível)\n");

    double Matriz[m][n];

    for(i = 0;i < m;i++)
    {
        for(j = 0;j < n;j++)
        {
            scanf("%lf",&Matriz[i][j]);
        }
    }

    double MatrizTranposta[n][m];

    for(i = 0; i < n;i++)
    {
        for(j = 0;j < m;j++)
        {
            MatrizTranposta[i][j] = Matriz[j][i];
        }
    }

    double C[n][n];

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            C[i][j] = 0;
        }
    }

    //Processo da multiplicacao de matrizes(A^T * A).

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            for(k = 0;k < m;k++)
            {
                C[i][j] += MatrizTranposta[i][k] * Matriz[k][j];
            }
        }
    }

    printf("Matriz C:\n");

    for(i = 0; i < n;i++)
    {
        for(j = 0; j < n;j++)
        {
            printf("%f  ",C[i][j]);
        }

        printf("\n");
    }

    double fatorCholesky[n][n];

    //Zerar os valores de memoria da variavel.("Inicializar" a variavel)
    for(i = 0; i < n;i++)
    {
        for(j = 0; j < n;j++)
        {
            fatorCholesky[i][j] = 0;
        }
    }

    //Passo 1: Determinar os primeiros elementos de cholesky (Formula 1):
    //Obs: funcao pow(x,n) = x elevado a n.

    fatorCholesky[0][0] = sqrt(C[0][0]);

    for(j = 1;j < n;j++)
    {
        fatorCholesky[0][j] = C[0][j] / fatorCholesky[0][0];
    }

    //Passo 2: Calcular os elementos r[i][i] de Cholesky (Formula 2):

    for(i = 1; i < n;i++)
    {
        for(k = 0;k < i;k++)
        {
            somatorio += pow(fatorCholesky[k][i],2);
        }

        fatorCholesky[i][i] = C[i][i] - somatorio;
        fatorCholesky[i][i] = sqrt(fatorCholesky[i][i]);
        somatorio = 0; //zerar para iniciar o somatório da proxima parcela.

    //Com todos os elementos r[i][i] determinados,podemos calcular os r[i][j] (Formula 3):
        for(j = i + 1;j < n;j++)
        {
            for(k = 0; k < i;k++)
            {
                somatorio += fatorCholesky[k][i] * fatorCholesky[k][j];
            }

            fatorCholesky[i][j] = C[i][j] - somatorio;
            fatorCholesky[i][j] = fatorCholesky[i][j] / fatorCholesky[i][i];
            somatorio = 0; //zerar para iniciar o somatorio da proxima parcela.
        }

    }

    //Mostrar o fator de Cholesky da matriz C
    printf("Fator de Cholesky:\n");

    for(i = 0; i < n;i++)
    {
        for(j = 0; j < n;j++)
        {
            printf("%f  ",fatorCholesky[i][j]);
        }

        printf("\n");
    }

    //Passo para determinar um sistema Ax = b com a fatoracao de Cholesky

    printf("Digite a matriz B para resolver um sistema Ax = B com Cholesky:\n");
    double B[n];

    for(i = 0;i < n;i++)
    {
        scanf("%lf",&B[i]);
    }

    double x[n];
    double y[n];
    double transpostaCholesky[n][n];

    //Determinar a transposta de Cholesky(R^T)
    for(i = 0; i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            transpostaCholesky[i][j] = fatorCholesky[j][i];
        }
    }

    //Resolvendo Ax = B ------> R^T * Rx = B:

    //Primeira parte: R^T * y = B;
    //Mesma logica usada na questao 5 da prova.

     y[0] = B[0] / transpostaCholesky[0][0];

    for(i = 0;i <= n - 1;i++)
    {
        for(j = 0; j <= i;j++)
        {
            if(j < i)
            {
                B[i] -= transpostaCholesky[i][j] * y[j];
            }
            else
            {
                B[i] = B[i] / transpostaCholesky[i][j];

            }
        }

        y[i] = B[i];
    }

    //Segunda parte: Resolver Rx = y;
    //Mesma logica usada na questao 4 da prova.

    x[n - 1] = y[n - 1] / fatorCholesky[n - 1][n - 1];

    for(i = n - 1;i >= 0;i--)
    {
        for(j = n - 1; j >= i;j--)
        {
            if(j > i)
            {
                y[i] -= fatorCholesky[i][j] * x[j];
            }
            else
            {
                y[i] = y[i] / fatorCholesky[i][j];

            }
        }

        x[i] = y[i];
    }

    //Resultados
    printf("Solução do sistema:\n");

    for(i = 0;i < n;i++)
    {
        printf("x_%d = %f\n",i,x[i]);
    }

    return 0;
}
