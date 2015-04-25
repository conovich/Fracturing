//
//  VoronoiTest.cpp
//  VoronoiTest
//
//  Created by Corey Novich on 4/12/15.
//  Copyright (c) 2015 Corey Novich. All rights reserved.
//

#include "VoronoiTest.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

VoronoiTest::VoronoiTest(){
    
}

//number of blocks that the container is divided into:
const int numX=6,numY=6,numZ=6;

// This function returns a random double between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}
void VoronoiTest::ConvexGeoDecomp(vector<glm::vec3> meshVerts, glm::vec3 POI, std::vector<int> listOfIndices){
    
    glm::vec3 minXYZ = GetMin(meshVerts);
    glm::vec3 maxXYZ = GetMax(meshVerts);
    
    double x_min = minXYZ[0];//GetMin("x", meshVerts);
    double y_min = minXYZ[1];//GetMin("y", meshVerts);
    double z_min = minXYZ[2];//GetMin("z", meshVerts);
    
    double x_max = maxXYZ[0];//GetMax("x", meshVerts);
    double y_max = maxXYZ[1];//GetMax("y", meshVerts);
    double z_max = maxXYZ[2];//GetMax("z", meshVerts);
    
    double cvol=(x_max-x_min)*(y_max-y_min)*(z_max-z_min);
    numCells = POI.x;
    
    // Set up the number of blocks that the container is divided into
    const int n_x=6,n_y=6,n_z=6;
    
    // Set the number of particles that are going to be randomly introduced
    //const int particles=2;
    
    
    
    int i;
    double x,y,z;
    
    // Create a container with the geometry given above, and make it
    // non-periodic in each of the three coordinates. Allocate space for
    // eight particles within each computational block
    container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
                  false,false,false,8);
    
    
    std::vector<float> pot;
    pot.push_back(POI.x);
    pot.push_back(POI.y);
    pot.push_back(POI.z);
    
    // USE PASSED IN ARGUMENTS
    Mesh myMesh = Mesh(meshVerts, listOfIndices, glm::vec3(0, 0, 0), "other");
    myMesh.GenerateRandomInternalPoints(100, pot);
    // Randomly add particles into the container
    //for(i=0;i<particles;i++) {
    for (int i = 0; i < myMesh.numInternalPoints; i++) {
        x = myMesh.myInternalPoints[i][0];
        y = myMesh.myInternalPoints[i][1];
        z = myMesh.myInternalPoints[i][2];
        
        //x=x_min+rnd()*(x_max-x_min);
        //y=y_min+rnd()*(y_max-y_min);
        //z=z_min+rnd()*(z_max-z_min);
        con.put(i,x,y,z);
    }
    
    // Sum up the volumes, and check that this matches the container volume
    double vvol=con.sum_cell_volumes();
    printf("Container volume : %g\n"
           "Voronoi volume   : %g\n"
           "Difference       : %g\n",cvol,vvol,vvol-cvol);
    
    
    
    
    
    
    allCellFaces.clear();
    allCellVerticesToDraw.clear();
    
    voronoicell c;
    double vol=0;
    numCells = 0;
    c_loop_all vl(con);
    std::vector<int> faceVertexIndices;
    std::vector<int> newFaceIndex;
    std::vector<int> edgesPerFace;
    if(vl.start()){
        //numCells = 1;
        do{
            //numCells = 2;
            if(con.compute_cell(c,vl)){
                //numCells = 3;
                vol+=c.volume();
                numCells++;
                //cellFaces = GetCellFaces(c);
                
                edgesPerFace;
                c.face_orders(edgesPerFace);
                
                faceVertexIndices;
                c.face_vertices(faceVertexIndices);
                
                std::vector<double> vertexVector;
                double posCx;
                double posCy;
                double posCz;
                vl.pos(posCx, posCy, posCz);
                //c_loop_base.pos(posC.x, posC.y, posC.z);
                c.vertices(posCx, posCy, posCz, vertexVector);
                //c.vertices(vertexVector); //global verts stored in x,y,z order
                
                
                
                /*
                 for (i = 0 ; i < vertexVector.size(); i++) {
                 if (vertexVector[i] > 1.0f) vertexVector[i] = 1.0f;
                 if (vertexVector[i] < -1.0f) vertexVector[i] = -1.0f;
                 }*/
                
                i = 0;
                cellVerticesToDraw.clear();
                currentCellFaces.clear();
                
                vector<glm::vec3> currentCellVertsVec3;
                currentCellVertsVec3.clear();
                
                while (i < faceVertexIndices.size()) {
                    int numVerts = faceVertexIndices[i];
                    vector<glm::vec3> vertsInFace;
                    for (int m = 0; m < numVerts; m++) {
                        i++;
                        glm::vec3 vertexVec(vertexVector[faceVertexIndices[i]*3], vertexVector[faceVertexIndices[i]*3 + 1], vertexVector[faceVertexIndices[i]*3 + 2]);
                        vertsInFace.push_back(vertexVec);
                        newFaceIndex.push_back(faceVertexIndices[i]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3 + 1]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3 + 2]);
                        
                        //getting vertices in glm::vec3 format... redundant...
                        glm::vec3 currentVert = glm::vec3(vertexVector[faceVertexIndices[i]*3],
                                                          vertexVector[faceVertexIndices[i]*3 + 1],
                                                          vertexVector[faceVertexIndices[i]*3 + 2]);
                        currentCellVertsVec3.push_back(currentVert);
                    }
                    currentCellFaces.push_back(vertsInFace);
                    i++;
                }
                
                
                vector<glm::vec3> cellVertsInMesh; //will be filled with the verts that are in the mesh
                bool isEntirelyInMesh = CheckCellWithinMesh(currentCellVertsVec3, minXYZ, maxXYZ, cellVertsInMesh);
                
                if(isEntirelyInMesh){
            
                    //cellVerticesToDraw = vertexVector;
                    allCellVerticesToDraw.push_back(cellVerticesToDraw);
                    
                    
                    allCellFaces.push_back(currentCellFaces);
                    
                }
                else{
                    
                    int a = 0;
                    
                }
            
            }
        }while(vl.inc());
    }
    
    FILE * pFile;
    //numCells++;
    pFile = fopen ("myfile.txt","w");
    con.print_custom("List of Vertices: %t \n  Next: %p", pFile);
    fclose(pFile);
    std::cout<<"numcells: "<<std::endl;
    std::cout<<numCells<<std::endl;
    
}

