#include <stdio.h>
#include <math.h>


/*

  c) O algoritmo deve resolver o sistema Ax=b usando o método de Gauss-Seidel.

*/


int main()
{
    int i,j,h,n;

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

    double xK[n]; //x(k)
    double xKmais1[n]; //x (k + 1)
    double xK2[n]; //Servira para guardar os valores de x(k) depois que a iteracao i for feita.
                    //Necessario para o caculo do criterio de parada.

    printf("Escolha a solução inicial para a iteração de Gauss-Seidel:\n");

    for(i = 0;i < n;i++)
    {
        scanf("%lf",&xK[i]);
        xK2[i] = xK[i]; //para guardar o valor inicial de xK para realizar o teste de parada.
    }

    double p; //valor do criterio de parada

    printf("Escolha um valor de critério de parada do algoritmo:\n");
    scanf("%lf",&p);

    //Implementacao do metodo de Gauss-Seidel

    int parada = 0; //Varavel que ira controlar o loop do algoritmo.
                    //Quando parada == 1, o loop "while" eh rompido.

    while(parada == 0)
    {
        //Calculo de cada valor de x(k + 1) na iteracao, considerando o isolamento de cada x em cada linha do sistema.
        for(i = 0;i < n;i++)
        {
            xKmais1[i] = b[i];

            for(j = 0;j < n;j++)
            {
                //Se j == i, estaremos usando o valor de xj para calcular xj, sendo algo sem sentido.
                if(j != i)
                {
                    xKmais1[i] += -1 * (A[i][j] * xK[j]);
                }
            }

            xKmais1[i] = xKmais1[i] / A[i][i];
            xK2[i] = xK[i]; //guardar o valor da iteracao k para efeito de teste de parada.
            xK[i] = xKmais1[i]; //x(k) sera x(k + 1) para ser usado na mesma iteracao.Nesta linha nos diferenciamos do
                                //metodo de Jacobi, pois atualizamos o valor de x(k) na mesma iteracao.
        }

        for(h = 0;h < n;h++)
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

            //Se chegarmos no ultimo valor de x e o loop nao for rompido, entao podemos dizer
            //que o criterio de parada foi cumprido e sairemos do loop principal.
            if(h == n - 1 && xK2[h] != 0)
            {
                parada = 1;
            }
        }
    }

    //Resultado(solucao aproximada do sistema)

    printf("Solução aproximada:\n");

    for(i = 0;i < n;i++)
    {
        printf("x[%d] = %f\n",i,xKmais1[i]);
    }

    return 0;
}
