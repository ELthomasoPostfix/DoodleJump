//
// Created by Thomas Gueutal on 29/12/2021.
//

#include <chrono>

#ifndef DOODLEJUMP_STOPWATCH_H
#define DOODLEJUMP_STOPWATCH_H

// TODO inspiration from https://gist.github.com/mcleary/b0bf4fa88830ff7c882d
class Stopwatch {
    public:
        static Stopwatch* getInstance();

        double elapsedSeconds();

        void update();

        static std::chrono::steady_clock::time_point now();

    private:
        std::chrono::time_point<std::chrono::steady_clock> _prevUpdate;

        Stopwatch();
        Stopwatch(Stopwatch const&) = default;              // don't implement
        Stopwatch& operator= (Stopwatch const&) = default;  // don't implement

};


#endif //DOODLEJUMP_STOPWATCH_H
