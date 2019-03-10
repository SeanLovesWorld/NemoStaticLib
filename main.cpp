/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Wooyoung
 *
 * Created on October 10, 2017, 10:48 AM
 */

//#include <cstdlib>
//#include <sparsehash/sparse_hash_map>


#include "Graph.h"
#include "Subgraph.h"
#include "SubgraphCount.h"
#include "SubgraphProfile.h"

#include "RandomGraphGenerator.h"
#include "RandomGraphAnalysis.h"
#include "StatisticalAnalysis.h"


using std::cout;
using std::cerr;
using std::endl;

#include <vector>

using std::vector;

#include <stdexcept>

using std::domain_error;

#include <string>

using std::string;

#include "ESU.h"
#include "NautyLink.h"

#include <string.h>
#include <stdio.h>
#include <math.h>





/*
#define MAXN 64
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include "gtools.h"
#include "nauty.h"
#include "graph64.hpp"

*/
//#include <cstdlib>





//should remove after checking the file IO
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

////should remove after checking the file IO

//using namespace std;

/*
 *
 */


template<typename map_key, typename map_val>
void printmap(const unordered_map<map_key, map_val> &_map) {
    for (const auto &p : _map)
        cout << p.first << " => " << p.second << endl;

}


/*inline edge new_edge(vertex u, vertex v)
{
    return uint64(u) << 32 | uint64(v);
}
*/

int main(int argc, char **argv) {
    std::clock_t begin = std::clock();
    std::clock_t tallyBegin = begin;

    double duration = 0.0;
    double tally = 0.0;

//    cout<<"Graph Test"<<endl;
    string filename = "../TestingFiles/Y2k.txt";
//   string filename = "test_input.txt";
    Graph targetg(filename, false);
//    cout << targetg.getSize() << endl;
//    cout << targetg << endl;

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "File Input time: \t\t\t\t\t\t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;
    tallyBegin = std::clock();

    cout << "Analyzing target graph..." << endl;
//    SubgraphProfile subc(targetg.getSize());
    SubgraphCount subc;
    int motifSize = 3;
    int randomCount = 1000;
    ESU::enumerate(targetg, subc, motifSize);

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "Enueration time: \t\t\t\t\t\t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;
    tallyBegin = std::clock();

    // measuring probing time in order to compare with java
    vector<double> probs;
    for (int i = 0; i < motifSize - 2; i++) {
        probs.push_back(1.0);
    }
    probs.push_back(0.5);
    probs.push_back(0.5);

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "Probing time: \t\t\t\t\t\t\t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;
    tallyBegin = std::clock();


    unordered_map<graph64, double> targetLabelRelFreqMap = subc.getRelativeFrequencies();
//    printmap(targetLabelRelFreqMap);

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "Unordered map initalization time time: \t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;
    tallyBegin = std::clock();

    cout << "Analyzing random graphs..." << endl;

    cout << "---------------------------------------------------------" << endl << endl << endl;

    cout << "targetg: " << targetg << endl << endl;
    cout << "randomCount: " << randomCount << endl << endl;
    cout << "motifSize: " << motifSize << endl << endl;
    cout << "probs: ";
    for (auto i = probs.begin(); i != probs.end(); ++i)
        std::cout << *i << ' ';

    cout << endl << endl;

//    return 0;


    unordered_map<graph64, vector<double>> randLabelRelFreqsMap = RandomGraphAnalysis::analyze(targetg, randomCount,
                                                                                               motifSize, probs);

    cout << endl << endl << endl;
    cout << "---------------------------------------------------------" << endl << endl << endl;

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "Analyzing time: \t\t\t\t\t\t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;
    tallyBegin = std::clock();


    cout << "Comparing target graph to random graphs" << endl;

    StatisticalAnalysis stat(targetLabelRelFreqMap, randLabelRelFreqsMap, randomCount);

    cout << stat << endl;

    tally = (std::clock() - tallyBegin) / (double) CLOCKS_PER_SEC;
    duration = (std::clock() - begin) / (double) CLOCKS_PER_SEC;
    cout << "Result output time: \t\t\t\t\t\t" << tally << "s" << endl;
    cout << "Time from the beginning: \t\t\t\t" << duration << "s" << endl << endl << endl;


    return 0;
}
