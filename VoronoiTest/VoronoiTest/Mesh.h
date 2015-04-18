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

#include "Intersection.h"
#include "Ray.h"

using namespace std;



class Mesh {
public:
    Mesh();
    Mesh(std::vector<glm::vec3> vert);
    virtual void DrawWireframe();
    virtual void DrawRandomPoints();
    std::vector<glm::vec3> myRandomPoints;
    std::vector<glm::vec3> myInternalPoints;
    //virtual void GenerateRandomInternalPoints(int numPoints);
    //int numOfIntersections;
    
};

class Cube : public Mesh
{
public:
    Cube();
    Cube(std::vector<glm::vec3> v);
    virtual void  DrawWireframe();
    
    std::vector<std::vector<float>> myRandomPoints;
    std::vector<std::vector<float>> myInternalPoints;
    int numRandomPoints;
    int numInternalPoints;
    void GenerateRandomInternalPoints(int numPoints, std::vector<float> impactPoint);
    virtual void DrawRandomPoints();
    std::vector<glm::vec3> DebugGenerateRandomPts(int numberOfPts);
    
    Intersection intersectImpl(const Ray &ray);
    //Intersection intersect(const glm::mat4 &T, Ray ray_world);
    
    std::vector<std::vector<float>> myPoints;
    
    /**
    std::vector<float> p1;
    std::vector<float> p2;
    std::vector<float> p3;
    std::vector<float> p4;
    std::vector<float> p5;
    std::vector<float> p6;
    std::vector<float> p7;
    std::vector<float> p8;
    */
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    glm::vec3 p5;
    glm::vec3 p6;
    glm::vec3 p7;
    glm::vec3 p8;
    
    float minX;
    float minY;
    float minZ;
    
    float maxX;
    float maxY;
    float maxZ;
    
    int numOfIntersections;
    std::vector<glm::vec3> myVertices;
    
};





#endif /* defined(__VoronoiTest__Cube__) */
