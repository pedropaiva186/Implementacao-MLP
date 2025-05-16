#include "localSearch.h"
#include "solution.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

void RVND(Solution &s)
{
    // Gerando a seed de aleatoriedade e gerador de números
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::vector<Subsequence>> matrizSub(s.route.size(), std::vector<Subsequence>(s.route.size()));
    std::vector<int> NL = {1, 2, 3, 4, 5};
    std::shuffle(NL.begin(), NL.end(), gen);
    bool improved = false;

    // Atualizando a matriz de subsequência pela primeira vez
    updateAllSubseq(s, matrizSub);

    for(int i; i < NL.size(); )
    {
        switch(NL[i]){
            case 1:
                improved = bestImprovementSwap(s, matrizSub);
                break;
            case 2:
                improved = bestImprovement2OPT(s, matrizSub);
                break;
            case 3:
                improved = bestImprovementInsertion(s, 1, matrizSub);
                break;
            case 4:
                improved = bestImprovementInsertion(s, 2, matrizSub);
                break;
            case 5:
                improved = bestImprovementInsertion(s, 3, matrizSub);
                break;
        }

        if(improved)
        {
        std::shuffle(NL.begin(), NL.end(), gen);
        i = 0;
        // Atualizando a matriz pois a solução mudou
        updateAllSubseq(s, matrizSub);
        }else
        {
            ++i;
        }
    }
}

bool bestImprovement2OPT(Solution &s, std::vector<std::vector<Subsequence>> &matrizSub)
{
    int size = s.route.size() - 1;
    Subsequence subseq;
    int best_i, best_j;
    double bestCusto = nan("");

    for(int i = 1; i < size - 1; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            subseq = Subsequence::Concatenate(matrizSub[0][i - 1], matrizSub[j][i]);
            subseq = Subsequence::Concatenate(subseq, matrizSub[j + 1][size]);

            if(subseq.C < bestCusto || std::isnan(bestCusto))
            {
                bestCusto = subseq.C;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestCusto < s.cost)
    {
        while(best_i < best_j)
        {
            int aux = s.route[best_i];

            s.route[best_i] = s.route[best_j];
            s.route[best_j] = aux;

            best_i++;
            best_j--;
        }

        s.cost = bestCusto;
        return true;
    }

    return false;
}

bool bestImprovementInsertion(Solution &s, int bloco, std::vector<std::vector<Subsequence>> &matrizSub)
{
    int size = s.route.size() - 1;
    Subsequence subseq;
    int indexVert, indexFinal;
    double bestCusto = nan("");

    for(int i = 1; i < size - bloco + 1; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(i - 1 <= j && j <= i + bloco - 1)
            {
                continue;
            }

            subseq = Subsequence::Concatenate(matrizSub[0][i - 1], matrizSub[i + bloco][j]);
            subseq = Subsequence::Concatenate(subseq, matrizSub[i][i + bloco - 1]);
            subseq = Subsequence::Concatenate(subseq, matrizSub[j + 1][size]);

            if(subseq.C < bestCusto || std::isnan(bestCusto))
            {
                bestCusto = subseq.C;
                indexVert = i;
                indexFinal = j;
            }
        }
    }

    if(bestCusto < s.cost)
    {
        auto &rota = s.route;
        std::vector<int> vert;

        vert.insert(vert.begin(), rota.begin() + indexVert, rota.begin() + indexVert + bloco);

        if(indexVert < indexFinal)
        {
            rota.insert(rota.begin() + indexFinal + 1, vert.begin(), vert.end());
            rota.erase(rota.begin() + indexVert, rota.begin() + indexVert + bloco);
        } else
        {
            rota.erase(rota.begin() + indexVert, rota.begin() + indexVert + bloco);
            rota.insert(rota.begin() + indexFinal + 1, vert.begin(), vert.end());
        }

        s.cost = bestCusto;
        return true;
    }

    return false;
}

bool bestImprovementSwap(Solution &s, std::vector<std::vector<Subsequence>> &matrizSub)
{
    int size = s.route.size() - 1;
    Subsequence subseq;
    double bestCusto = nan("");
    int bestI, bestJ, i, j;

    for(i = 1; i < size - 1; i++)
    {
        for(j = i + 1; j < size; j++)
        {

            subseq = Subsequence::Concatenate(matrizSub[0][i - 1], matrizSub[j][j]);

            // Caso não sejam adjacentes haverá uma quarta subsequência, que será somada
            if ((j != i + 1))
            {
                subseq = Subsequence::Concatenate(subseq, matrizSub[i + 1][j - 1]);
            }

            subseq = Subsequence::Concatenate(subseq, matrizSub[i][i]);
            subseq = Subsequence::Concatenate(subseq, matrizSub[j + 1][size]);

            if(subseq.C < bestCusto || std::isnan(bestCusto))
            {
                bestCusto = subseq.C;
                bestI = i;
                bestJ = j;
            }
        }
    }

    if(bestCusto < s.cost)
    {
        int aux = s.route[bestI];
        s.route[bestI] = s.route[bestJ];
        s.route[bestJ] = aux;

        s.cost = bestCusto;
        return true;
    }

    return false;
}