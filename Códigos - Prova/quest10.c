#include <stdio.h>
#include <math.h>


/*

10) Construa um algoritmo que receba o número condição de uma matriz A calculado pela função cond do matlab e que retorne o valor da norma 1, infinito e de Frobenius da matriz inversa de A.

*/


double Norma1(double* enderecoMatriz,int ordemMatriz)
{
    int i,j,k = 0; //variaveis de iteracao
    double somatorio = 0; //variavel para realizar o somatorio
    double norma1 = 0; //valor da norma 1
    double Matriz[ordemMatriz][ordemMatriz];

    //Necessario para passarmos os elementos da matriz A
    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            Matriz[i][j] = *(enderecoMatriz + k);
            k++;
        }
    }

    //Logica da norma 1: Maior soma dos elementos em modulo de cada coluna.
    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            somatorio += fabs(Matriz[j][i]);
        }

        if(norma1 < somatorio)
        {
            norma1 = somatorio;
        }

        somatorio = 0; //zera-se para iniciar a soma de uma nova coluna.
    }

    return norma1;
};

double NormaInfinito(double* enderecoMatriz,int ordemMatriz)
{
    int i,j,k = 0;
    double somatorio = 0;
    double normaInfinito = 0;
    double Matriz[ordemMatriz][ordemMatriz];

    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            Matriz[i][j] = *(enderecoMatriz + k);
            k++;
        }
    }

    //Logica da norma infinito: Maior soma dos elementos em modulo de cada linha
    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            somatorio += fabs(Matriz[i][j]);
        }

        if(normaInfinito < somatorio)
        {
            normaInfinito = somatorio;
        }

        somatorio = 0;
    }

    return normaInfinito;
};


double NormaFrobenius(double* enderecoMatriz,int ordemMatriz)
{
    int i,j,k = 0;
    double somatorio = 0;
    double normaFrobenius = 0;
    double Matriz[ordemMatriz][ordemMatriz];

    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            Matriz[i][j] = *(enderecoMatriz + k);
            k++;
        }
    }

    //Logica da norma Frobenius: A raiz quadrada da soma dos elementos da matriz em modulo ao quadrado.
    //Obs: pow(x,n) = funcao que retorna x elevado n.
    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            somatorio += pow(fabs(Matriz[i][j]),2);
        }
    }

    normaFrobenius = sqrt(somatorio);

    return normaFrobenius;
};

int main()
{
    int i,j,n;
    double numeroCondicaoNorma1, numeroCondicaoNormaFrobenius,numeroCondicaoNormaInfinito;

    printf("Qual a ordem da matriz A?\n");
    scanf("%d",&n);

    double A[n][n];

    printf("Qual a matriz A?\n");

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            scanf("%lf",&A[i][j]);
        }
    }

    printf("Qual o número condição na norma 1 de A(retirado do matlab)?\n");
    scanf("%lf",&numeroCondicaoNorma1);

    printf("Qual o número condição na norma infinito de A(retirado do matlab)?\n");
    scanf("%lf",&numeroCondicaoNormaInfinito);

    printf("Qual o número condição na norma de frobenius de A(retirado do matlab)?\n");
    scanf("%lf",&numeroCondicaoNormaFrobenius);

    //Calculo das normas da matriz inversa

    double matrizInversaNorma1, matrizInversaNormaFrobenius, matrizInversaNormaInfinito;
    double norma1A,normaFrobeniusA,normaInfinitoA;

    //Necessario para enviar a matriz A para as funcoes que calcularao as normas.
    /*Obs: Nao eh possivel realizar a passagem de matriz de ordem nao constante por passegem por valor,
    apenas por referencia, por isso estamos usando ponteiros para realizar a passagem por referencia.*/
    double* enderecoA;
    enderecoA = &A[0][0];

    //Calculando as normas da matriz A.
    norma1A = Norma1(enderecoA,n);
    normaFrobeniusA = NormaFrobenius(enderecoA,n);
    normaInfinitoA = NormaInfinito(enderecoA,n);

    //Calculando as normas da matriz inversa, utilizando a formula: ||A-¹|| = cond(A) / ||A||

    matrizInversaNorma1 = numeroCondicaoNorma1 / norma1A;
    matrizInversaNormaFrobenius = numeroCondicaoNormaFrobenius / normaFrobeniusA;
    matrizInversaNormaInfinito = numeroCondicaoNormaInfinito / normaInfinitoA;

    //Resultados

    printf("Matriz inversa:\n");

    printf("Norma 1 = %f\n",matrizInversaNorma1);
    printf("Norma de Frobenius = %f\n",matrizInversaNormaFrobenius);
    printf("Norma infinito = %f\n",matrizInversaNormaInfinito);

    return 0;
}
