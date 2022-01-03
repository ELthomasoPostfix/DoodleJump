//
// Created by Thomas Gueutal on 29/12/2021.
//


#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H

#include <chrono>

// TODO inspiration from https://gist.github.com/mcleary/b0bf4fa88830ff7c882d
//! A singleton class that uses the <a href="https://en.cppreference.com/w/cpp/chrono/steady_clock">std::chrono::steady_clock.</a> to simulate time intervals.
/*!
 * This class allows the user to store a point in time using the update() method. A call to elapsedSeconds()
 * will then return the number of seconds that have passed since the previous update() call.
 * The constructor initialises the first reference time point, so technically no update() call
 * is ever required for the class to function.
 */
class Stopwatch {
    public:
        //! Retrieve the single instance of the ::Stopwatch singleton.
        static Stopwatch* getInstance();

        //! The number of elapsed seconds in relation to the last update() call.
        double elapsedSeconds();

        //! Effectively reset elapsedSeconds() to 0 seconds.
        void update();

        //! Retrieve the time according to the <a href="https://en.cppreference.com/w/cpp/chrono/steady_clock">std::chrono::steady_clock.</a>
        static std::chrono::steady_clock::time_point now();

    private:
        std::chrono::time_point<std::chrono::steady_clock> _prevUpdate;

        Stopwatch();
        Stopwatch(Stopwatch const&) = default;              // don't implement
        Stopwatch& operator= (Stopwatch const&) = default;  // don't implement

};


#endif //DOODLEJUMP_STOPWATCH_H
