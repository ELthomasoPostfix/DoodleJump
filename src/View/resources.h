//
// Created by Thomas Gueutal on 08/01/2022.
//

#ifndef DOODLEJUMP_RESOURCES_H
#define DOODLEJUMP_RESOURCES_H

#include <utility>

#define PLAYER_TEXTURE_PATH  "../Resources/Images/doodle-artisanal.png"
#define PLAYER_TEXTURE_ID    0
#define SPRING_TEXTURE_PATH  "../Resources/Images/pruz1.png"
#define SPRING_TEXTURE_ID    1
#define JETPACK_TEXTURE_PATH "../Resources/Images/raketa_on_panel.png"
#define JETPACK_TEXTURE_ID   2
#define ARIAL_FONT_PATH      "../Resources/Fonts/arial.ttf"
#define ARIAL_FONT_ID        0

//! A struct used for generating entities that apply a texture.
/*!
 * When displaying an entity using a texture, the visual and collision
 * rectangles should have the same proportions. This requires knowledge
 * of the dimensions of the stored textures. When generating the collision
 * and view shapes of an entity, texture dimension information is provided
 * to the ::AbstractFactory created in ::Game by attaching an objects of
 * this type to the entity factory.
 * \note The units are in pixels.
 */
struct TexturesInfo {
        //! Determine a width for a shape based on a texture's dimensions if the height of the shape is known.
        static unsigned int determineWidth(const unsigned int chosenY, const std::pair<unsigned int, unsigned int>& textureDims) {
            return chosenY / textureDims.second * textureDims.first;
        }

        std::pair<unsigned int, unsigned int> playerTextureDims;
        std::pair<unsigned int, unsigned int> jetpackTextureDims;
        std::pair<unsigned int, unsigned int> springTextureDims;
};


#endif //DOODLEJUMP_RESOURCES_H
