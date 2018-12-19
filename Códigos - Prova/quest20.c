#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


/*

20) Implemente uma heurística de colônia de morcegos para resolver um sistema Ax = b.  

*/



//Estrutura contendo os elementos da PSO de um morcego.
//Obs: Iremos trabalhar as informacoes do morcegos com ponteiro, ou seja, para podermos atribuir
//valores a eles, precisaremos dar-lhes os enderecos das matrizes onde estarão amarzenadas os vetores
//de posicao, velocidade e melhor posicao de cada morcego.
typedef struct{

    double* posicao;
    double* melhorPosicao;
    double* velocidade;
    double funcaoFitness;
    double melhorFuncaoFitness;

} Morcego;

//Calcuclar a funcao de fitness de um morcego.
double CalcularFuncaoFitness(Morcego morcego, double* enderecoA,double* enderecoB,int ordem)
{
    int i,j,k = 0,h = 0; //em geral trabalharemos com essas variaveis para fazer os loops e
                         //para varer cada valor dos vetores que o morcego contem
                         //(posicao,velocidade,melhor posicao).
    double somatorio = 0;
    double A[ordem][ordem];
    double b[ordem];

    for(i = 0; i < ordem;i++)
    {
        for(j = 0; j < ordem; j++)
        {
            A[i][j] = *(enderecoA + k);
            k++;
        }
    }

    for(i = 0; i < ordem; i++)
    {
        b[i] = *(enderecoB + i);
    }

    morcego.funcaoFitness = 0;

    for(i = 0;i < ordem;i++)
    {
        somatorio += b[i];

        for(j = 0;j < ordem;j++)
        {
            somatorio -= *(morcego.posicao + h) * A[i][j];
            h++;
        }

            h = 0; //variavel necessaria para varrer os vetores dos morcegos.
                    //se zera aqui para iniciar uma nova varredura.

            morcego.funcaoFitness += fabs(somatorio);
            somatorio = 0; //somar a diferenca da proxima equacao do sistema.
        }

    return morcego.funcaoFitness;
};

/*Como gerar numeros aleatorios em ponto flutuante:
  Seja ]a;b[ o intervalo com o qual se deseja gerar o conjunto de numeros aletorios.
  Então, o "aleatorio" gerado sera igual a:
                a + (b - a) * ((double)(rand())/RAND_MAX)
    Com isso, geraremos numeros de ponto flutuante aleatorios no intervalo ]a;b[.
*/

