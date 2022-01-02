//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Random.h"

/*
 *      PUBLIC methods
 */

Random* Random::getInstance(const uint32_t seed, const double mean, const double stddev,
                            const double clampMin, const double clampMax)
{
        static auto* random = new Random(seed, mean, stddev, clampMin, clampMax);
        return random;
}

double Random::random() { return fmax(_clampMin, fmin(_clampMax, _normalDistribution(_rng))); }


double Random::randomAbsolute() { return fmax(_clampMin, fmin(_clampMax, std::abs(_normalDistribution(_rng)))); }



void Random::reseed(uint32_t seed) { _rng.seed(seed); }

void Random::redistribute(const double mean, const double stddev)
{
    _normalDistribution = std::normal_distribution<double>(mean, stddev);
}

void Random::reClamp(const double clampMin, const double clampMax) {
    _clampMin = clampMin;
    _clampMax = clampMax;
}



/*
 *      PRIVATE methods
 */

Random::Random(const uint32_t seed, const double mean, const double stddev,
               const double clampMin, const double clampMax) : _clampMin(clampMin), _clampMax(clampMax)
{
        reseed(seed);
        redistribute(mean, stddev);
}
