//
// Created by Thomas Gueutal on 31/12/2021.
//

#ifndef DOODLEJUMP_UTILITY_H
#define DOODLEJUMP_UTILITY_H

#include <cmath>
#include <limits>


namespace Utility {

    //! Convert degrees to radians.
    double toRadians(unsigned int degrees);

    //! Reduce the degrees value to its equivalent within the range [0, 360[.
    int reduceDegrees(int degrees);

    //! Check whether the value is equal +inf or -inf.
    bool isInf(double value);
};


#endif //DOODLEJUMP_UTILITY_H
