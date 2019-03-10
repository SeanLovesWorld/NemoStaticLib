/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandomGraphAnalysis.cpp
 * Author: Wooyoung
 * 
 * Created on November 3, 2017, 1:29 PM
 */

/**
 * RandomGraphAnalysis is a facade class that generates and enumerates using
 * RAND-ESU a set of random network graphs based on the degree sequence vector
 * of a specified graph. The output of the analyze() method can be used by a
 * StatisticalAnalysis object to determine whether a target graph contains any
 * network motifs.
 */

#include "RandomGraphAnalysis.h"

//should be removed after testing
#include <ctime>

RandomGraphAnalysis::RandomGraphAnalysis() {
}

RandomGraphAnalysis::~RandomGraphAnalysis() {
}

/**
 * Generate and enumerate a set of random graphs.
 * @param targetGraph the network graph from which to derive a degree
 *                    sequence vector for generating random graphs
 * @param randomGraphCount the number of random graphs to use for analysis
 * @param subgraphSize the size of subgraph to enumerate
 * @param probs the probability vector to be used by the RAND-ESU algorithm
 * @return mapping of labels to relative frequencies as found in the 
 * random graph pool
 */

unordered_map<graph64, vector<double>>
RandomGraphAnalysis::analyze(Graph &targetGraph, int randomGraphCount, int subgraphSize, const vector<double> &probs) {
    // create the return map and fill it with the labels we found in the
    // target graph, as those are the only labels about which we care
    // TODO consider changing this, as it creates the precondition of 
    // executing the target graph analysis first
    unordered_map<graph64, vector<double>> labelRelFreqsMap;

    std::clock_t begin = 0;
    double duration1 = 0;
    double duration2 = 0;
    double duration3 = 0;
    double duration4 = 0;
    double duration5 = 0;
    double duration6 = 0;

    for (int i = 0; i < randomGraphCount; i++) {
        //display status for every 100th graph
        if (i % 100 == 99) {
            cout << "Analyzing random graph " << i + 1 << "..." << endl;
        }

        begin = std::clock();

        //generate random graphs
        Graph randomGraph = RandomGraphGenerator::generate(targetGraph);

        duration1 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;

        begin = std::clock();
        // enumerate random graphs
        SubgraphCount subgraphCount;
        duration2 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;

        begin = std::clock();
        RandESU::enumerate(randomGraph, subgraphCount, subgraphSize, probs);
        duration3 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;
        begin = std::clock();
        unordered_map<graph64, double> curLabelRelFreqMap = subgraphCount.getRelativeFrequencies();
        duration4 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;

        // populate labelRelReqsMap with result

        begin = std::clock();
        for (const auto &curLabelRelFreqPair : curLabelRelFreqMap) {
            graph64 curLabel = curLabelRelFreqPair.first;
            double curFreq = curLabelRelFreqPair.second;
            labelRelFreqsMap[curLabel].push_back(curFreq);
        }
        duration5 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    }

    begin = std::clock();
    // fill in with zeros any List that is less than subgraph count to
    // ensure non-detection is accounted for.
    for (auto &p : labelRelFreqsMap) {
        while (p.second.size() < randomGraphCount) {
            p.second.push_back(0.0);
        }
    }

    duration6 += (std::clock() - begin) / (double) CLOCKS_PER_SEC;

    std::cout << "duration1: " << duration1 << endl;
    std::cout << "duration2: " << duration2 << endl;
    std::cout << "duration3: " << duration3 << endl;
    std::cout << "duration4: " << duration4 << endl;
    std::cout << "duration5: " << duration5 << endl;
    std::cout << "duration6: " << duration6 << endl;

    return labelRelFreqsMap;

}

