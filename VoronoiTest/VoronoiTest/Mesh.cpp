//
//  Mesh.cpp
//  VoronoiTest
//
//  Created by Corey Novich on 4/12/15.
//  Copyright (c) 2015 Corey Novich. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "Mesh.h"
#include "nearlyEqual.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>


#define NUM_ENDS 2           /* number of end "points" to draw */
int myEnds[NUM_ENDS][2];       /* array of 2D points */

Mesh::Mesh(){
    //numOfIntersections = 0;
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<int> indices, glm::vec3 center, string newType) {
    myType = newType;
    
    numOfIntersections = 0;
    
    float centerX = 0.0f;
    float centerY = 0.0f;
    float centerZ = 0.0f;
    
    
    //add vertices from mesh to myVertices
    for(int i = 0; i < vertices.size(); i++) {
        myVertices.push_back(vertices[i]);
        centerX += vertices[i].x;
        centerY += vertices[i].y;
        centerZ += vertices[i].z;
    }
    
    //add triangle indices to myIndices
    for(int j = 0; j < indices.size(); j++) {
        //REMEMBER TO CHANGE THIS TO NOT "- 1"
        myIndices.push_back(indices[j]);
    }
    
     //center of bounding box of the mesh
    //myCenter = center;
    myCenter = glm::vec3(centerX/vertices.size(), centerY/vertices.size(), centerZ/vertices.size());
    
    
    //JUST FOR DRAWING -- WILL HAVE NO EFFECT ON THE MESH FUNCTIONALITY.
    if(myType == "cube"){
        p1 = vertices[0];
        p2 = vertices[1];
        p3 = vertices[2];
        p4 = vertices[3];
        p5 = vertices[4];
        p6 = vertices[5];
        p7 = vertices[6];
        p8 = vertices[7];
    }
    else if(myType == "tetrahedron"){
        p1 = vertices[0]; //bottom point
        p2 = vertices[1]; //bottom point
        p3 = vertices[2]; //bottom point
        p4 = vertices[3]; //top point
    }
    else if(myType == "other"){
        //not drawing these currently!
    }
    
}

glm::vec3 Mesh::CalculateCenter(){
    //TODO: calculate center based on the vertices!!!
    glm::vec3 center;
    
    return center;
    
}

