cmake_minimum_required(VERSION 3.13)

project(NemoStaticLib)

set(CMAKE_CXX_STANDARD 17)

#include_directories(nauty)
#LINK_DIRECTORIES(nauty)

add_executable(NemoStaticLib main.cpp
        ESU.cpp Graph.cpp NautyLink.cpp RandESU.cpp RandomGraphAnalysis.cpp RandomGraphGenerator.cpp
        StatisticalAnalysis.cpp Subgraph.cpp SubgraphCount.cpp SubgraphProfile.cpp
        nauty/gtools.c nauty/naugraph.c nauty/nausparse.c nauty/nautinv.c nauty/naututil.c nauty/nauty.c
        nauty/schreier.c nauty/naurng.c nauty/nautil.c nauty/sorttemplates.c
        )

#target_link_libraries(NemoStaticLib mylib)