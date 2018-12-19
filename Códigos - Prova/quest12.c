#include <stdio.h>
#include <math.h>


/*

12) Implemente um algoritmo para calcular o que foi desenvolvido no exemplo 2.4.2

*/


//Funcao da norma 2 de um vetor ja aplicada em exercicios anteriores.
double Norma2(double* vetor,int tamanhoVetor)
{
    double norma2 = 0;
    int i = 0;

    for(i = 0;i < tamanhoVetor;i++)
    {
        norma2 += pow(fabs(vetor[i]),2);
    }

    norma2 = sqrt(norma2);

    return norma2;
};

int main()
{
    int i,j,ordem;

    printf("Qual a ordem do sistema?\n");
    scanf("%d",&ordem);

    double A[ordem][ordem];

    printf("Qual a matriz do sistema?\n");
    for(i = 0; i < ordem;i++)
    {
        for(j = 0;j < ordem;j++)
        {
            scanf("%lf",&A[i][j]);
        }
    }

    double b[ordem];

    printf("Qual o vetor b do sistema?\n");
    for(i = 0;i < ordem;i++)
    {
        scanf("%lf",&b[i]);
    }

    double xhat[ordem];

    printf("Qual a solução aproximada obtida no matlab?\n");

    for(i = 0;i < ordem;i++)
    {
        scanf("%lf",&xhat[i]);
    }

    double numeroCondicaoNorma2;

    printf("Qual o numero condição da norma 2,obtido no matlab, da matriz do sistema?\n");
    scanf("%lf",&numeroCondicaoNorma2);

    //Enderecos da matriz e vetor para serem passados para a funcao.
    double* enderecoB = &b[0];
    double* enderecoA = &A[0][0];

    //Incio dos calculos

    double residuoHat[ordem];

    double vetorResultado[ordem];

    //Calculo do residuohat.

    //Calculando A * xhat

    //Mulplicacao de matriz com vetor

    for(j = 0;j < ordem;j++)
    {
        vetorResultado[j] = 0;
    }

    for(i = 0;i < ordem;i++)
    {
        for(j = 0;j < ordem;j++)
        {
            vetorResultado[i] += A[i][j] * xhat[j];
        }
    }

    //Calculo final do residuohat rhat = b - A*xhat

    for(i = 0;i < ordem;i++)
    {
        residuoHat[i] = b[i] - vetorResultado[i];
    }

    //Mesma ideia para o enderecoA e enderecoB.
    double* enderecoResiduohat = &residuoHat[0];

    //Calculo da proximidade de xhat da solucao real(a sua precisao de acordo com a solucao real)
    double precisaoXhatNorma2;

    //Aplicacao da formula.
    precisaoXhatNorma2 = (numeroCondicaoNorma2 * Norma2(enderecoResiduohat,ordem)) / Norma2(enderecoB,ordem);

    //Avaliacao do resultado.

    printf("Precisao na norma 2 da solução x aproximada: %f\n",precisaoXhatNorma2);

    //O usuario pode inserir um valor de precisao aceitavel para avaliar se a solucao aproximada eh boa ou nao para
    //ele.

    double nivelPrecisaoAceitavel;

    printf("Insira um valor de precisão, que ao seu ver, é bom para a solução aproximada:\n");
    scanf("%lf",&nivelPrecisaoAceitavel);

    //Analise das precisoes
    //Se o nivel de precisao encontrado for menor ou igual ao desejado, a solucao eh adequada.
    if(precisaoXhatNorma2 <= nivelPrecisaoAceitavel)
        printf("Usando a norma 2, a solução aproximada é uma boa aproximação para seu caso\n");
    else
        printf("Usando a norma 2, a solução aproximada é uma ruim aproximação para seu caso\n");

    return 0;
}
