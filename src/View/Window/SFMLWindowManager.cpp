//
// Created by Thomas Gueutal on 07/01/2022.
//

#include "SFMLWindowManager.h"


/*
 *      PUBLIC methods
 */

SFMLWindowManager::SFMLWindowManager(unsigned int width, unsigned int height) {
    window = std::make_unique<sf::RenderWindow>();
    window->setSize({width, height});
}

void SFMLWindowManager::draw(EntityView &view) {
    try {
        auto& viewArea = view.getViewArea();

        if (view.hasTexture()) {

            sf::Sprite sprite;
            sprite.setTexture(textureManager->get(view.getTextureID()));
            sprite.setOrigin(viewArea->getOrigin().first, viewArea->getOrigin().second);
            sprite.setPosition(viewArea->getPosition().first, viewArea->getPosition().second);

            window->draw(sprite);
        } else {
            const auto& fc = view.getRGBFillColor();
            sf::Color fillColor(fc.at(0), fc.at(1), fc.at(2));

            sf::RectangleShape rect;    // TODO set corners
            rect.setOrigin(viewArea->getOrigin().first, viewArea->getOrigin().second);
            rect.setPosition(viewArea->getPosition().first, viewArea->getPosition().second);
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

void SFMLWindowManager::setFrameRateLimit(const unsigned int limit) {
    window->setFramerateLimit(limit);
}
