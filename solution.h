#ifndef SOLUTION_H
#define SOLUTION_H

#include "data.h"
#include <vector>

struct Solution
{
    std::vector<int> route;
    double cost;

    Solution(std::vector<int> route, double cost): route(route), cost(cost) {}
    Solution() : route(std::vector<int>(Data::getInstance().n + 1)), cost(0) {}
    Solution(const Solution &s) : route(s.route), cost(s.cost) {}

    void calculateCostAcum();

    void print();
};

Solution perturbacao(Solution s);

Solution ils(int maxIter, int maxIterIls);

#endif