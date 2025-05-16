#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <iostream>
#include "solution.h"

struct verticeECusto;

std::vector<verticeECusto> calculaCusto(int &vertFinal, std::vector<int> &CL);

Solution Construcao();

#endif