//returns if true/false if the cell is entirely inside of the mesh
//fills the cellVertsInMesh vector with the cells that *are* inside the mesh regardless of the cell being entirely contained in the mesh
bool VoronoiTest::CheckCellWithinMesh(vector<glm::vec3> cellVerts, glm::vec3 minXYZ, glm::vec3 maxXYZ, vector<glm::vec3> &cellVertsInMesh){
    cellVertsInMesh.clear();
    
    bool isEntirelyInsideMesh = true;
    for(int i = 0; i < cellVerts.size(); i++){
        glm::vec3 currentCellVert = cellVerts[i];
        //if outside the minXYZ bounds
        if(currentCellVert[0] < minXYZ[0] || currentCellVert[1] < minXYZ[1] || currentCellVert[2] < minXYZ[2]){
            isEntirelyInsideMesh = false;
        }
        //if outside maxXYZ bounds
        else if(currentCellVert[0] > maxXYZ[0] || currentCellVert[1] > maxXYZ[1] || currentCellVert[2] > maxXYZ[2]){
            isEntirelyInsideMesh = false;
        }
        else{ //inside the bounds!
            cellVertsInMesh.push_back(currentCellVert);
        }
    }
    
    return isEntirelyInsideMesh;
}

vector<glm::vec3> VoronoiTest::GetMeshVertsInCell(vector<glm::vec3> cellVerts, vector<glm::vec3> meshVerts){
    vector<glm::vec3> meshVertsInCell;
    
    glm::vec3 minXYZ = GetMin(cellVerts);
    glm::vec3 maxXYZ = GetMax(cellVerts);
    
    
    for(int i = 0; i < meshVerts.size(); i++){
        glm::vec3 currentMeshVert = meshVerts[i];
        
        //if inside the minXYZ bounds
        if(currentMeshVert[0] > minXYZ[0] && currentMeshVert[1] > minXYZ[1] && currentMeshVert[2] > minXYZ[2]){
            //if inside the maxXYZ bounds
            if(currentMeshVert[0] < maxXYZ[0] && currentMeshVert[1] < maxXYZ[1] && currentMeshVert[2] < maxXYZ[2]){
                //inside the bounds!
                meshVertsInCell.push_back(currentMeshVert);
            }
        }
        
        
    }
    
    return meshVertsInCell;
}


