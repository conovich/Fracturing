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
    //glRotatef(alpha, 0, 1, 0);
    
    
    //myCube.DrawWireframe();
    //myCube.DrawInternalPoints();
    myMesh.DrawWireframe();
    myMesh.DrawInternalPoints();
    
    
    
    /* Rotate a bit more */
    //alpha = alpha + 0.1;
    
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


int	main(int argc, char **argv)
{
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
    pot.push_back(0.5f);
    pot.push_back(0.5f);
    pot.push_back(0.5f);
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
    
    
    myMesh = Mesh(listOfVerts, listOfIndices, glm::vec3(0, 0, 0));
    myMesh.GenerateRandomInternalPoints(500, pot); 
    
    //Voronoi Decomp
    //VoronoiTest voroTester = VoronoiTest();
    //vector<glm::vec3> randomDebugPoints = myCube.DebugGenerateRandomPts(10);
    //voroTester.ComputeVoronoiDecompCube(myCube, randomDebugPoints);
    
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