//should refactor to give each shape type its own drawing method, instead of using the mesh class for all meshes.
void Mesh::DrawWireframe(){
    /* We tell we want to draw lines */
    glBegin(GL_LINES);
    
    if(myType == "cube"){
        //top face
        glColor3f(0, 0, 0); glVertex3f(p1[0], p1[1], p1[2]);
        glColor3f(0, 0, 1); glVertex3f(p2[0], p2[1],  p2[2]);
        
        glColor3f(0, 1, 1); glVertex3f(p2[0], p2[1], p2[2]);
        glColor3f(0, 1, 0); glVertex3f(p3[0], p3[1], p3[2]);
        
        glColor3f(1, 0, 0); glVertex3f(p3[0], p3[1], p3[2]);
        glColor3f(1, 0, 1); glVertex3f(p4[0], p4[1], p4[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
        glColor3f(1, 1, 0); glVertex3f(p1[0], p1[1], p1[2]);
        
        
        //bottom face
        glColor3f(0, 0, 0); glVertex3f(p5[0], p5[1], p5[2]);
        glColor3f(0, 0, 1); glVertex3f(p6[0], p6[1], p6[2]);
        
        glColor3f(1, 0, 1); glVertex3f(p6[0], p6[1], p6[2]);
        glColor3f(1, 0, 0); glVertex3f(p7[0], p7[1], p7[2]);
        
        glColor3f(0, 1, 0); glVertex3f(p7[0], p7[1], p7[2]);
        glColor3f(0, 1, 1); glVertex3f(p8[0], p8[1], p8[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p8[0], p8[1], p8[2]);
        glColor3f(1, 1, 0); glVertex3f(p5[0], p5[1], p5[2]);
        
        
        //sides!
        glColor3f(0, 0, 0); glVertex3f(p1[0], p1[1], p1[2]);
        glColor3f(0, 1, 0); glVertex3f(p5[0], p5[1], p5[2]);
        
        glColor3f(1, 1, 0); glVertex3f(p2[0], p2[1], p2[2]);
        glColor3f(1, 0, 0); glVertex3f(p6[0], p6[1], p6[2]);
        
        glColor3f(0, 0, 1); glVertex3f(p3[0], p3[1], p3[2]);
        glColor3f(0, 1, 1); glVertex3f(p7[0], p7[1], p7[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
        glColor3f(1, 0, 1); glVertex3f(p8[0], p8[1], p8[2]);
    }
    
    else if (myType == "tetrahedron"){
        //sides
        glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
        glColor3f(1, 1, 1); glVertex3f(p1[0], p1[1],  p1[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
        glColor3f(1, 1, 1); glVertex3f(p2[0], p2[1], p2[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
        glColor3f(1, 1, 1); glVertex3f(p3[0], p3[1], p3[2]);
        
        //base
        glColor3f(1, 1, 1); glVertex3f(p1[0], p1[1], p1[2]);
        glColor3f(1, 1, 1); glVertex3f(p2[0], p2[1], p2[2]);
    
        glColor3f(1, 1, 1); glVertex3f(p2[0], p2[1], p2[2]);
        glColor3f(1, 1, 1); glVertex3f(p3[0], p3[1], p3[2]);
        
        glColor3f(1, 1, 1); glVertex3f(p3[0], p3[1], p3[2]);
        glColor3f(1, 1, 1); glVertex3f(p1[0], p1[1], p1[2]);
        
    }
    
    //CURRENTLY DON'T DRAW IF IT'S AN OTHER SHAPE.
    
    glEnd();
    
}

void Mesh::DrawInternalPoints(){
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    std::vector<float> point;
    int i = 0;
    std::cout<<numInternalPoints<<std::endl;
    for(i = 0; i < numInternalPoints; i++){ //FOR SOME REASON .SIZE() WASN'T WORKING
        point = myInternalPoints.at(i);
        //glVertex3f(0.0f, 0.0f, 0.0f);
        float x = point[0];
        float y = point[1];
        float z = point[2];
        glVertex3f(x, y, z);
    }
    
    glEnd();
}

void Mesh::DrawExternalPoints(){
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    std::vector<float> point;
    int i = 0;
    for(i = 0; i < myExternalPoints.size(); i++){ //FOR SOME REASON .SIZE() WASN'T WORKING
        point = myExternalPoints.at(i);
        //glVertex3f(0.0f, 0.0f, 0.0f);
        float x = point[0];
        float y = point[1];
        float z = point[2];
        glVertex3f(x, y, z);
    }
    
    glEnd();
}

void Mesh::GenerateRandomInternalPoints(int numPoints, std::vector<float> impactPt){
    numRandomPoints = numPoints;
    myInternalPoints.clear();
    myRandomPoints.clear();
    numInternalPoints = 0;
    
    //vector<btConvexHullShape> convexHulls;
    //convexHull = btConvexHullShape();
    //btConvexHullShape convexMesh;
    //convexMesh = btConvexHullShape();
    
    for(int i = 0; i < numPoints; i++){
        
        //http://stackoverflow.com/questions/686353/c-random-float-number-generation
        float randomX = (impactPt[0] - .5) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[0] + 0.5) - (impactPt[0] - 0.5))));
        float randomY = (impactPt[1] - .5) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[1] + 0.5) - (impactPt[1] - 0.5))));
        float randomZ = (impactPt[2] - .5) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[2] + 0.5) - (impactPt[2] - 0.5))));
        
        //randomX = 0.0f;
        //randomY = 2.0f;
        //randomZ = 0.0f;
        vector<float> randomPoint;
        randomPoint.push_back(randomX);
        randomPoint.push_back(randomY);
        randomPoint.push_back(randomZ);
        
        myRandomPoints.push_back(randomPoint);
        
        //const btVector3 newPoint(randomX, randomY, randomZ);
        //convexMesh.addPoint(newPoint);
    }
    
    
    //generate points within the mesh
    for(int j = 0; j < numRandomPoints; j++) {
        numOfIntersections = 0;
        
        //raycast from each point in myRandomPoints in the direction of center of mesh
        float x = myCenter[0] - myRandomPoints[j][0];
        float y = myCenter[1] - myRandomPoints[j][1];
        float z = myCenter[2] - myRandomPoints[j][2];
        
        
        glm::vec3 d = glm::vec3(x, y, z);
        glm::vec3 o = glm::vec3(myRandomPoints[j][0], myRandomPoints[j][1], myRandomPoints[j][2]);
        Ray ray;
        ray.orig = o;
        ray.dir = d;
        
        intersectImpl(ray);
        
         //if the number of intersections is odd, add to internal points.
         if(numOfIntersections %2 == 1) {
             myInternalPoints.push_back(myRandomPoints[j]);
             numInternalPoints++;
         }
         else{
             myExternalPoints.push_back(myRandomPoints[j]);
         }
    }
    //convexHulls.push_back(convexMesh);
}