vector<glm::vec3> VoronoiTest::GetCellMeshIntersectionPoints(vector<glm::vec3> cellVerts, vector<glm::vec3> meshVerts){
    vector<glm::vec3> intersectionVerts;
    
    return intersectionVerts;
}


glm::vec3 VoronoiTest::GetMin(vector<glm::vec3> meshVerts){
    double minX = 0;
    double minY = 0;
    double minZ = 0;
    
    
    for(int i = 0; i < meshVerts.size(); i++){
        glm::vec3 currentVert = meshVerts.at(i);
        if(i == 0){
            minX = (double)currentVert[0];
            minY = (double)currentVert[1];
            minZ = (double)currentVert[2];
        }
        else{
            if(currentVert[0] < minX){
                minX = (double)currentVert[0];
            }
            if(currentVert[1] < minY){
                minY = (double)currentVert[1];
            }
            if(currentVert[2] < minZ){
                minZ = (double)currentVert[2];
            }
        }
    }
    
    
    
    glm::vec3 minXYZ = glm::vec3(minX, minY, minZ);
    return minXYZ;
}

glm::vec3 VoronoiTest::GetMax(vector<glm::vec3> meshVerts){
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;
    
    
    for(int i = 0; i < meshVerts.size(); i++){
        glm::vec3 currentVert = meshVerts.at(i);
        if(i == 0){
            maxX = (double)currentVert[0];
            maxY = (double)currentVert[1];
            maxZ = (double)currentVert[2];
        }
        else{
            if(currentVert[0] > maxX){
                maxX = (double)currentVert[0];
            }
            if(currentVert[1] > maxY){
                maxY = (double)currentVert[1];
            }
            if(currentVert[2] > maxZ){
                maxZ = (double)currentVert[2];
            }
        }
    }
    
    
    
    glm::vec3 maxXYZ = glm::vec3(maxX, maxY, maxZ);
    return maxXYZ;
}




