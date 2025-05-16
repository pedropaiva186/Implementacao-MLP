#include "data.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "solution.h"

int main() {

    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instances/rd100.tsp";

    Data & data = Data::getInstance();

    data.read(2, argv);

    Solution s;

    int maxIter = 10, maxIterIls = data.n <= 100 ? data.n:100;

    auto inicio = std::chrono::high_resolution_clock::now();

    s = ils(maxIter, maxIterIls);

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    s.print();

    std::ofstream tempo("tempo.txt", std::ios::app);
    
    if(tempo.is_open()) {
        tempo << "+ " << duracao.count() << std::endl;
        tempo.close();
    }

    std::ofstream custo("custo.txt", std::ios::app);

    if(custo.is_open()) {
        custo << std::fixed << std::setprecision(0);
        custo << "+ " << s.cost << std::endl;
    }

    return 0;
}