//
// Created by Thomas Gueutal on 29/12/2021.
//

#include <random>

#ifndef DOODLEJUMP_RANDOM_H
#define DOODLEJUMP_RANDOM_H

typedef std::mt19937 RNG;

// TODO  inspiration from https://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-does-it-work

//! A singleton class that generates pseudo random numbers based on a specified normal distribution.
/*!
 * This class is instantiated through the assignment of a seed for the purpose
 * of seeding a pseudo random number generator and a mean and standard deviation
 * for defining a normal distribution based on which to generate the random numbers.
 * \note The random numbers generated are clamped to the continuous range [0, 1].
 */
class Random {
    public:
        //! Random value based on a normal distribution, clamped to the continuous range [_clampMin, _clampMax]
        double random();

        //! Absolute random value based on a normal distribution, clamped to the continuous range [_clampMin, _clampMax].
        /*!
         * \note Choosing to take the absolute value before clamping increases the chances of all every positive
         * result by the chance of its negative counterpart occurring.
         */
        double randomAbsolute();

        //! Retrieve the single instance of the ::Random singleton.
        static Random* getInstance(uint32_t seed, double mean, double stddev,
                                   double clampMin = 0.0, double clampMax = 1.0);

        //! Change the seed of the underlying pseudo random number generator.
        void reseed(uint32_t seed);

        //! Adjust the normal distribution used to generate the random numbers when using random().
        void redistribute(double mean, double stddev);

        //! Adjust the clamp values used to restrict the generated random number when using random().
        void reClamp(double clampMin, double clampMax);



    private:
        RNG _rng;
        std::normal_distribution<double> _normalDistribution;

        double _clampMin;
        double _clampMax;

        Random(uint32_t seed, double mean, double stddev, double clampMin, double clampMax);
        Random(Random const&) = default;                // don't implement
        Random& operator= (Random const&) = default;    // don't implement

};


#endif //DOODLEJUMP_RANDOM_H