int Mesh::intersectImpl(const Ray &ray)
{
    Intersection inter;
    //Intersection smallest_inter;
    //smallest_inter.t = -1;
    
    //clear the number of intersections
    numOfIntersections = 0;
    
    //loop through the indices
    for(int i = 0; i < myIndices.size(); i+=3)
    {
        glm::vec3 p0 = myVertices[myIndices[i]];
        glm::vec3 p1 = myVertices[myIndices[i+1]];
        glm::vec3 p2 = myVertices[myIndices[i+2]];
        
        inter = triangleIntersect(p0, p1, p2, ray); //check every face
        //if(smallest_inter.t == -1) smallest_inter = inter; //set smallest_inter to the first intersection
        if(inter.t != -1) {
            //smallest_inter = inter;
            numOfIntersections++;  //only add to numOfIntersections if t != -1
        }
        
    }
    return numOfIntersections;
}

Intersection Mesh::triangleIntersect(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, const Ray &ray)
{
    
    Intersection inter;
    glm::vec3 xc = glm::cross((v1 - v0), (v2 - v0));
    glm::vec3 p = glm::cross(ray.dir, v2 - v0);
    glm::vec3 norm = glm::normalize(xc);
    
    if (abs(norm[0]) < .0001f && abs(norm[1]) < .0001f && abs(norm[2]) < .0001){
        inter.t = -1;
        return inter;;
    }
    
    float t;
    float a = glm::dot(v1 - v0, p);
    
    if (a < .00001 && a > -.00001){
        inter.t = -1;
        return inter;
    }
    else{
        float f = 1.0f/a;
        glm::vec3 s = ray.orig - v0;
        float u = f*(glm::dot(s, p));
        if ( u < 0.0f || u > 1.0f){
            inter.t = -1;
            return inter;
        }
        
        glm::vec3 q = glm::cross(s, v1 - v0);
        float v = f*glm::dot(ray.dir, q);
        
        if (v < 0.0f || u + v > 1.0f){
            inter.t = -1;
            return inter;
        }
        
        t = f*glm::dot(v2 - v0, q); //set t
        
        if (t < 0){
            inter.t = -1;
            return inter;
        }
    }
    
    inter.t = t;
    inter.normal = xc;
    
    return inter;
}

Cube::Cube(){
    //top face
    /**
    p1.push_back(-1);
    p1.push_back(1);
    p1.push_back(-1);
    
    p2.push_back(1);
    p2.push_back(1);
    p2.push_back(-1);
    
    p3.push_back(1);
    p3.push_back(1);
    p3.push_back(1);

    p4.push_back(-1);
    p4.push_back(1);
    p4.push_back(1);
    
    //bottom face
    p5.push_back(-1);
    p5.push_back(-1);
    p5.push_back(-1);
    
    p6.push_back(1);
    p6.push_back(-1);
    p6.push_back(-1);
    
    p7.push_back(1);
    p7.push_back(-1);
    p7.push_back(1);
    
    p8.push_back(-1);
    p8.push_back(-1);
    p8.push_back(1);
    
    myPoints.push_back(p1);
    myPoints.push_back(p2);
    myPoints.push_back(p3);
    myPoints.push_back(p4);
    myPoints.push_back(p5);
    myPoints.push_back(p6);
    myPoints.push_back(p7);
    myPoints.push_back(p8);
    
    
    //should set mins and max's when creating custom cubes.
    minX = -1;
    minY = -1;
    minZ = -1;
    
    maxX = 1;
    maxY = 1;
    maxZ = 1;
    
    numOfIntersections = 0;
    //myVertices = GetComponent<MeshFilter>().mesh.vertices;
    */
}

