#include <stdio.h>
#include <math.h>


/*

15) a) Construa um algoritmo avalie os critérios da norma, das linhas, das colunas e de Sassenfeld para um sistema Ax = b. O algoritmos deve indicar o que se concluir após aplicação de cada critério.

*/


//Funcoes para calcular normas ja usadas anteriormente.
double Norma1(double* enderecoMatriz,int ordemMatriz)
{
    int i,j,k = 0;
    double somatorio = 0;
    double norma1 = 0;
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
            somatorio += fabs(Matriz[j][i]);
        }

        if(norma1 < somatorio)
        {
            norma1 = somatorio;
        }

        somatorio = 0;
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

    //Variaveis de validacao dos criterios. Caso seus valores sejam 0, o criterio nao eh satisfeito.
    //caso contrario(valor 1), os criterios sao satisfeitos.
    int criterioLinhas = 1, criterioColunas = 1, criterioNorma = 1, criterioSassenfeld = 1;

    double somatorio = 0;

    double somatorioLinhas = 0;
    double somatorioColunas = 0;

    printf("Qual a ordem do sistema Ax = b?\n");
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

    double b[n];
    printf("Qual o vetor b?\n");

    for(i = 0;i < n;i++)
    {
        scanf("%lf",&b[i]);
    }

    //Aplicar o criterio das linhas

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
             //nao somamos elementos da diagonal.
            if(i != j)
            {
                somatorioLinhas += fabs(A[i][j]);
            }
        }
        //Se o somatorio linha i for maior ou igual ao valor absoluto de aii,
        //o criterio das linhas nao eh satisfeito.
        if(somatorioLinhas >= fabs(A[i][i]))
        {
            criterioLinhas = 0;
            break;
        }

        somatorioLinhas = 0;
    }

    //Criterio das colunas

    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            //nao somamos elementos da diagonal.
            if(i != j)
            {
                somatorioColunas += fabs(A[j][i]);
            }
        }

        //Se o somatorio coluna i for maior ou igual ao valor absoluto de aii,
        //o criterio das colunas nao eh satisfeito.
        if(somatorioColunas >= fabs(A[i][i]))
        {
            criterioColunas = 0;
            break;
        }

        somatorioColunas = 0;
    }

    //Criterio de Sassenfeld

    double beta[n]; //vetor que guarda os valores dos betas.
    double maxBeta = 0; //maior valor de beta.

    //Inicio da aplicação da formula do criterio de Sassenfeld

    //Calculo do beta[0](primeiro beta)
    for(j = 0;j < n;j++)
    {
        //Nao se pode somar o elemento da diagonal ii no calculo do beta(i).
        if(j != 0)
            somatorio += fabs(A[0][j]);
    }

    beta[0] = somatorio / fabs(A[0][0]);
    somatorio = 0; //reinicio da variavel para o calculo do proximo beta.

    for(i = 1;i < n;i++)
    {
        //Serve para eliminar o problema dos calculos do somatorio com os betas.
        //Em outras palavras: "Não temos no calculo do beta(i) a operação aji * beta(i), temos aji. Para
        //eliminar este problema, atribuimos ao beta(i) o valor de 1, pois todo numero multiplicado por 1 eh
        //ele mesmo."
        beta[i] = 1;

        for(j = 0;j < n;j++)
        {
            //Nao se pode somar o elemento da diagonal ii no calculo do beta(i).
            if(i != j)
                somatorio += fabs(A[i][j]) * beta[j];
        }

        beta[i] = somatorio / fabs(A[i][i]);
        somatorio = 0;//reiniciando a variavel para o calculo do proximo beta.
    }

    //Comparacao para ver quem eh o maior valor de beta.
    for(i = 0;i < n;i++)
    {
        if(beta[i] > maxBeta)
            maxBeta = beta[i];
    }

    //Se o maior valor de beta for >= 1, o criterio de Sassenfeld nao eh cumprido.
    if(!(maxBeta < 1))
        criterioSassenfeld = 0;

    //Criterio da Norma

    double B[n][n];

    //Pelo raciocenio, o valor de x(k) quando calculamos o valor de x(k) em função de x(k - n),...,x(k - 1),x(k),x(k + 1),...,
    //x(k + n) sera sempre zero, devido a definicao dos metodos iterativos.
    //Isso representa que os elementos da diagonal da matriz B sempre serão zero, pois x = Bx + g.
    for(i = 0;i < n;i++)
    {
        B[i][i] = 0;
    }

    //Calculando so valores de B.
    //Esta parte representa o processo de isolamento da variavel x(k) em funcao das outras variaveis x.
    //A matriz B representa o valor dos coeficientes das variaveis x quando serao usadas no calculo da variavel x(k).
    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            if(i != j)
                B[i][j] = -1 * (A[i][j] / A[i][i]);
        }
    }
    //Endereco para a passagem para as funcoes.
    double* enderecoB = &B[0][0];

    // Validacao do criterio da norma: Para qualquer norma de B, temos ||B|| < 1. Se ocorre o contrario, o criterio nao
    //eh satisfeito.
    if((Norma1(enderecoB,n) >= 1) && (NormaInfinito(enderecoB,n) >= 1) && (NormaFrobenius(enderecoB,n) >= 1))
        criterioNorma = 0;

    //Resultados
    //Estaremos aqui comparando cada criterio com seu respectivo metodo iterativo.

    if(criterioLinhas == 1 || criterioColunas == 1)
        printf("O critério das linhas e colunas convergem.Então, o método de Jacobi e Gauss-Seidel convergem.\n");
    else
        printf("Os critérios de linhas ou colunas não convergem. Não podemos afirmar com certeza que o método de Jacobi e Gauss-Seidel convergem.\n");

    if(criterioSassenfeld == 1)
        printf("O critério de Sassenfeld é satisfeito. Então, o método de Gauss-Seidel converge.\n");
    else
        printf("O critério de Sassenfeld não é satisfeito. Não podemos afirmar com certeza que o método de Gauss-Seidel converge.\n");

    if(criterioNorma == 1)
        printf("O critério da norma é satisfeito. Portanto o método iterativo com a matriz B converge.\n");
    else
        printf("O critério da norma não é satisfeito.Não podemos afirmar que o método iterativo com a matriz B converge.\n");

    return 0;
}
