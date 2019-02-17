cmake_minimum_required(VERSION 3.13)
project(NemoStaticLib)

set(CMAKE_CXX_STANDARD 17)

add_executable(NemoStaticLib main.cpp
        nauty/gtools.c nauty/naugraph.c nauty/nausparse.c nauty/nautil.c nauty/nautinv.c nauty/naututil.c nauty/nauty.c
        nauty/schreier.c nauty/sorttemplates.c nauty/naurng.c
        ESU.cpp Graph.cpp NautyLink.cpp RandESU.cpp RandomGraphAnalysis.cpp RandomGraphGenerator.cpp
        StatisticalAnalysis.cpp Subgraph.cpp SubgraphCount.cpp SubgraphProfile.cpp)