//create a cube using the array of vertices
Cube::Cube(std::vector<glm::vec3> vertices) {
    minX = 10000;
    minY = 10000;
    minZ = 10000;
    maxX = -10000;
    maxY = -10000;
    maxZ = -10000;
    
    for(int i = 0; i < vertices.size(); i++) {
        //myVertices.push_back(vertices[i]);
        std::vector<float> nv;
        nv.push_back((vertices[i][0]));
        nv.push_back((vertices[i][1]));
        nv.push_back((vertices[i][2]));
        myPoints.push_back(nv);
        
        //get the minx's and max's when creating custom cube
        if(vertices[i][0] < minX) minX = vertices[i][0];
        if(vertices[i][1] < minY) minY = vertices[i][1];
        if(vertices[i][2] < minZ) minZ = vertices[i][2];
        if(vertices[i][0] > maxX) maxX = vertices[i][0];
        if(vertices[i][1] > maxY) maxY = vertices[i][1];
        if(vertices[i][2] > maxZ) maxZ = vertices[i][2];
    }
    numOfIntersections = 0;
    
    p1 = vertices[0];
    p2 = vertices[1];
    p3 = vertices[2];
    p4 = vertices[3];
    p5 = vertices[4];
    p6 = vertices[5];
    p7 = vertices[6];
    p8 = vertices[7];
}

void Cube::DrawWireframe(){
    
    /* We tell we want to draw lines */
    glBegin(GL_LINES);
    
    //top face
    glColor3f(0, 0, 0); glVertex3f(p1[0], p1[1], p1[2]);
    glColor3f(0, 0, 1); glVertex3f(p2[0], p2[1],  p2[2]);
    
    glColor3f(0, 1, 1); glVertex3f(p2[0], p2[1], p2[2]);
    glColor3f(0, 1, 0); glVertex3f(p3[0], p3[1], p3[2]);
    
    glColor3f(1, 0, 0); glVertex3f(p3[0], p3[1], p3[2]);
    glColor3f(1, 0, 1); glVertex3f(p4[0], p4[1], p4[2]);
    
    glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
    glColor3f(1, 1, 0); glVertex3f(p1[0], p1[1], p1[2]);
    
    
    //bottom face
    glColor3f(0, 0, 0); glVertex3f(p5[0], p5[1], p5[2]);
    glColor3f(0, 0, 1); glVertex3f(p6[0], p6[1], p6[2]);
    
    glColor3f(1, 0, 1); glVertex3f(p6[0], p6[1], p6[2]);
    glColor3f(1, 0, 0); glVertex3f(p7[0], p7[1], p7[2]);
    
    glColor3f(0, 1, 0); glVertex3f(p7[0], p7[1], p7[2]);
    glColor3f(0, 1, 1); glVertex3f(p8[0], p8[1], p8[2]);
    
    glColor3f(1, 1, 1); glVertex3f(p8[0], p8[1], p8[2]);
    glColor3f(1, 1, 0); glVertex3f(p5[0], p5[1], p5[2]);
    
    
    //sides!
    glColor3f(0, 0, 0); glVertex3f(p1[0], p1[1], p1[2]);
    glColor3f(0, 1, 0); glVertex3f(p5[0], p5[1], p5[2]);
    
    glColor3f(1, 1, 0); glVertex3f(p2[0], p2[1], p2[2]);
    glColor3f(1, 0, 0); glVertex3f(p6[0], p6[1], p6[2]);
    
    glColor3f(0, 0, 1); glVertex3f(p3[0], p3[1], p3[2]);
    glColor3f(0, 1, 1); glVertex3f(p7[0], p7[1], p7[2]);
    
    glColor3f(1, 1, 1); glVertex3f(p4[0], p4[1], p4[2]);
    glColor3f(1, 0, 1); glVertex3f(p8[0], p8[1], p8[2]);
    
    /* Every four calls to glVertex, a quad is drawn */
    /*glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
     glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
     
     glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
     glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
     
     
     
     glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
     glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
     
     glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
     glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
     
     
     
     glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
     glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
     
     glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
     glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
     
     
     
     glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
     glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
     
     glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
     glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
     
     
     
     glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
     glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
     
     glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
     glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
     
     
     
     glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
     glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
     
     glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
     glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);*/
    
    /* No more quads */
    glEnd();
    
}

void Cube::DrawInternalPoints(){
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    std::vector<float> point;
    int i = 0;
    std::cout<<numInternalPoints<<std::endl;
    for(i = 0; i < numInternalPoints; i++){ //FOR SOME REASON .SIZE() WASN'T WORKING
        point = myInternalPoints.at(i);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(point.at(0), point.at(1), point.at(2));
    }
    
    glEnd();
}

