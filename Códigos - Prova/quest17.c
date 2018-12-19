#include <stdio.h>
#include <math.h>


/*

17) Construa um algoritmo que calcule o w ótimo e resolva o sistema Ax = b, onde A é uma matriz 3x3, positiva definida e tridiagonal. 

*/


int main()
{
    int i,j,h;

    double A[3][3];
    printf("Qual a matriz A de ordem 3,positiva definida e tridiagonal?\n");

    for(i = 0;i < 3;i++)
    {
        for(j = 0;j < 3;j++)
        {
            scanf("%lf",&A[i][j]);
        }
    }

    double b[3];
    printf("Qual o vetor b?\n");

    for(i = 0;i < 3;i++)
    {
        scanf("%lf",&b[i]);
    }

    double xK[3]; //x(k)
    double xKmais1[3]; //x (k + 1)
    double xK2[3]; //Servira para guardar os valores de x(k) depois que a iteracao i for feita.
                    //Necessario para o caculo do criterio de parada.

    printf("Escolha a solução inicial para a iteração SOR:\n");

    for(i = 0;i < 3;i++)
    {
        scanf("%lf",&xK[i]);
        xK2[i] = xK[i]; //para guardar o valor inicial de xK para realizar o teste de parada.
    }

    double p;

    printf("Escolha um valor de critério de parada do algoritmo:\n");
    scanf("%lf",&p);

    //Implementacao do metodo SOR.

    //Aplicacao da formula generica.
    double pTj = 0;

    pTj += (A[2][1] * A[1][2]) / (A[2][2] * A[1][1]);
    pTj += (A[1][0] * A[0][1]) / (A[1][1] * A[0][0]);
    pTj = sqrt(pTj);

    //Agora, iremos calcular o omega otimo atraves de sua formula.

    double w = 0;

    w = 2 / (1 + sqrt(1 - (pTj * pTj)));

    printf("w = %f\n",w);

//-----------------------------------------------------------------------------------------------------------------
    //Com o omega, iniciaremos a iteracao do metodo SOR.

    int parada = 0;//Varavel que ira controlar o loop do algoritmo.
                    //Quando parada == 1, o loop "while" é rompido.

    while(parada == 0)
    {
        //Calculo de cada valor de x(k + 1) na iteracao, considerando o isolamento de cada x em cada linha do sistema.
        for(i = 0;i < 3;i++)
        {
            xKmais1[i] = b[i];

            for(j = 0;j < 3;j++)
            {
                if(j != i)
                {
                    xKmais1[i] += -1 * (A[i][j] * xK[j]);
                }
            }

            xKmais1[i] = xKmais1[i] / A[i][i];

            //Nesta parte em exato, encontramos a diferenca do metodo SOR. O uso
            //de uma constante w para acelerar o processo. Afirmamos que o metodo SOR
            //seria apenas o metodo de Gauss-Seidel melhorado. O Gauss-Seidel eh o SOR
            //considerando w = 1.
            //--------------------------------------------------
            xKmais1[i] *= w;//multiplicando o w como diz a formula.
            xKmais1[i] += (1 - w) * xK[i];// somando com (1 - w) * x(k) como diz a formula.
            //--------------------------------------------------


            xK2[i] = xK[i]; //guardar o valor da iteracao k para efeito de teste de parada.
            xK[i] = xKmais1[i]; //x(k) sera x(k + 1) para ser usado na mesma iteracao.Nesta linha encontramos
            //uma semalhanca com o Gauss-Seidel, pois atualizamos o valor de x(k) na mesma iteracao.
        }

        for(h = 0;h < 3;h++)
        {
             //se x(k) for diferente de 0, iremos verificar o criterio de parada.
            if(xK2[h] != 0)
            {
                //Se cumprirmos a condicao, a iteracao sera continuada.
                if((fabs(xKmais1[h] - xK2[h]) / fabs(xK2[h])) > p)
                {
                    break;
                }
            }

            //Se chegarmos no eltimo valor de x e o loop nao for rompido, entao podemos dizer
            //que o criterio de parada foi cumprido e sairemos do loop principal.
            if(h == 2 && xK2[h] != 0)
            {
                parada = 1;
            }
        }
    }
//-------------------------------------------------------------------------------------------------------------------------
    //Resultado(solucao aproximada do sistema)

    printf("Solução aproximada:\n");

    for(i = 0;i < 3;i++)
    {
        printf("x[%d] = %f\n",i,xKmais1[i]);
    }

    return 0;
}
