//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Stopwatch.h"

/*
 *      PUBLIC methods
 */

std::unique_ptr<Stopwatch>& Stopwatch::getInstance()
{
    static std::unique_ptr<Stopwatch> stopwatch(new Stopwatch);
    return stopwatch;
}

Stopwatch::Stopwatch() : _prevUpdate(Stopwatch::now()) {}

double Stopwatch::elapsedSeconds()
{
        return std::chrono::duration_cast<std::chrono::nanoseconds>(Stopwatch::now() - _prevUpdate).count() /
               1000000000.0;
}

void Stopwatch::update() { _prevUpdate = Stopwatch::now(); }

std::chrono::steady_clock::time_point Stopwatch::now() { return std::chrono::steady_clock::now(); }

/*
 *      PRIVATE methods
 */
