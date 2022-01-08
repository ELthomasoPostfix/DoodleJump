//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_WINDOWMANAGER_H
#define DOODLEJUMP_WINDOWMANAGER_H

#include <iostream>
#include "../ResourceManager/ResourceManager.h"
#include "../EntityView.h"


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

        //! Draw an ::EntityView onto the window. The view may describe a texture or not.
        virtual void draw(EntityView& view) = 0;

        virtual ~WindowManager();

        virtual void draw(const std::string &text, size_t fontID) = 0;

        virtual void setFrameRateLimit(unsigned int limit) {};

        void printDrawError(const std::string& what);

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
void WindowManager<Texture, Font, RenderWindow>::printDrawError(const std::string &what) {
    std::cout << "Error while drawing on DoodleJump window : " << what << std::endl;
}



#endif //DOODLEJUMP_WINDOWMANAGER_H
