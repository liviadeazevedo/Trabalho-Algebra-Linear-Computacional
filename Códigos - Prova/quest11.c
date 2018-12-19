#include <stdio.h>
#include <math.h>


/*

11) Construa um algoritmo que calcule um limitante inferior do número condição. Use a equação (2.2.28). Dê um exemplo de aplicação do seu algoritmo usando uma matriz de Hilbert.

*/


//Funcoes que calculam as normas de vetor ou matriz.

double Norma1Vetor(double* vetor,int tamanhoVetor)
{
    double norma1 = 0; // resultado da norma 1
    int i = 0; //variavel de iteracao

    //Logica da norma 1 de vetor: resultado da soma de todos os elementos em modulo do vetor
    for(i = 0;i < tamanhoVetor;i++)
    {
        norma1 += fabs(vetor[i]);
    }

    return norma1;
};

double NormaInfinitoVetor(double* vetor,int tamanhoVetor)
{
    double normaInfinito = 0;
    int i = 0;

    //Logica da norma infinito: Maior elemento em modulo do vetor.
    for(i = 0;i < tamanhoVetor;i++)
    {
        if(fabs(vetor[i]) > normaInfinito)
        {
            normaInfinito = fabs(vetor[i]);
        }
    }

    return normaInfinito;
};

//Mesma funcao usada na questao 10
double Norma1Matriz(double* enderecoMatriz,int ordemMatriz)
{
    int i,j,k = 0;
    double somatorio = 0;
    double norma1 = 0;
    double Matriz[ordemMatriz][ordemMatriz];

    //Necessario para a funcao receber todos os elementos da matriz passada como parametro.
    for(i = 0; i < ordemMatriz;i++)
    {
        for(j = 0; j < ordemMatriz; j++)
        {
            Matriz[i][j] = *(enderecoMatriz + k);
            k++;
        }
    }

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

        somatorio = 0; //necessario para o somatorio ser reutilizado.
    }

    return norma1;
};

//Mesma funcao usada na questao 10
double NormaInfinitoMatriz(double* enderecoMatriz,int ordemMatriz)
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

int main()
{
    int i,j,n;
    double numeroCondicaoAproximadoNorma1,numeroCondicaoAproximadoNormaInfinito;

    printf("Qual a ordem da matriz?\n");
    scanf("%d",&n);

    double Matriz[n][n];

    printf("Qual a matriz?\n");

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            scanf("%lf",&Matriz[i][j]);
        }
    }

    double MatrizInversa[n][n];

    printf("Entre com a matriz inversa obtida no Matlab\n");

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            scanf("%lf",&MatrizInversa[i][j]);
        }
    }

    double w[n]; //vetor w qualquer

    printf("Entre com um vetor w qualquer,com exceção do vetor nulo, para o cálculo do limitante inferior\n");

    for(i = 0;i < n;i++)
    {
        scanf("%lf",&w[i]);
    }

    //Multiplicação da matriz inversa com o vetor w
    //Mesmo raciocinio retirado da questao numero 1.

    double MatrizResultadoInversaW[n]; //Resultado da multiplicacao entre a inversa e w.

    //Zerar todos os elementos para eliminar os numeros de memoria contidos na variavel.
    for(j = 0;j < n;j++)
    {
        MatrizResultadoInversaW[j] = 0;
    }

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            MatrizResultadoInversaW[i] += MatrizInversa[i][j] * w[j];
        }
    }

    //Variaveis de endereco necessarias para serem enviadas para as funcoes para o calculo das normas.
    double* enderecoMatriz = &Matriz[0][0];
    double* enderecoMatrizInversaW = &MatrizResultadoInversaW[0];
    double* enderecoW = &w[0];

    //Calculando o limitante inferior do número condicao, de acordo com a formula dada 2.2.28 no livro.

    numeroCondicaoAproximadoNorma1 = Norma1Matriz(enderecoMatriz,n) * Norma1Vetor(enderecoMatrizInversaW,n) / Norma1Vetor(enderecoW,n);
    numeroCondicaoAproximadoNormaInfinito = NormaInfinitoMatriz(enderecoMatriz,n) * NormaInfinitoVetor(enderecoMatrizInversaW,n) / NormaInfinitoVetor(enderecoW,n);

    //Resultados

    printf("O número condição é maior ou igual a %f na norma 1\n",numeroCondicaoAproximadoNorma1);
    printf("O número condição é maior ou igual a %f na norma infinito\n",numeroCondicaoAproximadoNormaInfinito);

    return 0;
}
