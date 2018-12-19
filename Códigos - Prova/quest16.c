#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


/*

16) Construa um algoritmo que resolva o sistema Ax = b usando o método SOR.

*/



/*Como gerar numeros aleatorios em ponto flutuante:
  Seja ]a;b[ o intervalo com o qual se deseja gerar o conjunto de numeros aletorios.
  Entao, o "aleatorio" gerado sera igual a:
                a + (b - a) * ((double)(rand())/RAND_MAX)
    Com isso, geraremos numeros de ponto flutuante aleatorios no intervalo ]a;b[.
*/

//Ira realizar o metodo SOR
void MetodoSOR(double*matrizA,double*matrizB,double criterioParada,int ordemSistema)
{
    int i,j,h,k = 0; //variaveis de iteracao
    double A[ordemSistema][ordemSistema];
    double b[ordemSistema];

    //Receber os elementos da matriz A
    for(i = 0; i < ordemSistema;i++)
    {
        for(j = 0; j < ordemSistema; j++)
        {
            A[i][j] = *(matrizA + k);
            k++;
        }
    }

    //Receber os elementos do vetor b
    for(i = 0; i < ordemSistema; i++)
    {
        b[i] = *(matrizB + i);
    }

    double xK[ordemSistema]; //x(k)
    double xKmais1[ordemSistema]; //x (k + 1)
    double xK2[ordemSistema]; //Servira para guardar os valores de x(k) depois que a iteracao i for feita.
                    //Necessario para o caculo do criterio de parada.

    printf("Escolha a solução inicial para a iteração SOR:\n");

    for(i = 0;i < ordemSistema;i++)
    {
        scanf("%lf",&xK[i]);
        xK2[i] = xK[i]; //para guardar o valor inicial de xK para realizar o teste de parada.
    }

    //Implementação do metodo SOR.

    //Agora, iremos estimar o omega otimo. Como a matriz eh positiva definida, podemos afirmar
    //que o omega esta entre 0 < w < 2. Usaremos a funcao de gerador de numeros aleatorios do C
    //para obter um numero "aleatorio" entre 0 e 2.

    double w;

    srand((double)time(NULL));
    w = 2 * ((double)(rand())/RAND_MAX);

    printf("w que será usado: %f\n",w);


    //Com o omega, iniciaremos a iteracao do metodo SOR.

    int parada = 0; //Varavel que ira controlar o loop do algoritmo.
                    //Quando parada == 1, o loop "while" eh rompido.

    while(parada == 0)
    {
        //Calculo de cada valor de x(k + 1) na iteracao, considerando o isolamento de cada x em cada linha do sistema.
        for(i = 0;i < ordemSistema;i++)
        {
            xKmais1[i] = b[i];

            for(j = 0;j < ordemSistema;j++)
            {
                if(j != i)
                {
                    xKmais1[i] += -1 * (A[i][j] * xK[j]);
                }
            }

            xKmais1[i] = xKmais1[i] / A[i][i];

            //Nesta parte em exato, encontramos a diferenca do método SOR. O uso
            //de uma constante w para acelerar o processo. Afirmamos que o metodo SOR
            //seria apenas o metodo de Gauss-Seidel melhorado. O Gauss-Seidel eh o SOR
            //considerando w = 1.
            //-----------------------------------------------------------------
            xKmais1[i] *= w; //multiplicando o w como diz a formula.
            xKmais1[i] += (1 - w) * xK[i]; // somando com (1 - w) * x(k) como diz a formula.
            //--------------------------------------------------------------------

            xK2[i] = xK[i]; //guardar o valor da iteracao k para efeito de teste de parada.
            xK[i] = xKmais1[i]; //x(k) sera x(k + 1) para ser usado na mesma iteracao.Nesta linha encontramos
            //uma semalhanca com o Gauss-Seidel, pois atualizamos o valor de x(k) na mesma iteracao.
        }

        for(h = 0;h < ordemSistema;h++)
        {
         //se x(k) for diferente de 0, iremos verificar o criterio de parada.
            if(xK2[h] != 0)
            {
                //Se cumprirmos a condicao, a iteracao sera continuada.
                if((fabs(xKmais1[h] - xK2[h]) / fabs(xK2[h])) > criterioParada)
                {
                    break;
                }
            }

            //Se chegarmos no ultimo valor de x e o loop nao for rompido, entao podemos dizer
            //que o criterio de parada foi cumprido e sairemos do loop principal.
            if(h == ordemSistema - 1 && xK2[h] != 0)
            {
                parada = 1;
            }
        }
    }

    //Resultado(solucao aproximada do sistema)

    printf("Solução aproximada:\n");

    for(i = 0;i < ordemSistema;i++)
    {
        printf("x[%d] = %f\n",i,xKmais1[i]);
    }
};

int main()
{
    int i,j,n;

    printf("Qual a ordem do sistema?\n");
    scanf("%d",&n);

    double A[n][n];
    printf("Qual a matriz A positiva definida?\n");

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

    double criterioParada;

    printf("Escolha um valor de critério de parada do algoritmo:\n");
    scanf("%lf",&criterioParada);

    //Endereco de A e b para enviar a função que realizara o metodo SOR.
    double* enderecoA = &A[0][0];
    double* enderecoB = &b[0];

    //Funcao que executara o método SOR
    MetodoSOR(enderecoA,enderecoB,criterioParada,n);

    return 0;
}
