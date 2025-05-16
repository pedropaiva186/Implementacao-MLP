#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "solution.h"
#include "subsequence.h"

void RVND(Solution & s);

bool bestImprovementSwap(Solution &s, std::vector<std::vector<Subsequence>> &matrizSub);

bool bestImprovement2OPT(Solution &s, std::vector<std::vector<Subsequence>> &matrizSub);

bool bestImprovementInsertion(Solution & s, int bloco, std::vector<std::vector<Subsequence>> &matrizSub);

#endif // LOCAL_SEARCH_H