/* ============================================================================
 **
 ** Demonstration of spinning cube
 ** Copyright (C) 2005  Julien Guertault
 **
 ** This program is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU General Public License
 ** as published by the Free Software Foundation; either version 2
 ** of the License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 **
 ** ========================================================================= */

#include	<stdlib.h>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include	<math.h>

#include "Mesh.h"
#include "VoronoiTest.h"


Cube myCube;
Mesh myMesh;
VoronoiTest voroTester;

/*
 ** Function called to update rendering
 */
void		DisplayFunc(void)
{
    static float alpha = 0;
    
    /* Clear the buffer, clear the matrix */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* A step backward, then spin the cube */
    glTranslatef(0, 0, -10);
    //glRotatef(30, 1, 0, 0);
    glRotatef(alpha, 0, 1, 0);
    
    
    //myCube.DrawWireframe();
    //myCube.DrawInternalPoints();
    myMesh.DrawWireframe();
    myMesh.DrawInternalPoints();
    
    voroTester.DrawVoronoiEdges();
    //voroTester.DrawVoronoiVertices();
    voroTester.DrawVertices(voroTester.cellVerticesToDraw, 1, 1, 1);
    //voroTester.DrawAllVertices(voroTester.allCellVerticesToDraw);
    
    
    /* Rotate a bit more */
    alpha = alpha + 0.01;
    
    /* End */
    glFlush();
    glutSwapBuffers();
    
    /* Update again and again */
    glutPostRedisplay();
}

/*
 ** Function called when the window is created or resized
 */
void		ReshapeFunc(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    gluPerspective(20, width / (float) height, 5, 15);
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

/*
 ** Function called when a key is hit
 */
void		KeyboardFunc(unsigned char key, int x, int y)
{
    int foo;
    
    foo = x + y; /* Has no effect: just to avoid a warning */
    if ('q' == key || 'Q' == key || 27 == key)
        exit(0);
}

//TODO: MOVE TO MESH CLASS
std::vector<glm::vec3> MakeCubeListOfVerts(){
    std::vector<glm::vec3> listOfVerts;
    listOfVerts.push_back(glm::vec3(-1, 1, -1));
    listOfVerts.push_back(glm::vec3(1, 1, -1));
    listOfVerts.push_back(glm::vec3(1, 1, 1));
    listOfVerts.push_back(glm::vec3(-1, 1, 1));
    listOfVerts.push_back(glm::vec3(-1, -1, -1));
    listOfVerts.push_back(glm::vec3(1, -1, -1));
    listOfVerts.push_back(glm::vec3(1, -1, 1));
    listOfVerts.push_back(glm::vec3(-1, -1, 1));
    
    return listOfVerts;
    
}

//TODO: MOVE TO MESH CLASS
std::vector<int> MakeCubeListOfIndices(){
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
    
    return listOfIndices;
    
}

//TODO: MOVE TO MESH CLASS
std::vector<glm::vec3> MakeTetraListOfVerts(){
    std::vector<glm::vec3> listOfVerts;
    listOfVerts.push_back((glm::vec3(-0.5f, -0.5f, -0.5f))); //bottom point
    listOfVerts.push_back((glm::vec3(2 - 0.5f, -0.5f, -0.5f))); //bottom point
    float sqrtPt75 = glm::sqrt(0.75);
    listOfVerts.push_back(glm::vec3(1 - 0.5f, -0.5f, (sqrtPt75*2.0f) - 0.5f)); //bottom point
    listOfVerts.push_back(glm::vec3((.5f*2.0f) - 0.5f, (sqrtPt75*2.0f) - 0.5f, (2.0f*(sqrtPt75)/3) - 0.5f)); //top point
    
    return listOfVerts;
    
}

//TODO: MOVE TO MESH CLASS
std::vector<int> MakeTetraListOfIndices(){
    std::vector<int> listOfIndices;
 
    listOfIndices.push_back(0);
    listOfIndices.push_back(1);
    listOfIndices.push_back(2);
    
    listOfIndices.push_back(0);
    listOfIndices.push_back(2);
    listOfIndices.push_back(3);
    
    listOfIndices.push_back(2);
    listOfIndices.push_back(1);
    listOfIndices.push_back(3);
    
    listOfIndices.push_back(0);
    listOfIndices.push_back(3);
    listOfIndices.push_back(1);
    
    return listOfIndices;
}


int	main(int argc, char **argv)
{
    
    //CUBE CASE
    //std::vector<glm::vec3> listOfVerts = MakeCubeListOfVerts();
    //std::vector<int> listOfIndices = MakeCubeListOfIndices();
    //string shapeType = "cube";
    
    //TETRAHEDON CASE
    std::vector<glm::vec3> listOfVerts = MakeTetraListOfVerts();
    std::vector<int> listOfIndices = MakeTetraListOfIndices();
    string shapeType = "tetrahedron";
    
    //myCube = Cube(listOfVerts);
    //myCube = Cube();
    std::vector<float> pot;
    pot.push_back(1.0f);
    pot.push_back(0.0f);
    pot.push_back(-1.0f);
    glm::vec3 POI(pot[0], pot[1], pot[2]);
    //myCube.GenerateRandomInternalPoints(500, pot);
    
    
    // USE PASSED IN ARGUMENTS
    myMesh = Mesh(listOfVerts, listOfIndices, glm::vec3(0, 0, 0), shapeType);
    myMesh.GenerateRandomInternalPoints(500, pot); 
    
    glm::vec3 POI2 = glm::vec3(pot[0], pot[1], pot[2]);
    //Voronoi Decomp
    voroTester = VoronoiTest();
    //vector<glm::vec3> randomDebugPoints = myCube.DebugGenerateRandomPts(4);
    voroTester.ConvexGeoDecomp(listOfVerts, POI2, listOfIndices);
    //voroTester.CubeExample(POI2);
    

    //int newNum = sizeof(*indices); ///sizeof(indices[0]);
    /* Creation of the window */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning cube");
    
    /* OpenGL settings */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    /* Declaration of the callbacks */
    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutKeyboardFunc(&KeyboardFunc);
    
    /* Loop */
    glutMainLoop();
    
    /* Never reached */
    return 0;
}

/* ========================================================================= */
