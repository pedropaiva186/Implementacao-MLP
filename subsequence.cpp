#include <iostream>
#include <vector>

#include "subsequence.h"

// Função responsável por combinar duas subsequências
Subsequence Subsequence::Concatenate(Subsequence &sigma1, Subsequence &sigma2)
{
    auto &t = Data::getInstance().matrizAdj;
    Subsequence sigma;
    // Valor da aresta entre o último elemento da primeira subsequência com o primeiro elemento da segunda subsequência
    double temp = t[sigma1.last][sigma2.first];

    // Calculando o valor das estruturas auxiliares e definindo outros parâmetros
    sigma.W = sigma1.W + sigma2.W;
    sigma.T = sigma1.T + temp + sigma2.T;
    sigma.C = sigma1.C + sigma2.W * (sigma1.T + temp) + sigma2.C;
    sigma.first = sigma1.first;
    sigma.last = sigma2.last;

    return sigma;
}

// Função responsável por atualizar a matriz de subsequência
void updateAllSubseq(Solution &s, std::vector<std::vector<Subsequence>> &subseq_matriz)
{
    int aux = s.route.size();

    // Atualizando a diagonal principal
    for(int i = 0; i < aux; i++)
    {
        // Depende se é o elemento "alpha 0" ou não
        subseq_matriz[i][i].W = (i > 0);
        subseq_matriz[i][i].T = 0;
        subseq_matriz[i][i].C = 0;
        subseq_matriz[i][i].first = s.route[i];
        subseq_matriz[i][i].last = s.route[i];
    }

    // Atualizando a parte triangular superior da matriz
    for(int i = 0; i < aux; i++)
    {
        for(int j = i + 1; j < aux; j++)
        {
            subseq_matriz[i][j] = Subsequence::Concatenate(subseq_matriz[i][j-1], subseq_matriz[j][j]);
        }
    }

    // Atualizando a parte triangular inferior da matriz, considerando as subsequências em ordem inversa
    for(int i = aux - 1; i >= 0; i--)
    {
        for(int j = i - 1; j >= 0; j--)
        {
            subseq_matriz[i][j] = Subsequence::Concatenate(subseq_matriz[i][j + 1], subseq_matriz[j][j]);
        }
    }
}