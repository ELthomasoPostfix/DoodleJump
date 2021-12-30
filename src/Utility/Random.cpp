//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Random.h"

/*
 *      PUBLIC methods
 */

Random* Random::getInstance(const uint32_t seed, const double mean, const double stddev)
{
        static auto* random = new Random(seed, mean, stddev);
        return random;
}

void Random::reseed(uint32_t seed) { _rng.seed(seed); }

/*
 *      PRIVATE methods
 */

Random::Random(const uint32_t seed, const double mean, const double stddev)
{
        reseed(seed);
        redistribute(mean, stddev);
}

void Random::redistribute(const double mean, const double stddev)
{
        _normalDistribution = std::normal_distribution<double>(mean, stddev);
}

double Random::random() { return fmax(0.0, fmin(1.0, _normalDistribution(_rng))); }
