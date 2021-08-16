#ifndef HEADERS_h
#define HEADERS_H
#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
#include <glm/glm.hpp>

#include "GameConfigs.hpp"
#include "BlockTypes.hpp"

#define debug(a, args...) printf("%s(%s:%d): " a "\n",  __func__,__FILE__, __LINE__, ##args)

// template <typename T>
// inline void debug(T arg, T args...) {
//     std::cout << ##args << "\n";
// }

template <typename T>
bool isSameSign(T x, T y)
{
    return (x >= 0) ^ (y < 0);
}

#endif