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
    Mesh(std::vector<glm::vec3> vert, std::vector<int> indices, glm::vec3 center, string type);
    
    //TODO: should refactor into differenct classes. when we have time. if we have time.
    string myType;
    
    virtual void DrawWireframe();
    virtual void DrawInternalPoints();
    virtual void DrawExternalPoints();
    
    std::vector<std::vector<float>> myRandomPoints;
    std::vector<std::vector<float>>myInternalPoints;
    std::vector<std::vector<float>>myExternalPoints; //for debugging
    std::vector<glm::vec3> myVertices;
    std::vector<int> myIndices;
    virtual void GenerateRandomInternalPoints(int numPoints, std::vector<float> impactPoint);
    int numOfIntersections;
    int numRandomPoints;
    int numInternalPoints;
    glm::vec3 myCenter;
    
    int intersectImpl(const Ray &ray);
    Intersection triangleIntersect(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, const Ray &ray);
    
    
    glm::vec3 CalculateCenter();
    
    
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    glm::vec3 p5;
    glm::vec3 p6;
    glm::vec3 p7;
    glm::vec3 p8;

    
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
    virtual void DrawInternalPoints();
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