std::vector<glm::vec3> Cube::DebugGenerateRandomPts(int numberOfPts) {
    //convex hull stuff
    vector<btConvexHullShape> convexHulls;
    //convexHull = btConvexHullShape();
    btConvexHullShape convexMesh;
    convexMesh = btConvexHullShape();
    
    //clear internal points
    myInternalPoints.clear();
    
    //vector of new random points
    std::vector<glm::vec3> newRandomPts;
    std::vector<float> cubeCenter;
    cubeCenter.push_back((minX+maxX)/2.0f);
    cubeCenter.push_back((minX+maxX)/2.0f);
    cubeCenter.push_back((minX+maxX)/2.0f);
    
    for(int i = 0; i < numberOfPts; i++) {
        
        //http://stackoverflow.com/questions/686353/c-random-float-number-generation
        float randomX = minX + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxX - minX)));
        float randomY = minY  + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxY - minY)));
        float randomZ = minZ + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxZ - minZ)));
        
        //randomX = 0.0f;
        //randomY = 2.0f;
        //randomZ = 0.0f;
        vector<float> randomPoint;
        randomPoint.push_back(randomX);
        randomPoint.push_back(randomY);
        randomPoint.push_back(randomZ);
        
        myInternalPoints.push_back(randomPoint);
        numInternalPoints++;
        newRandomPts.push_back(glm::vec3(randomX, randomY, randomZ));
        
        const btVector3 newPoint(randomX, randomY, randomZ);
        convexMesh.addPoint(newPoint);
    }
    
    
    return newRandomPts;
}

void Cube::GenerateRandomInternalPoints(int numPoints, std::vector<float> impactPt){
    numRandomPoints = numPoints;
    myInternalPoints.clear();
    myRandomPoints.clear();
    numInternalPoints = 0;
    
    vector<btConvexHullShape> convexHulls;
    //convexHull = btConvexHullShape();
    btConvexHullShape convexMesh;
    convexMesh = btConvexHullShape();
    
    std::vector<float> cubeCenter;
    cubeCenter.push_back((minX+maxX)/2.0f);
    cubeCenter.push_back((minX+maxX)/2.0f);
    cubeCenter.push_back((minX+maxX)/2.0f);
    
    for(int i = 0; i < numPoints; i++){
        
        //http://stackoverflow.com/questions/686353/c-random-float-number-generation
        float randomX = impactPt[0] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[0] + 0.5) - (impactPt[0] - 0.5))));
        float randomY = impactPt[1] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[1] + 0.5) - (impactPt[1] - 0.5))));
        float randomZ = impactPt[2]+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((impactPt[2] + 0.5) - (impactPt[2] - 0.5))));
        
        //randomX = 0.0f;
        //randomY = 2.0f;
        //randomZ = 0.0f;
        vector<float> randomPoint;
        randomPoint.push_back(randomX);
        randomPoint.push_back(randomY);
        randomPoint.push_back(randomZ);
        
        myRandomPoints.push_back(randomPoint);
        
        const btVector3 newPoint(randomX, randomY, randomZ);
        convexMesh.addPoint(newPoint);
        }
    
    
        //generate points within the mesh
        for(int j = 0; j < numRandomPoints; j++) {
            numOfIntersections = 0;
            
            //raycast from each point in myRandomPoints in the direction of center of mesh
            float x = cubeCenter[0] - myRandomPoints[j][0];
            float y = cubeCenter[1] - myRandomPoints[j][1];
            float z = cubeCenter[2] - myRandomPoints[j][2];
        
            glm::vec3 d = glm::vec3(x, y, z);
            glm::vec3 o = glm::vec3(myRandomPoints[j][0], myRandomPoints[j][1], myRandomPoints[j][2]);
            Ray ray;
            ray.orig = o;
            ray.dir = d;
        
            //intersectImpl(ray);
        
            if(myRandomPoints[j][0] <= maxX && myRandomPoints[j][0] >= minX) {
                if(myRandomPoints[j][1] <= maxY && myRandomPoints[j][1] >= minY) {
                    if(myRandomPoints[j][2] <= maxZ && myRandomPoints[j][2] >= minZ) {
                        myInternalPoints.push_back(myRandomPoints[j]);
                        numInternalPoints++;
                    }
                }
            }
        
            /**
            //if the number of intersections is odd, add to internal points.
            if(numOfIntersections %2 == 1) {
                myInternalPoints.push_back(myRandomPoints[j]);
                numInternalPoints++;
            }
             */
    }
    convexHulls.push_back(convexMesh);
}



