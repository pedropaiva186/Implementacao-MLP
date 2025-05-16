#include "solution.h"
#include "subsequence.h"
#include "localSearch.h"
#include "construcao.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>

void Solution::calculateCostAcum()
{
    Data &data = Data::getInstance();
    int vert1, vert2;
    double aux = 0;
    cost = 0;

    for(int i = 0; i < data.n; i++)
    {
        vert1 = route[i];
        vert2 = route[i + 1];
        
        aux += data.matrizAdj[vert1][vert2];
        cost += aux;
    }
}

void Solution::print()
{
    std::cout << "Route: ";
    for(int i = 0; i < Data::getInstance().n; i++)
    {
        std::cout << route[i] << " - ";
    }
    std::cout << route[Data::getInstance().n] << std::endl;
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Cost: " << cost << std::endl;
}

Solution perturbacao(Solution s)
{
    // Gerando a seed de aleatoriedade
    std::random_device rd;
    std::mt19937 gen(rd());

    Data &data = Data::getInstance();

    int n = data.n;
    int max_seg = ceil(n / 10.0);
    int tam_seg_i, tam_seg_j, i, j;

    // Criando a solução que será retornada, que será baseada na solução advinda do parâmetro
    auto &rota = s.route;
    Subsequence subseq;
    std::vector<std::vector<Subsequence>> matrizSub(s.route.size(), std::vector<Subsequence>(s.route.size()));

    // Definindo o tamanho dos dois segmentos que trocarão de lugar
    std::uniform_int_distribution<> ger(2, max_seg);
    tam_seg_i = ger(gen);
    tam_seg_j = ger(gen);

    // Definindo os indíces
    std::uniform_int_distribution<> ger1(1, n / 2 - tam_seg_i);
    i = ger1(gen);
    std::uniform_int_distribution<> ger2(i + tam_seg_i, n - tam_seg_j);
    j = ger2(gen);

    // Atualizando a matriz de subsequências a partir da solução atual
    updateAllSubseq(s, matrizSub);

    subseq = Subsequence::Concatenate(matrizSub[0][i - 1], matrizSub[j][j + tam_seg_j - 1]);

    // Caso sejam adjascentes
    if(i + tam_seg_i != j)
    {
        subseq = Subsequence::Concatenate(subseq, matrizSub[i + tam_seg_i][j - 1]);
    }

    subseq = Subsequence::Concatenate(subseq, matrizSub[i][i + tam_seg_i - 1]);
    subseq = Subsequence::Concatenate(subseq, matrizSub[j + tam_seg_j][data.n]);

    std::vector<int> seg_i(rota.begin() + i, rota.begin() + i + tam_seg_i);
    std::vector<int> seg_j(rota.begin() + j, rota.begin() + j + tam_seg_j);

    // Retirando o segmento "j" e pondo o segmento "i" no lugar
    rota.insert(rota.begin() + j, seg_i.begin(), seg_i.end());
    rota.erase(rota.begin() + j + tam_seg_i, rota.begin() + j + tam_seg_i + tam_seg_j);

    // Retirando o segmento "i" e pondo o segmento "j" no lugar
    rota.insert(rota.begin() + i, seg_j.begin(), seg_j.end());
    rota.erase(rota.begin() + i + tam_seg_j, rota.begin() + i + tam_seg_j + tam_seg_i);

    s.cost = subseq.C;

    return s;
}

Solution ils(int maxIter, int maxIterIls)
{
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;

    for(int i = 0; i < maxIter; i++)
    {
        Solution s = Construcao();
        Solution best = s;

        int iterIls = 0;

        while(iterIls <= maxIterIls)
        {
            RVND(s);
            if(s.cost < best.cost)
            {
                best = s;
                iterIls = 0;
            }

            s = perturbacao(best);
            iterIls++;
        }

        if(best.cost < bestOfAll.cost)
        {
            bestOfAll = best;
        }
    }

    return bestOfAll;
}