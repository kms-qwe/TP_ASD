#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "graph.h"
#include <vector>

class Experiment {
public:
    Experiment(int minN, int maxN, int runsPerN);
    void run();

private:
    int minN, maxN, runsPerN;

    void runForN(int n, double& mean, double& stddev);
};

#endif 