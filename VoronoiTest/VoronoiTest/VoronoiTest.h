//
//  VoronoiTest.h
//  VoronoiTest
//
//  Created by Corey Novich on 4/12/15.
//  Copyright (c) 2015 Corey Novich. All rights reserved.
//

#ifndef __VoronoiTest__VoronoiTest__
#define __VoronoiTest__VoronoiTest__

#include <iostream>
#include "Mesh.h"
#include "voro++.hh"

//using namespace std;
using namespace voro;

class VoronoiTest{
public:
    VoronoiTest();
    
    
    
    //%P
    //A list of the vertices of the Voronoi cell in the format (x,y,z), relative to the global coordinate system.
    
    void ComputeVoronoiDecompCube(Cube hitCube, std::vector<std::vector<float>> internalRandomPoints);
    
    void DrawVoronoi();
    
};

#endif /* defined(__VoronoiTest__VoronoiTest__) */