void VoronoiTest::CubeExample(glm::vec3 POI){
    const double x_min=-1,x_max=1;
    const double y_min=-1,y_max=1;
    const double z_min=-1,z_max=1;
    const double cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
    
    // Set up the number of blocks that the container is divided into
    const int n_x=6,n_y=6,n_z=6;
    
    // Set the number of particles that are going to be randomly introduced
    const int particles=3;
    
    
    
    int i;
	double x,y,z;
    
	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for
	// eight particles within each computational block
	container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
                  false,false,false,8);
    
    std::vector<glm::vec3> listOfVerts;
    listOfVerts.push_back(glm::vec3(-1, 1, -1));
    listOfVerts.push_back(glm::vec3(1, 1, -1));
    listOfVerts.push_back(glm::vec3(1, 1, 1));
    listOfVerts.push_back(glm::vec3(-1, 1, 1));
    listOfVerts.push_back(glm::vec3(-1, -1, -1));
    listOfVerts.push_back(glm::vec3(1, -1, -1));
    listOfVerts.push_back(glm::vec3(1, -1, 1));
    listOfVerts.push_back(glm::vec3(-1, -1, 1));
    //myCube = Cube(listOfVerts);
    //myCube = Cube();
    std::vector<float> pot;
    pot.push_back(POI.x);
    pot.push_back(POI.y);
    pot.push_back(POI.z);
    //myCube.GenerateRandomInternalPoints(500, pot);
    
    std::vector<int> listOfIndices;
    listOfIndices.push_back(1);
    listOfIndices.push_back(2);
    listOfIndices.push_back(6);
    
    listOfIndices.push_back(1);
    listOfIndices.push_back(5);
    listOfIndices.push_back(6);
    
    listOfIndices.push_back(2);
    listOfIndices.push_back(7);
    listOfIndices.push_back(6);
    
    listOfIndices.push_back(3);
    listOfIndices.push_back(7);
    listOfIndices.push_back(6);
    
    listOfIndices.push_back(3);
    listOfIndices.push_back(7);
    listOfIndices.push_back(8);
    
    listOfIndices.push_back(3);
    listOfIndices.push_back(4);
    listOfIndices.push_back(8);
    
    listOfIndices.push_back(1);
    listOfIndices.push_back(5);
    listOfIndices.push_back(8);
    
    listOfIndices.push_back(4);
    listOfIndices.push_back(5);
    listOfIndices.push_back(8);
    
    listOfIndices.push_back(1);
    listOfIndices.push_back(4);
    listOfIndices.push_back(3);
    
    listOfIndices.push_back(1);
    listOfIndices.push_back(2);
    listOfIndices.push_back(3);
    
    listOfIndices.push_back(5);
    listOfIndices.push_back(8);
    listOfIndices.push_back(7);
    
    listOfIndices.push_back(5);
    listOfIndices.push_back(6);
    listOfIndices.push_back(7);
    
    // USE PASSED IN ARGUMENTS
    Mesh myMesh = Mesh(listOfVerts, listOfIndices, glm::vec3(0, 0, 0), "cube");
    myMesh.GenerateRandomInternalPoints(500, pot);
    //double x_guy = GetMin("x", listOfVerts);
    
	// Randomly add particles into the container
	for(i=0;i<myMesh.numInternalPoints;i++) {
        x = myMesh.myInternalPoints[i][0];
        y = myMesh.myInternalPoints[i][1];
        z = myMesh.myInternalPoints[i][2];
        
		//x=x_min+rnd()*(x_max-x_min);
		//y=y_min+rnd()*(y_max-y_min);
		//z=z_min+rnd()*(z_max-z_min);
		con.put(i,x,y,z);
	}
    
    /*con.put(0,0.1,0.7,0.7);
    con.put(1,0.2,-0.4,0.2);
    con.put(2,-0.4,0.2,0.2);
    con.put(3,-0.8,-0.9,0.5);
    
    con.put(4,0.3,0.9,-0.4);
    con.put(5,0.5,-0.7,-0.3);
    con.put(6,-0.8,-0.2,-0.6);
    con.put(7,-0.1,0.4,-0.9);
    
    con.put(8,0.5,0.3,-0.3);
    con.put(9,0.6,-0.1,-0.5);
    con.put(10,-0.7,-0.4,-0.6);
    con.put(11,-0.7,0.5,-0.6);*/
    
	// Sum up the volumes, and check that this matches the container volume
	double vvol=con.sum_cell_volumes();
	printf("Container volume : %g\n"
	       "Voronoi volume   : %g\n"
	       "Difference       : %g\n",cvol,vvol,vvol-cvol);
    

    
    
    
    
    allCellFaces.clear();
    allCellVerticesToDraw.clear();
    
    voronoicell c;
    double vol=0;
    numCells = 0;
    c_loop_all vl(con);
    std::vector<int> faceVertexIndices;
    std::vector<int> newFaceIndex;
    std::vector<int> edgesPerFace;
    if(vl.start()){
        do{
            if(con.compute_cell(c,vl)){
                vol+=c.volume();
                numCells++;
                //cellFaces = GetCellFaces(c);
                
                edgesPerFace;
                c.face_orders(edgesPerFace);
                
                faceVertexIndices;
                c.face_vertices(faceVertexIndices);
                
                std::vector<double> vertexVector;
                double posCx;
                double posCy;
                double posCz;
                vl.pos(posCx, posCy, posCz);
                //c_loop_base.pos(posC.x, posC.y, posC.z);
                c.vertices(posCx, posCy, posCz, vertexVector);
                //c.vertices(vertexVector); //global verts stored in x,y,z order
                
                
                
                
                for (i = 0 ; i < vertexVector.size(); i++) {
                    if (vertexVector[i] > 1.0f) vertexVector[i] = 1.0f;
                    if (vertexVector[i] < -1.0f) vertexVector[i] = -1.0f;
                }
                
                
                
                
                //AHHHHHH//
                //vector<vector<glm::vec3>> currentCellFaces;
                
                i = 0;
                cellVerticesToDraw.clear();
                currentCellFaces.clear();
                while (i < faceVertexIndices.size()) {
                    int numVerts = faceVertexIndices[i];
                    vector<glm::vec3> vertsInFace;
                    for (int m = 0; m < numVerts; m++) {
                        i++;
                        glm::vec3 vertexVec(vertexVector[faceVertexIndices[i]*3], vertexVector[faceVertexIndices[i]*3 + 1], vertexVector[faceVertexIndices[i]*3 + 2]);
                        vertsInFace.push_back(vertexVec);
                        newFaceIndex.push_back(faceVertexIndices[i]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3 + 1]);
                        cellVerticesToDraw.push_back(vertexVector[faceVertexIndices[i]*3 + 2]);
                    }
                    currentCellFaces.push_back(vertsInFace);
                    i++;
                }
                //cellVerticesToDraw = vertexVector;
                allCellVerticesToDraw.push_back(cellVerticesToDraw);
                
                
                
                
                
                
                //int numFaces = c.number_of_faces();
                
                //vector<vector<glm::vec3>> currentCellFaces;
                
                //currentCellFaces = GetFaceVertices(edgesPerFace, newFaceIndex, vertexVector, numFaces);
                allCellFaces.push_back(currentCellFaces);
            }
        }while(vl.inc());
    }
    
    FILE * pFile;
    
    pFile = fopen ("myfile.txt","w");
    con.print_custom("List of Vertices: %t \n  Next: %p", pFile);
    fclose(pFile);
    std::cout<<"numcells: "<<std::endl;
    std::cout<<numCells<<std::endl;
    
}


