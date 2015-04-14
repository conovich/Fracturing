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
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>


#define NUM_ENDS 2           /* number of end "points" to draw */
int myEnds[NUM_ENDS][2];       /* array of 2D points */

Mesh::Mesh(){
    
    
}

void Mesh::DrawWireframe(){
    
    
}

void Mesh::DrawRandomPoints(){
    
}

void Cube::DrawRandomPoints(){
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    std::vector<float> point;
    int i = 0;
    std::cout<<myRandomPoints.size()<<std::endl;
    for(i = 0; i < numRandomPoints; i++){ //FOR SOME REASON .SIZE() WASN'T WORKING
        point = myRandomPoints.at(i);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(point.at(0), point.at(1), point.at(2));
    }

    glEnd();
}

Cube::Cube(){
    //top face
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

void Cube::GenerateRandomInternalPoints(int numPoints){
    numRandomPoints = numPoints;
    
    myRandomPoints.clear();
    vector<btConvexHullShape> convexHulls;
    //convexHull = btConvexHullShape();
    btConvexHullShape convexMesh;
    convexMesh = btConvexHullShape();
    
    for(int i = 0; i < numPoints; i++){
        
        //http://stackoverflow.com/questions/686353/c-random-float-number-generation
        
        float randomX = minX + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxX-minX)));
        float randomY = minY + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxY-minY)));
        float randomZ = minZ + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxZ-minZ)));
        
        vector<float> randomPoint;
        randomPoint.push_back(randomX);
        randomPoint.push_back(randomY);
        randomPoint.push_back(randomZ);
        
        myRandomPoints.push_back(randomPoint);
        
        const btVector3 newPoint(randomX, randomY, randomZ);
        
        convexMesh.addPoint(newPoint);
    }
    convexHulls.push_back(convexMesh);
}