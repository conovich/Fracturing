//
//  Ray.cpp
//  VoronoiTest
//
//  Created by Renula Mitra on 4/17/15.
//  Copyright (c) 2015 Renula Mitra. All rights reserved.
//

#include <stdio.h>
#include "Ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 d) {
    orig = o;
    dir = d;
}