void VoronoiTest::ComputeVoronoiDecompCube(Cube hitCube, vector<glm::vec3> internalRandomPoints){

    double maxX = hitCube.maxX;
    double maxY = hitCube.maxY;
    double maxZ = hitCube.maxZ;
    
    double minX = hitCube.minX;
    double minY = hitCube.minY;
    double minZ = hitCube.minZ;
    
    
    
    
    //cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
    double cubeVolume = ( maxX - minX ) * ( maxY - minY ) * ( maxZ - minZ );

    
    int i;
    
	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for
	// eight particles within each computational block
	
    container myContainer(minX,maxX,minY,maxY,minZ,maxZ,numX,numY,numZ,false,false,false,8);
    
    // Add particles into the container
    for(i = 0; i < internalRandomPoints.size(); i++){
        glm::vec3 currentPoint = internalRandomPoints[i];
        myContainer.put(i,currentPoint[0],currentPoint[1],currentPoint[2]);
    }
    
    double voronoiVolume = myContainer.sum_cell_volumes();
	printf("Container volume : %g\n"
	       "Voronoi volume   : %g\n"
	       "Difference       : %g\n",cubeVolume,voronoiVolume,voronoiVolume-cubeVolume);
    
    
    //vector<voronoicell> myCells = GetCells(myContainer);
    //GetCells(myContainer);
    
    //for each cell...
    /*for( int i = 0; i < myCells.size(); i++){
        GetCellFaces(myCells.at(i));
    }*/
    
    
    
    //vector<voronoicell> myCells;
    
    //a vector of cells where...
        //...each cell has a vector of faces...
            //...which has a vector of vertices.
    allCellFaces.clear();
    
    voronoicell c;
    double vol=0;
    int numCells = 0;
    c_loop_all vl(myContainer);
     
    if(vl.start()){
        while(vl.inc()){
            if(myContainer.compute_cell(c,vl)){
                vol+=c.volume();
                numCells++;
                //cellFaces = GetCellFaces(c);
                 
                std::vector<int> edgesPerFace;
                c.face_orders(edgesPerFace);
                 
                std::vector<int> faceVertexIndices;
                c.face_vertices(faceVertexIndices);
                 
                std::vector<double> vertexVector;
                c.vertices(vertexVector); //global verts stored in x,y,z order
                std::vector<int> vertexOrder;
                c.vertex_orders(vertexOrder);
                
                int numFaces = c.number_of_faces();
                
                vector<vector<glm::vec3>> currentCellFaces;
                
                currentCellFaces = GetFaceVertices(edgesPerFace, faceVertexIndices, vertexVector, numFaces);
                allCellFaces.push_back(currentCellFaces);
            }
        }
    }
    
    std::cout<<"numcells: "<<std::endl;
    std::cout<<numCells<<std::endl;
    
    
    //con.print_custom("ID=%i, pos=(%x,%y,%z), vertices=%w, edges=%g, faces=%s","packing.custom1");
    //con.draw_cells_gnuplot("test.gnu");
}


