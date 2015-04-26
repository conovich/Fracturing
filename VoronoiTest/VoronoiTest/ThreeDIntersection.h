//
//  ThreeDIntersection.h
//  VoronoiTest
//
//  Created by Megan Moore on 4/25/15.
//  Copyright (c) 2015 Megan Moore. All rights reserved.
//

#ifndef VoronoiTest_ThreeDIntersection_h
#define VoronoiTest_ThreeDIntersection_h


#endif
#include "glm/glm.hpp"
#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include "Intersection.h"
#include "Ray.h"

class ThreeDIntersection {
public:
    ThreeDIntersection(){};
    void DrawCube();
    void DrawTetra();
    std::vector<glm::vec3> cubeVerts;
    std::vector<int> cubeInds;
    std::vector<glm::vec3> tetraVerts;
    std::vector<int> tetraInds;
    std::vector<glm::vec3> GetNormals();
    void newConvexHull(std::vector<glm::vec3>, std::vector<int>, std::vector<glm::vec3>);
    std::vector<glm::vec3> vertsInTetra;
    std::vector<glm::vec3> normals;
    void GetVertsInTetra();
    int intersectionImpl(const Ray &ray);
    Intersection triangleIntersect(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, const Ray &ray);
};