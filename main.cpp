#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

void windowTest() {

    // TODO set window VSync to true
    //  cap framerate at 60

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
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
    //windowTest();
    // TODO
    // TODO

    return 0;
}
