//
// Created by Thomas Gueutal on 29/12/2021.
//

#include <random>

#ifndef DOODLEJUMP_RANDOM_H
#define DOODLEJUMP_RANDOM_H

typedef std::mt19937 RNG;

// TODO  inspiration from https://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-does-it-work

class Random {
    public:
        // Random value based on a normal distribution,
        // clamped to range [0, 1]
        double random();

        static Random* getInstance(uint32_t seed, double mean, double stddev);

        void reseed(uint32_t seed);

        void redistribute(double mean, double stddev);



    private:
        RNG _rng;
        std::normal_distribution<double> _normalDistribution;

        Random(uint32_t seed, double mean, double stddev);
        Random(Random const&) = default;                // don't implement
        Random& operator= (Random const&) = default;    // don't implement

};


#endif //DOODLEJUMP_RANDOM_H