vector<vector<glm::vec3>> VoronoiTest::GetFaceVertices(std::vector<int> edgesPerFace, std::vector<int> faceVertexIndices, std::vector<double> vertexVector, int numFaces){ //returns a vector of vertices for each face
    vector<vector<glm::vec3>> cellFaces;
    
        
    /*std::vector<int> edgesPerFace;
    myCell.face_orders(edgesPerFace);
    
    std::vector<int> faceVertexIndices;
    myCell.face_vertices(faceVertexIndices);
    
    std::vector<double> vertexVector;
    myCell.vertices(vertexVector); //global verts stored in x,y,z order
    
    
    int numFaces = myCell.number_of_faces();*/

    //for each face in the cell
    for(int j = 0; j < numFaces; j++){
        
        vector<glm::vec3> currentFaceVertices;
        
        int currentNumEdgesInFace = edgesPerFace.at(j);
        
        //for each edge, add two vertices to the current face's list of verts
        for(int k = 0; k < currentNumEdgesInFace; k++){
            
            int startVertIndex = faceVertexIndices[k*2];
            int endVertIndex = faceVertexIndices[(k*2)+1];
            
            double startX = vertexVector.at(startVertIndex);
            double startY = vertexVector.at(startVertIndex + 1);
            double startZ = vertexVector.at(startVertIndex + 2);
            
            double endX = vertexVector.at(endVertIndex);
            double endY = vertexVector.at(endVertIndex + 1);
            double endZ = vertexVector.at(endVertIndex + 2);
            
            
            glm::vec3 startVertex = glm::vec3(startX, startY, startZ);
            glm::vec3 endVertex = glm::vec3(endX, endY, endZ);
            
            currentFaceVertices.push_back(startVertex);
            currentFaceVertices.push_back(endVertex);
             
            
            
        }
        cellFaces.push_back(currentFaceVertices);
    }
    
    return cellFaces;
}


void VoronoiTest::DrawVoronoiEdges(){
    
    /* We tell we want to draw lines */
    glBegin(GL_LINES);
    
    unsigned long numCells = allCellFaces.size();
    for(int i = 0; i < numCells; i++){
        
        vector<vector<glm::vec3>> currentCellFaces = allCellFaces.at(i);
        unsigned long numFaces = currentCellFaces.size();
        for(int j = 0; j < numFaces; j++){
            
            vector<glm::vec3> currentFace = currentCellFaces.at(j);
            unsigned long numVerts = currentFace.size();
            for(int k = 0; k < numVerts; k+=2){
                
                //DRAW EACH EDGE HERE
                glm::vec3 startVert = currentFace.at(k);
                glm::vec3 endVert;
                if (k+1 != numVerts) {
                    endVert = currentFace.at(k+1);
                }
                else {
                    endVert = currentFace.at(0);
                }
                //top face
                if (i == 0){
                    glColor3f(0, 1, 0); glVertex3f(startVert[0], startVert[1], startVert[2]);
                    glColor3f(0, 1, 0); glVertex3f(endVert[0], endVert[1],  endVert[2]);
                }
                else {
                    glColor3f(0, 0, 1); glVertex3f(startVert[0], startVert[1], startVert[2]);
                    glColor3f(0, 0, 1); glVertex3f(endVert[0], endVert[1],  endVert[2]);

                }
                
            }
            
        }
        
    }
    
    //end drawing//
    glEnd();
}

void VoronoiTest::DrawVertices(std::vector<double> vertexVector, int R, int G, int B){
    glBegin(GL_POINTS);
    
    for(int i = 0; i < vertexVector.size(); i+=3){
        double X = vertexVector.at(i);
        double Y = vertexVector.at(i + 1);
        double Z = vertexVector.at(i + 2);

        glColor3f(R, G, B); glVertex3f(X, Y, Z);
        
    }
    
    
    //end drawing//
    glEnd();
}

