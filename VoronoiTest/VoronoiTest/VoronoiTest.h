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
    
    void ComputeVoronoiDecomp(Cube hitCube, std::vector<std::vector<float>> internalRandomPoints);
    
};

#endif /* defined(__VoronoiTest__VoronoiTest__) */
