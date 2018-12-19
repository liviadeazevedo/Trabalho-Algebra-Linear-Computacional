#include <stdio.h>
#include <math.h>

/*

19) Construa um algoritmo para calcular as raízes de um polinômio característico de uma matriz de ordem maior que 2.

*/



int main()
{
    int i,j;

    double Matriz[3][3];
    double vetorLambda[3];

    printf("Qual a matriz 3x3?\n");

    for(i = 0;i < 3;i++)
    {
        for(j = 0;j < 3;j++)
        {
            scanf("%lf",&Matriz[i][j]);
        }
    }

    //Inicio do calculo do polinomio caracteristico. Sera dividido em passos:

    //Passo 1: Calcular o determinante da matriz 3x3.

    double vetorCoeficientesPolinimio[4];

    //Calculo do coeficiente 1
    vetorCoeficientesPolinimio[0] = -1;

    //Calculo do coeficiente 2
    vetorCoeficientesPolinimio[1] = Matriz[0][0] + Matriz[1][1] + Matriz[2][2];

    //Calculo do coeficiente 3

    vetorCoeficientesPolinimio[2] = Matriz[2][0] * Matriz[0][2];
    vetorCoeficientesPolinimio[2] += Matriz[2][1] * Matriz[1][2];
    vetorCoeficientesPolinimio[2] += Matriz[1][0] * Matriz[0][1];
    vetorCoeficientesPolinimio[2] -= Matriz[0][0] * Matriz[2][2];
    vetorCoeficientesPolinimio[2] -= Matriz[1][1] * Matriz[2][2];
    vetorCoeficientesPolinimio[2] -= Matriz[0][0] * Matriz[1][1];

    //Calculo do coeficiente 4

    vetorCoeficientesPolinimio[3] = Matriz[0][2] * Matriz[1][0] * Matriz[2][1];
    vetorCoeficientesPolinimio[3] += Matriz[0][1] * Matriz[1][2] * Matriz[2][0];
    vetorCoeficientesPolinimio[3] += Matriz[0][0] * Matriz[1][1] * Matriz[2][2];
    vetorCoeficientesPolinimio[3] -= Matriz[2][0] * Matriz[0][2] * Matriz[1][1];
    vetorCoeficientesPolinimio[3] -= Matriz[2][1] * Matriz[1][2] * Matriz[0][0];
    vetorCoeficientesPolinimio[3] -= Matriz[1][0] * Matriz[0][1] * Matriz[2][2];

    //Passo 2: Calcular uma raiz do polinomio.

    //Criterio de parada da iteracao
    double criterioParada;
    printf("Qual o critério de parada para o método de Newton-Raphson?\n");
    scanf("%lf",&criterioParada);

    //Valor inicial de x(k) na primeira iteracao
    double xK;
    printf("Qual o valor inicial de x para a iteração?\n");
    scanf("%lf",&xK);


    int parada = 0;// variavel de controle de parada. Quando parada = 1, a iteracao sera desfeita.
    double xKmais1 = 0; // x(k + 1)

    double derivadaFxk = 0;
    double Fxk = 0;
    double xK2; //sera a memoria do valor antigo de xK. Servira para efeito de testes de parada da iteracao
                //de Newton-Raphson.

    do
    {
        //Calcular f(x(k)): O valor do polinomino caracteristico quando (lambda) = x(k).

        Fxk += vetorCoeficientesPolinimio[0] * pow(xK,3);
        Fxk += vetorCoeficientesPolinimio[1] * pow(xK,2);
        Fxk += vetorCoeficientesPolinimio[2] * xK;
        Fxk += vetorCoeficientesPolinimio[3];

        //Calcular f'(x(k)): Usando a formula da derivada encontrada.

        derivadaFxk += vetorCoeficientesPolinimio[0] * (3 * pow(xK,2));
        derivadaFxk += vetorCoeficientesPolinimio[1] * (2 * xK);
        derivadaFxk += vetorCoeficientesPolinimio[2];

        //Calcular x(k + 1)

        xKmais1 = xK - (Fxk / derivadaFxk); //iteracao de Newton-Raphson.

        xK2 = xK; //guardar o valor antigo de xK para ver se devemos terminar a iteracao.
        xK = xKmais1; //xK sera agora o x(k + 1) na proxima iteracao.

        Fxk = 0;            //Zerar as variáveis para iniciarmos a proxima iteracao.
        derivadaFxk = 0;

        //Teste de parada: Usando a formula  de criterio de parada ja citada.
        if(fabs(xKmais1 - xK2) /fabs(xK2) <= criterioParada)
            parada = 1;


    }while(parada == 0);

    vetorLambda[0] = xKmais1; //A primeira raiz recebe o valor de x(k + 1)



    //Passo 3: Calcular as duas raizes restantes.

    //Coeficientes da equacao do 2º grau.
    double a = -1;
    double b = vetorCoeficientesPolinimio[1] - vetorLambda[0];
    double c = (-1 * pow(vetorLambda[0],2)) + (vetorLambda[0] * vetorCoeficientesPolinimio[1]) + vetorCoeficientesPolinimio[2];

    //Calculo do delta
    double delta = pow(b,2) - (4 * a * c);

    //Calculo das raizes x1 e x2
    vetorLambda[1] = (-1 * b + sqrt(delta)) / 2 * a;
    vetorLambda[2] = (-1 * b - sqrt(delta)) / 2 * a;

//------------------------------------------------------------------------------------------------------------------------
    //Resultados

    printf("Raizes do polinômio:\n");
    printf("x1 = %f\n",vetorLambda[0]);

    //Se o delta for menor que zero, a equacao do segundo grau nao tera raizes reias!

    if(delta >= 0)
    {
        printf("x2 = %f\n",vetorLambda[1]);
        printf("x3 = %f\n",vetorLambda[2]);
    }
    else
    {
        printf("Não há raizes reais para x2 e x3!\n");
    }

    return 0;
}
