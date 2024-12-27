#include "experiment.h"

int main() {
    int minN = 2, maxN = 10, runsPerN = 10;

    Experiment experiment(minN, maxN, runsPerN);
    experiment.run();

    return 0;
}
