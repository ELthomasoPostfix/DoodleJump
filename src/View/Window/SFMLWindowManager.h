//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_SFMLWINDOWMANAGER_H
#define DOODLEJUMP_SFMLWINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include "WindowManager.h"

//! An SFML implementation of the ::WindowManager abstract interface.
struct SFMLWindowManager : public WindowManager<sf::Texture, sf::Font, sf::RenderWindow> {
    public:
        SFMLWindowManager(unsigned int width, unsigned int height);

        ~SFMLWindowManager() override = default;

        // TODO set scale of sprite?
        void draw(EntityView& view) final;

        void draw(const std::string &text, size_t fontID) final;

        void setFrameRateLimit(unsigned int limit) final;

};


#endif //DOODLEJUMP_SFMLWINDOWMANAGER_H