void VoronoiTest::DrawAllVertices(vector<std::vector<double>> vertexVectors){
    glBegin(GL_POINTS);
    
    int R = 0;
    int G = 0;
    int B = 0;
    
    for(int j = 0; j < vertexVectors.size(); j++){
        
        switch (j){
            case 0:
                R = 1;
                G = 0;
                B = 0;
                break;
            case 1:
                R = 0;
                G = 1;
                B = 0;
                break;
            case 2:
                R = 1;
                G = 1;
                B = 0;
                break;
            case 3:
                R = 0;
                G = 0;
                B = 1;
                break;
            case 4:
                R = 1;
                G = 0;
                B = 1;
                break;
            case 5:
                R = 0;
                G = 1;
                B = 1;
                break;
            case 6:
                R = 1;
                G = 1;
                B = 1;
                break;
            case 7:
                R = 0.5;
                G = 0;
                B = 1;
                break;
            case 8:
                R = 0;
                G = 0.5;
                B = 1;
                break;
            case 9:
                R = 0.5;
                G = 1;
                B = 0;
                break;
            case 10:
                R = 1;
                G = 0.5;
                B = 0;
                break;
            case 11:
                R = 1;
                G = 0;
                B = 0.5;
                break;
            case 12:
                R = 0;
                G = 1;
                B = 0.5;
                break;
            case 13:
                R = 0.5;
                G = 1;
                B = 0.5;
                break;
            case 14:
                R = 0.5;
                G = 0.5;
                B = 1;
                break;
            case 15:
                R = 1;
                G = 0.5;
                B = 0.5;
                break;
            case 16:
                R = 0.2;
                G = 0.5;
                B = 0.8;
                break;
            case 17:
                R = 0.8;
                G = 0.5;
                B = 0.2;
                break;
            case 18:
                R = 0.8;
                G = 0.2;
                B = 0.5;
                break;
        }
        
        
        
        vector<double> vertexVector = vertexVectors.at(j);
        for(int i = 0; i < vertexVector.size(); i+=3){
            double X = vertexVector.at(i);
            double Y = vertexVector.at(i + 1);
            double Z = vertexVector.at(i + 2);
            
            glColor3f(R, G, B); glVertex3f(X, Y, Z);
            
        }
    }
    
    
    //end drawing//
    glEnd();
}

void VoronoiTest::DrawVoronoiVertices(){
    
    /* We tell we want to draw lines */
    glBegin(GL_POINTS);
    
    float R = 0.1f;
    float G = 0.1f;
    float B = 0.1f;
    
    unsigned long numCells = allCellFaces.size();
    for(int i = 0; i < numCells; i++){
        
        if(i == 0){
            R = 0;
            G = 0;
            B = 0;
        }
        switch (i){
            case 0:
                R = 1;
                G = 0;
                B = 0;
                break;
            case 1:
                R = 0;
                G = 1;
                B = 0;
                break;
            case 2:
                R = 1;
                G = 1;
                B = 0;
                break;
            case 3:
                R = 0;
                G = 0;
                B = 1;
                break;
            case 4:
                R = 1;
                G = 0;
                B = 1;
                break;
            case 5:
                R = 0;
                G = 1;
                B = 1;
                break;
            case 6:
                R = 1;
                G = 1;
                B = 1;
                break;
            case 7:
                R = 0.5;
                G = 0;
                B = 1;
                break;
            case 8:
                R = 0;
                G = 0.5;
                B = 1;
                break;
            case 9:
                R = 0.5;
                G = 1;
                B = 0;
                break;
            case 10:
                R = 1;
                G = 0.5;
                B = 0;
                break;
            case 11:
                R = 1;
                G = 0;
                B = 0.5;
                break;
            case 12:
                R = 0;
                G = 1;
                B = 0.5;
                break;
            case 13:
                R = 0.5;
                G = 1;
                B = 0.5;
                break;
            case 14:
                R = 0.5;
                G = 0.5;
                B = 1;
                break;
            case 15:
                R = 1;
                G = 0.5;
                B = 0.5;
                break;
            case 16:
                R = 0.2;
                G = 0.5;
                B = 0.8;
                break;
            case 17:
                R = 0.8;
                G = 0.5;
                B = 0.2;
                break;
            case 18:
                R = 0.8;
                G = 0.2;
                B = 0.5;
                break;
        }
        
        vector<vector<glm::vec3>> currentCellFaces = allCellFaces.at(i);
        unsigned long numFaces = currentCellFaces.size();
        for(int j = 0; j < numFaces; j++){
            
            vector<glm::vec3> currentFace = currentCellFaces.at(j);
            unsigned long numVerts = currentFace.size();
            for(int k = 0; k < numVerts; k+=2){
                
                //DRAW EACH EDGE HERE
                glm::vec3 startVert = currentFace.at(k);
                glm::vec3 endVert = currentFace.at(k+1);
                
                //top face
                glColor3f(R, G, B); glVertex3f(startVert[0], startVert[1], startVert[2]);
                glColor3f(R, G, B); glVertex3f(endVert[0], endVert[1],  endVert[2]);
                
                
            }
            
        }
        
        
        if(i == 0){
            R = 0;
            G = 0;
            B = 0;
        }
        if(R >= 1.0f){
            if(G >= 1.0f){
                B += 0.1f;
            }
            else{
                G += 0.1f;
            }
        }
        else{
            R += 0.1f;
        }
        
    }
    
    //end drawing//
    glEnd();
}