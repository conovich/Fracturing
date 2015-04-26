//
//  ThreeDIntersection.cpp
//  VoronoiTest
//
//  Created by Megan Moore on 4/25/15.
//  Copyright (c) 2015 Megan Moore. All rights reserved.
//

#include "ThreeDIntersection.h"
#include "Ray.h"
#include "Mesh.h"



void ThreeDIntersection::newConvexHull(std::vector<glm::vec3> verts, std::vector<int> inds, std::vector<glm::vec3> normals){
    
    
}


std::vector<glm::vec3> ThreeDIntersection::GetNormals() {
    std::vector<glm::vec3> normals;
    
    for (int i = 0; i < tetraInds.size(); i+=3) {
        glm::vec3 v0 = tetraVerts[tetraInds[i]];
        glm::vec3 v1 = tetraVerts[tetraInds[i + 1]];
        glm::vec3 v2 = tetraVerts[tetraInds[i + 2]];
        glm::vec3 start = v0 - v1;
        glm::vec3 end = v2 - v1;
        glm::vec3 norm = glm::cross(start, end);
        normals.push_back(norm);
    }
    
    
    
    return normals;
}

void ThreeDIntersection::GetVertsInTetra(){
   
    std::vector<int> indsInTetra;
    for (int i = 0; i < cubeVerts.size(); i++) {
        
            int numOfIntersections = 0;
            
            //raycast from each point in myRandomPoints in the direction of center of mesh
        float centerX = 0;
        float centerY = 0;
        float centerZ = 0;
        for(int j = 0; j < tetraVerts.size(); j++) {
            
            centerX += tetraVerts[j][0];
            centerY += tetraVerts[j][1];
            centerZ += tetraVerts[j][2];
        }
        glm::vec3 center = glm::vec3(centerX/tetraVerts.size(), centerY/tetraVerts.size(), centerZ/tetraVerts.size());
            float x = center.x - cubeVerts[i][0];
            float y = center.y - cubeVerts[i][1];
            float z = center.z - cubeVerts[i][2];
            
            glm::vec3 d = glm::vec3(x, y, z);
            glm::vec3 o = glm::vec3(cubeVerts[i][0], cubeVerts[i][1], cubeVerts[i][2]);
            Ray ray;
            ray.orig = o;
            ray.dir = d;
            
        
            numOfIntersections = intersectionImpl(ray);
            
            //if the number of intersections is odd, add to internal points.
        if(numOfIntersections == 1) {//%2 == 1) {
                vertsInTetra.push_back(cubeVerts[i]);
                indsInTetra.push_back(i);
            }
        
    
    
    }
    for (int i = 0; i < vertsInTetra.size(); i++) {
        std::cout << "Vert in Tetra:" << indsInTetra[i] << endl;
        
    }
}



int ThreeDIntersection::intersectionImpl(const Ray &ray)
{
    Intersection inter;
    inter.t = -1;
    //Intersection smallest_inter;
    //smallest_inter.t = -1;
    
    //clear the number of intersections
    int numOfIntersections = 0;
    
    //loop through the indices
    for(int i = 0; i < tetraInds.size(); i+=3)
    {
        glm::vec3 p0 = tetraVerts[tetraInds[i]];
        glm::vec3 p1 = tetraVerts[tetraInds[i+1]];
        glm::vec3 p2 = tetraVerts[tetraInds[i+2]];
    
        inter = triangleIntersect(p0, p1, p2, ray); //check every face
        //if(smallest_inter.t == -1) smallest_inter = inter; //set smallest_inter to the first intersection
        if(inter.t != -1) {
            //smallest_inter = inter;
            numOfIntersections++;  //only add to numOfIntersections if t != -1
        }
        
    }
    return numOfIntersections;
}


Intersection ThreeDIntersection::triangleIntersect(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, const Ray &ray)
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






void ThreeDIntersection::DrawCube(){
    std::vector<glm::vec3> Verts = cubeVerts;
    std::vector<int> Inds = cubeInds;
    glBegin(GL_LINES);
    for (int i = 0; i < Inds.size(); i+=3) {
        glm::vec3 startVert = Verts[Inds[i]];
        glm::vec3 endVert = Verts[Inds[i + 1]];
        glColor3f(0, 1, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(0, 1, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
        startVert = Verts[Inds[i+1]];
        endVert = Verts[Inds[i+2]];
        glColor3f(0, 1, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(0, 1, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
        startVert = Verts[Inds[i+2]];
        endVert = Verts[Inds[i]];
        glColor3f(0, 1, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(0, 1, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
    }


    glEnd();
    
}

void ThreeDIntersection::DrawTetra(){
    std::vector<glm::vec3> Verts = tetraVerts;
    std::vector<int> Inds = tetraInds;
    /*
    glBegin(GL_LINES);
    for (int i = 0; i < Inds.size(); i+=3) {
        glm::vec3 startVert = Verts[Inds[i]];
        glm::vec3 endVert = Verts[Inds[i + 1]];
        glColor3f(1, 0, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(1, 0, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
        startVert = Verts[Inds[i+1]];
        endVert = Verts[Inds[i+2]];
        glColor3f(1, 0, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(1, 0, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
        startVert = Verts[Inds[i+2]];
        endVert = Verts[Inds[i]];
        glColor3f(1, 0, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
        glColor3f(1, 0, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
    }
    */
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < Inds.size(); i+=3) {
        glColor3f(0, 0, 1);
        glVertex3f(Verts[Inds[i]][0], Verts[Inds[i]][1], Verts[Inds[i]][2]);
        glVertex3f(Verts[Inds[i+1]][0], Verts[Inds[i+1]][1], Verts[Inds[i+1]][2]);
        glVertex3f(Verts[Inds[i+2]][0], Verts[Inds[i+2]][1], Verts[Inds[i+2]][2]);
    }
    glEnd();

}









