//
// Created by Thomas Gueutal on 07/01/2022.
//

#include "SFMLWindowManager.h"


/*
 *      PUBLIC methods
 */

SFMLWindowManager::SFMLWindowManager(unsigned int width, unsigned int height) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "DoodleJump");
}

bool SFMLWindowManager::close() {
    try {
        window->close();
        return true;
    } catch (std::exception& e) {
        printExitError(e.what());
        return false;
    }
}

void SFMLWindowManager::clear(std::array<uint8_t, 3> clearColor) {
    window->clear(sf::Color{clearColor.at(0), clearColor.at(1), clearColor.at(2)});
}

void SFMLWindowManager::display() {
    window->display();
}

void SFMLWindowManager::draw(EntityView &view) {
    // TODO delete
    // TODO delete
    // TODO delete
    sf::RectangleShape r;
    r.setSize({10, static_cast<float>(window->getSize().y)});
    r.setOrigin(5, 0);
    r.setPosition(window->getSize().x/2, 0);
    r.setFillColor(sf::Color(0, 0, 0));
    window->draw(r);

    sf::RectangleShape rh;
    rh.setSize({static_cast<float>(window->getSize().x), 10});
    rh.setOrigin(0, 5);
    rh.setPosition(0, window->getSize().y/2);
    rh.setFillColor(sf::Color(0, 0, 0));
    window->draw(rh);

    sf::RectangleShape va;
    va.setSize({static_cast<float>(view.getViewArea().getBoundingWidth()), static_cast<float>(view.getViewArea().getBoundingHeight())});
    va.setOrigin(view.getViewArea().getBoundingWidth()/2.0, 0);
    va.setPosition(window->getSize().x/2, window->getSize().y/2 - 100);
    va.setFillColor(sf::Color(0, 255, 0));
    //if (view.hasTexture())
    //    window->draw(va);

    // TODO delete
    // TODO delete
    // TODO delete

    try {
        auto& viewArea = view.getViewArea();

        if (view.hasTexture()) {
            sf::Sprite sprite;
            sprite.setTexture(textureManager->get(view.getTextureID()));
            // The view and texture should have the same height-width ratios.
            const double scale = viewArea.getBoundingHeight() / sprite.getTexture()->getSize().y;
            sprite.setScale(scale, scale);
            auto sfmlPos = determineSFMLPosition(viewArea);
            sprite.setPosition(sfmlPos.first, sfmlPos.second);

            window->draw(sprite);
        } else {
            const auto& fc = view.getRGBFillColor();
            sf::Color fillColor(fc.at(0), fc.at(1), fc.at(2));

            // TODO  SFML uses top left as origin, compensate because we use bottom left???

            sf::RectangleShape rect({static_cast<float>(view.getViewArea().getBoundingWidth()),
                                     static_cast<float>(view.getViewArea().getBoundingHeight())});    // TODO set corners
            auto sfmlPos = determineSFMLPosition(viewArea);
            rect.setPosition(sfmlPos.first, sfmlPos.second);
            rect.setFillColor(fillColor);

            window->draw(rect);
        }
    } catch (std::runtime_error& re) {
        printDrawError(re.what());
    }

}

void SFMLWindowManager::draw(const std::string &text, const size_t fontID) {
    try {
        sf::Text sfmlText;
        sfmlText.setFont(fontManager->get(fontID));
        sfmlText.setString(text);
        sfmlText.setCharacterSize(24);
        sfmlText.setOrigin(sfmlText.getLocalBounds().width/2, 0);
        sfmlText.setPosition(250, 100);
        sfmlText.setFillColor(sf::Color::Black);

        window->draw(sfmlText);
    } catch (std::runtime_error& re) {
        printDrawError(re.what());
    }
}

bool SFMLWindowManager::pollEvent(dj::Event& event) const {
    sf::Event sfEvent{};
    if (window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed)
            event = dj::Event::EXIT;
        else if (sfEvent.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                event = dj::Event::LEFT;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                event = dj::Event::RIGHT;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                event = dj::Event::SPACE_BAR;
        } else
            event = dj::Event::NONE;
    } else
        event = dj::Event::NONE;

    return event != dj::Event::NONE;
}

void SFMLWindowManager::setFrameRateLimit(const unsigned int limit) {
    window->setFramerateLimit(limit);
}

std::pair<unsigned int, unsigned int> SFMLWindowManager::getTextureDimensions(size_t textureID) const {
    try {
        auto size = textureManager->get(textureID).getSize();
        return {size.x, size.y};
    } catch (std::runtime_error& e) {
        printTextureDimError(e.what());
        return {0, 0};
    }
}

/*
 *      PRIVATE methods
 */

double SFMLWindowManager::determineSFMLYOffset(CollisionObject& viewArea) const {
    // SFML chooses y = 0 at the top of the screen
    const double centerY = window->getSize().y / 2.0;
    const double topDistance = centerY - viewArea.getBoundingBox().at(3);
    const double bottomDistance = centerY - viewArea.getBoundingBox().at(1);
    return topDistance + bottomDistance;
}

std::pair<double, double> SFMLWindowManager::determineSFMLPosition(CollisionObject &viewArea) {
    return {viewArea.getPosition().first  - viewArea.getOrigin().first,
            viewArea.getPosition().second + determineSFMLYOffset(viewArea) - viewArea.getOrigin().second};

}



