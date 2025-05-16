#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include "solution.h"

struct Subsequence {
    double T, C;
    int W;
    int first, last;
    
    static Subsequence Concatenate(Subsequence &sigma1, Subsequence &sigma2);
};

void updateAllSubseq(Solution &s, std::vector<std::vector<Subsequence>> &subseq_matriz);

#endif