//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Random.h"

/*
 *      PUBLIC methods
 */

std::unique_ptr<Random>& Random::getInstance()
{
        static std::unique_ptr<Random> random(new Random(rand(), 0.6, 0.15, 0, 1));
        return random;
}

double Random::random(bool clamp)
{
    if (clamp)
        return fmax(_clampMin, fmin(_clampMax, _normalDistribution(_rng)));
    return _normalDistribution(_rng);
}


double Random::randomAbsolute()
{
    return fmax(_clampMin, fmin(_clampMax, std::abs(_normalDistribution(_rng))));
}

double Random::randomNormalized()
{
    return (this->random(false) - _clampMin) / _clampMax - _clampMin;
}

uint32_t Random::getSeed() const
{
    return _seed;
}

void Random::reseed(uint32_t seed)
{
    _seed = seed;
    _rng.seed(seed);
}

std::pair<double, double> Random::getDistributionParameters() const
{
    return {_mean, _stddev};
}

void Random::redistribute(const double mean, const double stddev)
{
    _mean = mean;
    _stddev = stddev;
    _normalDistribution = std::normal_distribution<double>(mean, stddev);
}

void Random::reClamp(const double clampMin, const double clampMax)
{
    _clampMin = clampMin;
    _clampMax = clampMax;
}

std::pair<double, double> Random::getClamp() const
{
    return {_clampMin, _clampMax};
}


/*
 *      PRIVATE methods
 */

Random::Random(const uint32_t seed,
               const double mean, const double stddev,
               const double clampMin, const double clampMax)
{
        reseed(seed);
        redistribute(mean, stddev);
        reClamp(clampMin, clampMax);
}




