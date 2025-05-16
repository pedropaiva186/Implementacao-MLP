#include <iostream> // Biblioteca padrão do c++
#include <cmath> // Funções matemática
#include <vector> // Estrutura de dados vector
#include <algorithm> // Permite o uso do "sort"
#include <random> // Permite o uso de funções de aleatorização
#include <unordered_set> // Estrutura de dado do CL

#include "construcao.h"
#include "data.h"
#include "solution.h"

struct verticeECusto
{
    int vertice;
    double custo;
};

// Calculando o custo de inserção de cada possível vértice ao final da solução
std::vector<verticeECusto> calculaCusto(int vertFinal, std::unordered_set<int> &CL)
{
    auto &matrizAdj = Data::getInstance().matrizAdj;
    std::vector<verticeECusto> custos;

    // Salvando o custo de cada possível inserção no vector custo
    for(int i : CL)
    {
        custos.push_back({i, matrizAdj[vertFinal][i]});
    }

    return custos;
}

bool compareByCost(const verticeECusto &a, const verticeECusto &b)
{
    return a.custo < b.custo;
}

Solution Construcao()
{
    // Gerando a seed de aleatoriedade
    std::random_device rd;
    std::mt19937 gen(rd());

    Data &data = Data::getInstance();
    auto &matriz_adj = data.matrizAdj;

    // Criando a rota que será retornada
    Solution s;
    s.route = {1};

    // Estruturas para auxiliar o calculo do custo
    double custo_auxiliar = 0, duracao_auxiliar = 0;

    // Criando e preenchendo o CL
    std::unordered_set<int> CL;
    for(int i = 2; i <= data.n; i++)
    {
        CL.insert(i);
    }

    // Servirá como auxiliar para definirmos o vértice escolhido
    int r = 1;
    
    while(!CL.empty())
    {
        // Organizando e preenchendo o vector de custo de inserção
        std::vector<verticeECusto> custoInsercao = calculaCusto(r, CL);
        std::sort(custoInsercao.begin(), custoInsercao.end(), compareByCost);

        // Escolhendo um valor aleatório dentre os possíveis
        double alpha = 0.5;
        std::uniform_int_distribution<> ger(0, (int) floor(alpha * custoInsercao.size()));
        verticeECusto selecionado = custoInsercao[ger(gen)];

        // Adicionando os valores referentes ao vértice escolhido
        duracao_auxiliar += selecionado.custo;
        custo_auxiliar += duracao_auxiliar;

        // Apagando o vértice escolhido do CL e colocando-o dentro da rota
        CL.erase(selecionado.vertice);
        s.route.push_back(selecionado.vertice);

        // Definindo o vértice final atual
        r = selecionado.vertice;
    }

    // Adicionando o custo da última aresta
    duracao_auxiliar += matriz_adj[r][1];
    custo_auxiliar += duracao_auxiliar;

    // Transferindo o valor do custo para a rota
    s.route.push_back(1);
    s.cost = custo_auxiliar;
    return s;
}