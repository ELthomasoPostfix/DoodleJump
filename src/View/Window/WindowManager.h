//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_WINDOWMANAGER_H
#define DOODLEJUMP_WINDOWMANAGER_H

#include <iostream>
#include "../ResourceManager/ResourceManager.h"
#include "../EntityView/EntityView.h"


//! A common interface for all window managers.
/*!
 * To minimize the interface of the ::Game class, a ::WindowManager object
 * is defined instead. A class template is used to define the strictly
 * needed common functionality. A concrete window manager may then define its
 * specific and helper methods at its own discretion without cluttering the
 * common interface. To change the used graphics library, a new window manager
 * can be defined. A texture, font and window class type must be supplied.
 * Because the interface is abstract, it is not strictly necessary to supply a
 * texture, font and window class type of the same library, as long as the
 * implementation handles everything correctly.
 */
template<typename Texture, typename Font, typename RenderWindow>
struct WindowManager {
    public:
        //! Common constructor for all window managers.
        /*!
         * The construction of the texture manager and the font manager is handled
         * by the ::WindowManager constructor. However the construction of the window
         * is <b>not</b> handled here. This should be done explicitly in the derived
         * class, as to ensure proper construction of the window.
         */
        WindowManager();

        //! Resets all ::WindowManager members.
        virtual ~WindowManager();

        //! Shut down the window.
        /*!
         * \return Whether or not the shutdown succeeded.
         */
        virtual bool close() = 0;

        //! Clear the window of any drawn views.
        /*!
         * \param clearColor The color RGB of the screen after clearing.
         */
        virtual void clear(std::array<uint8_t, 3> clearColor) = 0;

        //! Display the current view buffer to the window.
        virtual void display() = 0;

        //! Draw an ::EntityView onto the window. The view may describe a texture or not.
        virtual void draw(EntityView& view) = 0;

        //! Draw a text string onto the window.
        /*!
         * \param text The text to display.
         * \param fontID The id of the font to apply to the text.
         * It references the related font stored in the font manager.
         */
        virtual void draw(const std::string &text, size_t fontID) = 0;

        //! Poll the window for an event.
        virtual bool pollEvent(dj::Event& event) const = 0;

        //! Set the framerate limit of the window.
        virtual void setFrameRateLimit(unsigned int limit) {};

        //! Get the dimensions of a registered texture by id.
        virtual std::pair<unsigned int, unsigned int> getTextureDimensions(size_t textureID) const = 0;

        // TODO  Push error handling to Controller???
        //  ==> throw;
        //! Print a generic error to report that the ::WindowManager encountered a problem drawing onto the window.
        void printDrawError(const std::string& what) const;

        //! Print a generic error to report that the ::WindowManager encountered a problem drawing onto the window.
        void printTextureDimError(const std::string& what) const;

        //! Print a generic error to report that the ::WindowManager encountered a problem closing the window.
        void printExitError(const std::string& what) const;

    public:
        std::unique_ptr<ResourceManager<Texture, size_t>> textureManager;
        std::unique_ptr<ResourceManager<Font, size_t>> fontManager;
        std::unique_ptr<RenderWindow> window;
};

template<typename Texture, typename Font, typename RenderWindow>
WindowManager<Texture, Font, RenderWindow>::WindowManager() {
    textureManager = std::make_unique<ResourceManager<Texture, size_t>>();
    fontManager = std::make_unique<ResourceManager<Font, size_t>>();
}

template<typename Texture, typename Font, typename RenderWindow>
WindowManager<Texture, Font, RenderWindow>::~WindowManager() {
    textureManager.reset();
    fontManager.reset();
    window.reset();
}

template<typename Texture, typename Font, typename RenderWindow>
void WindowManager<Texture, Font, RenderWindow>::printDrawError(const std::string &what) const {
    std::cout << "Error while drawing on DoodleJump window : " << what << std::endl;
}

template<typename Texture, typename Font, typename RenderWindow>
void WindowManager<Texture, Font, RenderWindow>::printExitError(const std::string &what) const {
    std::cout << "Error while closing DoodleJump window : " << what << std::endl;
}

template<typename Texture, typename Font, typename RenderWindow>
void WindowManager<Texture, Font, RenderWindow>::printTextureDimError(const std::string &what) const {
    std::cout << "Error concerning a Texture : " << what << std::endl;
}


#endif //DOODLEJUMP_WINDOWMANAGER_H
