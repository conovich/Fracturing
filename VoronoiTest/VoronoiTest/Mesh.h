//
//  Mesh.h
//  VoronoiTest
//
//  Created by Corey Novich on 4/12/15.
//  Copyright (c) 2015 Corey Novich. All rights reserved.
//

#ifndef __VoronoiTest__Mesh__
#define __VoronoiTest__Mesh__

#include <iostream>
#include <vector>

using namespace std;



class Mesh{
public:
    Mesh();
    virtual void DrawWireframe();
    virtual void DrawRandomPoints();
    std::vector<std::vector<float>> myRandomPoints;
    //virtual void GenerateRandomInternalPoints(int numPoints);
    
};

class Cube : public Mesh
{
public:
    Cube();
    virtual void  DrawWireframe();
    
    std::vector<std::vector<float>> myRandomPoints;
    int numRandomPoints;
    void GenerateRandomInternalPoints(int numPoints);
    virtual void DrawRandomPoints();
    
    
    std::vector<std::vector<float>> myPoints;
    std::vector<float> p1;
    std::vector<float> p2;
    std::vector<float> p3;
    std::vector<float> p4;
    std::vector<float> p5;
    std::vector<float> p6;
    std::vector<float> p7;
    std::vector<float> p8;
    
    float minX;
    float minY;
    float minZ;
    
    float maxX;
    float maxY;
    float maxZ;
    
    
};





#endif /* defined(__VoronoiTest__Cube__) */
