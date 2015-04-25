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
#include <vector>
#include "Mesh.h"
#include "container.hh"



//using namespace std;
using namespace voro;

class VoronoiTest{
public:
    VoronoiTest();
    
    
    
    //%P
    //A list of the vertices of the Voronoi cell in the format (x,y,z), relative to the global coordinate system.
    
    glm::vec3 GetMin(vector<glm::vec3> meshVerts);
    glm::vec3 GetMax(vector<glm::vec3> meshVerts);
    
    
    void ConvexGeoDecomp(std::vector<glm::vec3> meshVerts, glm::vec3 POI, std::vector<int> listOfIndices);
    bool CheckCellWithinMesh(vector<glm::vec3> cellVerts, glm::vec3 minXYZ, glm::vec3 maxXYZ, vector<glm::vec3> &cellVertsInMesh);
    vector<glm::vec3> GetMeshVertsInCell(vector<glm::vec3> cellVerts, vector<glm::vec3> meshVerts);
    //vector<glm::vec3> GetCellVertsInMesh(vector<glm::vec3> cellVerts, vector<glm::vec3> meshVerts);
    vector<glm::vec3> GetCellMeshIntersectionPoints(vector<glm::vec3> cellVerts, vector<glm::vec3> meshVerts);
    
    
    
    void CubeExample(glm::vec3);
    
    void ComputeVoronoiDecompCube(Cube hitCube, vector<glm::vec3> internalRandomPoints);
    
    vector<vector<glm::vec3>> GetFaceVertices(std::vector<int> edgesPerFace, std::vector<int> faceVertexIndices, std::vector<double> vertexVector, int numFaces);
    
    
    vector<vector<vector<glm::vec3>>> allCellFaces;
    double x_min;
    int numCells; //number of cells computed in voronoi decomp or cube example
    int numCellVerts;
    int numFaceVerts;//number of verts of all of the faces --> ex: a cube has 4 verts per face, 24 verts total
    vector<vector<glm::vec3>> currentCellFaces;
    
    //OPEN GL DRAW FUNCTION
    void DrawVoronoiEdges();
    void DrawVoronoiVertices();
    void DrawVertices(std::vector<double> vertexVector, int R, int G, int B);
    void DrawAllVertices(vector<std::vector<double>> vertexVectors);
    void DrawEdges(std::vector<double> vertexVector, int R, int G, int B);
    vector<double> cellVerticesToDraw;
    vector<vector<double>> allCellVerticesToDraw;
    
    
};

#endif /* defined(__VoronoiTest__VoronoiTest__) */
