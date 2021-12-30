#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Utility/Stopwatch.h"

// TODO  to modify difficulty, modify standard deviation of the normal distribution of Random???
//  ==> If we normalize the result of random to the rang [0, 1], and we multiply default
//  platform distance by the random result, then the platform will be located to the
//  middle end of the distribution more often if the stddev is low. If the stddev is
//  higher, then there is more chance for the platform to be spawned at a further distance instead

// TODO  use  https://homepage.divms.uiowa.edu/~mbognar/applets/normal.html to
//  determine good stddev for random
//      Random(seed, .5, .15)       ??

void windowTest()
{

        // TODO set window VSync to true
        //  cap framerate at 60

        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen()) {
                sf::Event event{};
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }

                window.clear();
                window.draw(shape);
                window.display();
        }
}

int main()
{


        // TODO
        // TODO
        // windowTest();
        // TODO
        // TODO

        return 0;
}
