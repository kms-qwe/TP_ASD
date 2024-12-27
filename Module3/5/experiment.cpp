#include "experiment.h"
#include "graph.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <iomanip> 

Experiment::Experiment(int minN, int maxN, int runsPerN)
    : minN(minN), maxN(maxN), runsPerN(runsPerN) {}

void Experiment::run() {
    std::cout << "MAR - Mean Approximation Ratio" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::setw(5) << "N" << std::setw(15) << "MAR" 
              << std::setw(15) << "StdDev" << "\n";
    
    for (int n = minN; n <= maxN; ++n) {
        double meanRatio = 0, stddev = 0;
        runForN(n, meanRatio, stddev);
        std::cout << std::setw(5) << n 
                  << std::setw(15)<< meanRatio 
                  << std::setw(15) << stddev << "\n";
    }
}

void Experiment::runForN(int n, double& meanRatio, double& stddev) {
    std::vector<double> approximationRatios;
    
    for (int i = 0; i < runsPerN; ++i) {
        auto points = Point::generatePoints(n);
        Graph graph(n, points);

        auto [mstBasedWeight, mstPath] = graph.findTspPath();
        double exactWeight = graph.exactTSP(points);

        double ratio = mstBasedWeight / exactWeight;
        approximationRatios.push_back(ratio);

        // std::cout << "Run " << i + 1 << ":\n";
        // std::cout << "MST Based Weight: " << mstBasedWeight << "\n";
        // std::cout << "Exact Weight: " << exactWeight << "\n";

        // std::cout << "POINTS: ";
        // for (auto point : points) {
        //     std::cout <<  point << " ";
        // }
        // std::cout << "\n";

        // std::cout << "MST Path: ";
        // for (int node : mstPath) {
        //     std::cout << node << " ";
        // }
        // std::cout << "\n\n";
    }

    meanRatio = std::accumulate(approximationRatios.begin(), approximationRatios.end(), 0.0) / runsPerN;

    double sumSquaredDiffs = 0.0;
    for (double ratio : approximationRatios) {
        double diff = ratio - meanRatio;
        sumSquaredDiffs += diff * diff;
    }
    stddev = std::sqrt(sumSquaredDiffs / runsPerN);
}
