//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_ABSTRACTENTITYFACTORY_H
#define DOODLEJUMP_ABSTRACTENTITYFACTORY_H

#include "../../Game/GameObject/Entity/Player/Player.h"
#include "../../Game/GameObject/Entity/Platform/Platform.h" // TODO specific Platforms
#include "../../Game/GameObject/Entity/Platform/StaticPlatform.h" // TODO specific Platforms
#include "../../Game/GameObject/Entity/BGTile/BGTile.h"
#include "../../Game/GameObject/Entity/Bonus/Jetpack.h"
#include "../../Game/GameObject/Entity/Bonus/Spring.h"

//! Functions as the observer of the ::EntityView derived class objects.
class Game;
class TexturesInfo;

class AbstractEntityFactory {
    public:
        //! All concrete factories are required to implement a constructor that assigns the observer and acquires texture info.
        /*!
         * The observer is necessary to retrieve the views to be drawn onto the window.
         * The texture info is necessary to properly proportion entities according to their
         * texture.
         */
        AbstractEntityFactory(Game &observer, const TexturesInfo& info);

    // TODO  contain the logic of entity spawning within the EntityFactory?
    //  ==> e.g. The EntityFactory keeps "totalCreated" and "lastCreatedPosition" members.
    //  If it "tC" is < 1, then spawn a platform. If "tC" == 1, then spawn the player on that
    //  platform. If it is > 1, then do whatever. Boost spawns must always follow a platform
    //  spawn and may alter the difficulty (distance to) the next platforms (e.g. by
    //  increasing/taking min(flat value, normal distr chance)) for platform spawn location.
    //  ==> IF THIS IS DONE, ONLY A CREATEENTITY() METHOD IS NEEDED!!!

        //! Create a ::Player object with the correct view attached.
        virtual std::shared_ptr<Player> createPlayer() = 0;

        // TODO revise comment
        //! Create a ::StaticPlatform object with the correct view attached.
        virtual std::shared_ptr<Platform> createStaticPlatform() = 0;

        // TODO revise comment
        //! Create a ::HorizontalPlatform object with the correct view attached.
        virtual std::shared_ptr<Platform> createHorizontalPlatform(double positionX, double positionY) = 0;

        // TODO revise comment
        //! Create a ::VerticalPlatform object with the correct view attached.
        virtual std::shared_ptr<Platform> createVerticalPlatform(double positionX, double positionY) = 0;

        // TODO revise comment
        //! Create a ::TemporaryPlatform object with the correct view attached.
        virtual std::shared_ptr<Platform> createTemporaryPlatform(double positionX, double positionY) = 0;

        //! Create a ::Jetpack object with the correct view attached.
        virtual std::shared_ptr<Jetpack> createJetpack(double positionX, double positionY) = 0;

        //! Create a ::Spring object with the correct view attached.
        virtual std::shared_ptr<Spring> createSpring(double positionX, double positionY) = 0;

        //! Create a ::BGTile object with the correct view attached.
        virtual std::shared_ptr<BGTile> createBGTile(double positionX, double positionY) = 0;

    protected:
        //! Create a non-rotated rectangle that contains the point (0, 0) based on the specified width and height..
        /*!
         * \param width The x-coordinate of the two points not located at x = 0.
         * \param width The y-coordinate of the two points not located at y = 0.
         */
        Rect createRect(double width, double height);

    protected:
        Game& observer;
        const TexturesInfo& info;
};


#endif //DOODLEJUMP_ABSTRACTENTITYFACTORY_H
