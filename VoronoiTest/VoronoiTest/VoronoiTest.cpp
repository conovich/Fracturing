//
//  VoronoiTest.cpp
//  VoronoiTest
//
//  Created by Corey Novich on 4/12/15.
//  Copyright (c) 2015 Corey Novich. All rights reserved.
//

#include "VoronoiTest.h"

VoronoiTest::VoronoiTest(){
    
}

//number of blocks that the container is divided into:
const int numX=6,numY=6,numZ=6;

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
    
    //for each cell...
    /*for( int i = 0; i < myCells.size(); i++){
        GetCellFaces(myCells.at(i));
    }*/
    
    //con.print_custom("ID=%i, pos=(%x,%y,%z), vertices=%w, edges=%g, faces=%s","packing.custom1");
}

vector<voronoicell> VoronoiTest::GetCells(container myContainer){
    vector<voronoicell> myCells;
    
    vector<vector<glm::vec3>> cellFaces;
    
    voronoicell c;
	double vol=0;
    c_loop_all vl(myContainer);
    
	if(vl.start()){
        while(vl.inc()){
            if(myContainer.compute_cell(c,vl)){
                vol+=c.volume();
                testFunction();
                //voronoicell newCell = c;
                //myCells.push_back(newCell);
                //cellFaces = GetCellFaces(c);
            }
        }
    }
    
    return myCells;
}

void VoronoiTest::testFunction(){
    std::cout<<"BLARG"<<std::endl;
}

vector<vector<glm::vec3>> VoronoiTest::GetCellFaces(voronoicell myCell){ //returns a vector of vertices for each face
    vector<vector<glm::vec3>> cellFaces;
    
        
    std::vector<int> edgesPerFace;
    myCell.face_orders(edgesPerFace);
    
    std::vector<int> faceVertexIndices;
    myCell.face_vertices(faceVertexIndices);
    
    std::vector<double> vertexVector;
    myCell.vertices(vertexVector); //global verts stored in x,y,z order
    
    
    int numFaces = myCell.number_of_faces();

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
            
            double endX = vertexVector.at(startVertIndex);
            double endY = vertexVector.at(startVertIndex + 1);
            double endZ = vertexVector.at(startVertIndex + 2);
            
            
            glm::vec3 startVertex = glm::vec3(startX, startY, startZ);
            glm::vec3 endVertex = glm::vec3(endX, endY, endZ);
            
            currentFaceVertices.push_back(startVertex);
            currentFaceVertices.push_back(endVertex);
        }
        cellFaces.push_back(currentFaceVertices);
    }
    
    return cellFaces;
}