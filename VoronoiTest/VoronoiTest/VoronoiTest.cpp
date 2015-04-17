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
	
    //container con(minX,maxX,minY,maxY,minZ,maxZ,numX,numY,numZ,false,false,false,8);
    
    /*// Add particles into the container
    for(i = 0; i < internalRandomPoints.size(); i++){
        std::vector<float> currentPoint = internalRandomPoints.at(i);
        con.put(i,currentPoint[0],currentPoint[1],currentPoint[2]);
    }*/
    // Add random cube particles into the container
    for(i = 0; i < hitCube.myRandomPoints.size(); i++){
        std::vector<float> currentPoint = hitCube.myRandomPoints.at(i);
        //con.put(i,currentPoint[0],currentPoint[1],currentPoint[2]);
    }
    
    /*double voronoiVolume = con.sum_cell_volumes();
	printf("Container volume : %g\n"
	       "Voronoi volume   : %g\n"
	       "Difference       : %g\n",cubeVolume,voronoiVolume,voronoiVolume-cubeVolume);
    
    con.print_custom("ID=%i, pos=(%x,%y,%z), vertices=%w, edges=%g, faces=%s","packing.custom1");
    */
}