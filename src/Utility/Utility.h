//
// Created by Thomas Gueutal on 31/12/2021.
//

#ifndef DOODLEJUMP_UTILITY_H
#define DOODLEJUMP_UTILITY_H

#include <cmath>
#include <limits>


namespace Utility {

    //! Convert \param degrees to radians.
    double toRadians(unsigned int degrees);

    //! Reduce the \param degrees value to its equivalent within the discrete range [0, 360[.
    int reduceDegrees(int degrees);

    //! Check whether \param value is equal to +inf or -inf.
    bool isInf(double value);
};


#endif //DOODLEJUMP_UTILITY_H