int main()
{
    int i,j,k = 0,h = 0; //variaveis de iteracao
    int ordem; //ordem do sistema.

    srand((double)time(NULL)); //gerador de semente, para gerarmos sequencias de
                                //numeros aleatorios diferentes a cada vez que o
                                //programa for iniciado.

    printf("Qual a ordem do sistema?\n");
    scanf("%d",&ordem);

    double A[ordem][ordem];

    printf("Qual a matriz A do sistema?\n");
    for(i = 0;i < ordem;i++)
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

    //Necessario para obtermos a matriz A e b nas funcoes que futuramente
    //iremos utilizar em nossos calculos.
    double* enderecoA = &A[0][0];
    double* enderecoB = &b[0];

    //Criando os "morcegos"
    //Obs: A funcao round() retorna o valor arredondado do parametro fornecido.
    //Neste caso, a quantidade de morcegos sera igual a 30% do numero de equacoes existentes.
    int quantidadeDeMorcegos = round(0.3 * ordem);

    //Usaremos no minimo 2 morcegos para a iteracao, caso os 30% do numero de equacoes
    //seja menor que 2.
    if(quantidadeDeMorcegos < 2)
        quantidadeDeMorcegos = 2;

        //Cada linha da matriz das caracteristicas de cada morcego
        //ira representar o numero do morcego; as colunas irao
        //representar os valores contidos no vetor daquele morcego.
        //Essas matrizes seriam como se fossem "Banco de Dados" para
        //amarzenar essas informacoes.

    Morcego morcegos[quantidadeDeMorcegos]; //vetor com todos os morcegos disponiveis.
    double posicoesMorcego[quantidadeDeMorcegos][ordem];//vetor de posicoes dos morcegos, necessario para gerarmos
                                                        //aleatoriamente os valores.
    double velocidadesMorcegos[quantidadeDeMorcegos][ordem]; //vetor de velocidades dos morcegos, necessario para gerarmos
                                                            //aleatoriamente os valores.
    double melhorPosicaoMorcego[quantidadeDeMorcegos][ordem]; //Melhores posicoes de cada morcego.

    //double melhorPosicaoBando[ordem]; //melhor posicao do bando.

    double melhorFuncaoFitness = 10000000000; //foi iniciada com este valor alto pois sera logo substituida pela melhor
                                                //funcao de fitness entre os morcegos.
    double melhorPosicaoBandoTodasAsIteracoes[ordem]; //melhor posicao do bando dentre todas as iteracoes.

    //Criando os morcegos

   for(i = 0; i < quantidadeDeMorcegos;i++)
   {
        Morcego morcego;
        morcegos[i] = morcego;
   }

    //Criando os valores das posições dos morcegos.
    //Aquela função ali dentro irá gerar aletórios no intervalo de 0 a 20.

        srand((double)time(NULL));

        for(k = 0;k < quantidadeDeMorcegos;k++)
        {
            for(j = 0;j < ordem;j++)
            {
                posicoesMorcego[k][j] = 20 * ((double)(rand())/RAND_MAX);
            }

            morcegos[k].posicao = &posicoesMorcego[k][0];//envio do endereco da linha da matriz
                                                         //que contera as informacoes do morcego.

        }

    //Criando os valores de velocidade dos morcegos entre 0 e 3.

     for(k = 0;k < quantidadeDeMorcegos;k++)
    {
            for(j = 0;j < ordem;j++)
            {
                velocidadesMorcegos[k][j] = 3  * ((double)(rand())/RAND_MAX);
            }

            morcegos[k].velocidade = &velocidadesMorcegos[k][0];//envio do endereco da linha da matriz
                                                                //que contera as informacoes do morcego.
    }

//Obtendo a função de fitness inical para cada morcego.

   for(i = 0; i < quantidadeDeMorcegos;i++)
   {
        morcegos[i].funcaoFitness = CalcularFuncaoFitness(morcegos[i],enderecoA,enderecoB,ordem);
        morcegos[i].melhorFuncaoFitness = morcegos[i].funcaoFitness;
   }

    //Obter a melhor posicao do bando inicialmente

    for(i = 0;i < quantidadeDeMorcegos;i++)
    {
        for(j = 0;j < quantidadeDeMorcegos;j++)
        {

            if(i != j) //Nao faria sentido comparar o morcego com ele mesmo.
            {
                if(morcegos[i].funcaoFitness < morcegos[j].funcaoFitness)
                {
                    melhorFuncaoFitness = morcegos[i].funcaoFitness;

                    for(h = 0;h < ordem;h++)
                    {
                        //melhorPosicaoBando[h] = *(morcegos[i].posicao + h);
                        melhorPosicaoBandoTodasAsIteracoes[h] = *(morcegos[i].posicao + h);
                    }
                }
            }
        }
    }

    for(i = 0;i < quantidadeDeMorcegos;i++)
    {
        morcegos[i].melhorPosicao = &melhorPosicaoMorcego[i][0];
    }


    //Atualizar a melhor posicao de cada morcego inicialmente.

    for(i = 0;i < quantidadeDeMorcegos;i++)
    {
        for(j = 0;j < ordem;j++)
        {
            *(morcegos[i].melhorPosicao + j) = *(morcegos[i].posicao + j);
        }
    }

    //Variaveis da formula da PSO
   double A1,A2,A3; //irao ser gerados aleatoriamente sempre.
   double c1 = 2,c2 = 2; //Considerados sempre iguais a 2, por definicao.
   double tempo = 1; //considerado sempre igual a 1, por definicao.

    double criterioParada;
    printf("Qual o critério de parada para o algoritmo?\n");
    scanf("%lf",&criterioParada);


//Comecaremos a nossa iteracao...(Consideramos aqui que a variacao do tempo sempre sera igual a 1)
//e os valores constantes de c1 e c2 serao iguais a 2, respectivamente.

    int parada = 0; //quando parada = 1, o loop sera rompido.

    while(parada == 0)
    {
        //Passo 1: Gerar aleatoriamente A1,A2,A3, entre 0 e 1.

        A1 = 1 * ((double)(rand())/RAND_MAX);
        A2 = 1 * ((double)(rand())/RAND_MAX);
        A3 = 1 * ((double)(rand())/RAND_MAX);

        //Passo 2: Atualizar o vetor de velocidade dos morcegos.

        //Aplicando a formula da velocidade do morcego na iteracao.
        for(i = 0; i < quantidadeDeMorcegos;i++)
        {
            for(k = 0; k < ordem;k++)
            {
                //A1 * V na iteracao i do morcego q

                *(morcegos[i].velocidade + k) = *(morcegos[i].velocidade + k) * A1;

                //A2 * c1 * (melhor posicao do morcego q * posicao do morcego q na iteracao i) / tempo

                *(morcegos[i].velocidade + k) += A2 * c1 *  *(morcegos[i].velocidade + k) + *(morcegos[i].velocidade + k) + ((*(morcegos[i].melhorPosicao + k) - *(morcegos[i].posicao + k)) / tempo);

                //A3 * c2 * (melhor posicao do bando na iteracao i * posicao do morcego q na iteracao i) / tempo
                //Obs: Usaremos nesse caso a melhor posicao do bando dentre todas ja feitas e nao a melhor de cada
                //iteracao. Mudancas necessarias para o sucesso de convergencia do algoritmo.

                *(morcegos[i].velocidade + k) += A3 * c2 * (melhorPosicaoBandoTodasAsIteracoes[k] - *(morcegos[i].posicao + k) / tempo);

                //Realizar o controle da velocidade para a mesma nao aumentar muito,
                //pois fugirá do contexto da realiadade.
                if(*(morcegos[i].velocidade + k) >= 2)
                {
                    *(morcegos[i].velocidade + k) = 3 * ((double)(rand())/RAND_MAX);
                }
            }
        }

        //Passo 3: Atualizar as posicoes de cada morcego.

        //Aplicando a formula da posicaoo do morcego na iteracao.
        for(i = 0; i < quantidadeDeMorcegos;i++)
        {
            //S(q)(i + 1) = S(q)(i) + V(q)(i + 1) * tempo
            for(k = 0;k < ordem;k++)
            {
                *(morcegos[i].posicao + k) = *(morcegos[i].posicao + k) + *(morcegos[i].velocidade + k) * tempo;
            }
        }

        //Passo 4: Calcular a função de fitness de cada morcego.

        for(i = 0; i < quantidadeDeMorcegos;i++)
        {
            morcegos[i].funcaoFitness = CalcularFuncaoFitness(morcegos[i],enderecoA,enderecoB,ordem);
        }

        //Passo 5: Atualizar a melhor posicao do bando dentre todas as iteracoes

        for(i = 0;i < quantidadeDeMorcegos;i++)
        {
            if(morcegos[i].funcaoFitness < melhorFuncaoFitness)
            {
                melhorFuncaoFitness = morcegos[i].funcaoFitness;

                for(j = 0;j < ordem;j++)
                {
                    melhorPosicaoBandoTodasAsIteracoes[j] = *(morcegos[i].posicao + j);
                }

            }
        }

        //printf("Melhor função de fitness: %f\n",melhorFuncaoFitness);

        //Passo 6: Atualizar a melhor posicao de cada morcego

        for(i = 0;i < quantidadeDeMorcegos;i++)
        {
            if(morcegos[i].funcaoFitness < morcegos[i].melhorFuncaoFitness)
            {
                morcegos[i].melhorFuncaoFitness = morcegos[i].funcaoFitness;

                for(j = 0;j < ordem;j++)
                {
                    *(morcegos[i].melhorPosicao + j) = *(morcegos[i].posicao + j);
                }
            }
        }

        //Passo 7: Verificar o criterio de parada.
        //Se a melhor funcao de fitness for menor que o criterio de parada,
        //encontramos uma solucao aproximada.
        if(melhorFuncaoFitness <= criterioParada)
        {
            parada = 1;
        }
    }

    //Resultados

    printf("Solução aproximada do sistema:\n");

    for(i = 0;i < ordem;i++)
    {
        printf("x%d = %f\n",i + 1,melhorPosicaoBandoTodasAsIteracoes[i]);
    }

    return 0;
}
