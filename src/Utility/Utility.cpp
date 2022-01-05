//
// Created by Thomas Gueutal on 31/12/2021.
//

#include "Utility.h"


namespace Utility {

    double toRadians(unsigned int degrees) {
        return static_cast<double>(degrees) * M_PI / 180.0;
    }

    int reduceDegrees(int degrees) {
        degrees %= 360;
        return degrees < 0 ? 360 + degrees : degrees;
    }

    bool isInf(const double value) {
        return std::abs(value) == std::numeric_limits<double>::infinity();
    }

    double determineSlope(double x1, double y1, double x2, double y2) {
        try {
            const double yDiff = y2 - y1;
            const double xDiff = x2 - x1;

            if (xDiff == 0)
                return yDiff < 0 ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();

            return yDiff / xDiff;

        } catch (std::exception& e) {
            throw;
        }
    }

    double epsilon() {
        static const double eps = 0.001;
        return eps;
    }

    bool approximate(const double value1, const double value2) {
        return std::abs(value2 - value1) < epsilon();
    }

    double dot2(const std::pair<double, double>& vec1, const std::pair<double, double>& vec2) {
        return vec1.first * vec2.first + vec1.second * vec2.second;
    }

    double magnitude(const std::pair<double, double>& vec) {
        return std::sqrt(std::pow(vec.first, 2) + std::pow(vec.second, 2));
    }

    unsigned int getLongestVectorIndex(const std::vector<std::pair<double, double>>& vectors) {
        unsigned int index = -1;
        double maxMagnitude = std::numeric_limits<double>::infinity();
        for (unsigned int i = 0; i < vectors.size(); ++i) {
            const auto& vector = vectors.at(i);
            double magnitude = Utility::magnitude(vector);
            if (maxMagnitude < magnitude) {
                maxMagnitude = magnitude;
                index = i;
            }
        }
        return index;
    }

}