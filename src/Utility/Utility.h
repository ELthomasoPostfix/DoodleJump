//
// Created by Thomas Gueutal on 31/12/2021.
//

#ifndef DOODLEJUMP_UTILITY_H
#define DOODLEJUMP_UTILITY_H

#include <cmath>
#include <exception>
#include <limits>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
#include <memory>
#include <iostream> // TODO good idea?



namespace Utility {

    //! Convert \param degrees to radians.
    double toRadians(unsigned int degrees);

    //! Reduce the \param degrees value to its equivalent within the discrete range [0, 360[.
    int reduceDegrees(int degrees);

    //! Check whether \param value is equal to +inf or -inf.
    bool isInf(double value);

    //! Determine the slope of the line defined by the given line segment.
    double determineSlope(double x1, double y1, double x2, double y2);

    //! Return a static margin.
    double epsilon();

    //! Check whether the two values lie withing Utility::epsilon() of each other.
    bool approximates(double value1, double value2);

    //! Compute the dot product of two 2D vectors.
    double dot2(const std::pair<double, double>& vec1, const std::pair<double, double>& vec2);

    //! Compute the magnitude of the 2D vector.
    double magnitude(const std::pair<double, double>& vec);

    //! Find the index of the vector with the largest magnitude. If the list is empty, returns -1.
    size_t getLongestVectorIndex(const std::vector<std::pair<double, double>>& vectors);

    //! Find the index of the vector with the lowest magnitude. If the list is empty, returns -1.
    size_t getShortestVectorIndex(const std::vector<std::pair<double, double>>& vectors);

    //! Clamp the value.
    double clamp(double value, double clampMin, double clampMax);
};


#endif //DOODLEJUMP_UTILITY_H
