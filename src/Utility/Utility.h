//
// Created by Thomas Gueutal on 31/12/2021.
//

#ifndef DOODLEJUMP_UTILITY_H
#define DOODLEJUMP_UTILITY_H

#include <cmath>
#include <limits>
#include <utility>


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
    bool approximate(double value1, double value2);

    //! Compute the dot product of two 2D vectors.
    double dot2(const std::pair<double, double>& vec1, const std::pair<double, double>& vec2);
};


#endif //DOODLEJUMP_UTILITY_H
