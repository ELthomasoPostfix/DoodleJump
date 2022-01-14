//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_SFMLWINDOWMANAGER_H
#define DOODLEJUMP_SFMLWINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include "../View/Window/WindowManager.h"

//! An SFML implementation of the ::WindowManager abstract interface.
struct SFMLWindowManager : public WindowManager<sf::Texture, sf::Font, sf::RenderWindow> {
    public:
        SFMLWindowManager(unsigned int width, unsigned int height);

        ~SFMLWindowManager() override = default;

        bool close() override;

        void clear(std::array<uint8_t, 3> clearColor) override;

        void display() override;


        // TODO set scale of sprite?
        void draw(EntityView& view) final;

        void draw(const std::string &text, size_t fontID) final;

        bool pollEvent(dj::Event& event) const override;

        void setFrameRateLimit(unsigned int limit) final;

        std::pair<unsigned int, unsigned int> getTextureDimensions(size_t textureID) const override;

private:
        //! Transform the independent y-coordinate to an SFML position  y-coordinate.
        /*!
         * The independent coordinates choose the bottom of the window to be y = 0.
         * However, SFML chooses this to be at the top of the screen. Thus,
         * we must add offset to the position of drawn entities so that
         * they appear in the correct position on the SFML windows.
         */
        double determineSFMLYOffset(CollisionObject& viewArea) const;

        //! Determine the position to move the sfml view object to. This is in sfml window coordinates.
        std::pair<double, double> determineSFMLPosition(CollisionObject& viewArea);
};


#endif //DOODLEJUMP_SFMLWINDOWMANAGER_H
