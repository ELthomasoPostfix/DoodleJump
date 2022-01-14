//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_ABSTRACTENTITYFACTORY_H
#define DOODLEJUMP_ABSTRACTENTITYFACTORY_H

#include "../GameObject/Entity/Player/Player.h"
#include "../GameObject/Entity/Platform/StaticPlatform.h"
#include "../GameObject/Entity/Platform/TemporaryPlatform.h"
#include "../GameObject/Entity/Platform/HorizontalPlatform.h"
#include "../GameObject/Entity/Platform/VerticalPlatform.h"
#include "../GameObject/Entity/BGTile/BGTile.h"
#include "../GameObject/Entity/Bonus/Jetpack.h"
#include "../GameObject/Entity/Bonus/Spring.h"

//! Functions as the observer of the ::EntityView derived class objects.
class Game;
class TexturesInfo;

//! The interface with which the world constructs its entities.
/*!
 * The abstract entity factory provides the world with an interface to construct the specific
 * entity types defined in the logic library.
 * \note As the ::World class is a singleton, it is possible for limited logic for manipulating the
 * internals of a constructed entity through its interface by querying the world object.
 */
class AbstractEntityFactory {
    public:
        //! All concrete factories are required to implement a constructor that assigns the observer and acquires texture info.
        /*!
         * The observer is necessary to retrieve the views to be drawn onto the window.
         * The texture info is necessary to properly proportion entities according to their
         * texture file.
         */
        AbstractEntityFactory(Game &observer, const TexturesInfo& info);

        //! Create a ::Player object with the correct view attached.
        virtual std::shared_ptr<Player> createPlayer() = 0;

        //! Create a ::StaticPlatform object with the correct view attached.
        virtual std::shared_ptr<StaticPlatform> createStaticPlatform() = 0;

        //! Create a ::HorizontalPlatform object with the correct view attached.
        virtual std::shared_ptr<HorizontalPlatform> createHorizontalPlatform() = 0;

        //! Create a ::VerticalPlatform object with the correct view attached.
        virtual std::shared_ptr<VerticalPlatform> createVerticalPlatform() = 0;

        //! Create a ::TemporaryPlatform object with the correct view attached.
        virtual std::shared_ptr<TemporaryPlatform> createTemporaryPlatform() = 0;

        //! Create a ::Jetpack object with the correct view attached.
        virtual std::shared_ptr<Jetpack> createJetpack() = 0;

        //! Create a ::Spring object with the correct view attached.
        virtual std::shared_ptr<Spring> createSpring() = 0;

        //! Create a ::BGTile object with the correct view attached.
        virtual std::shared_ptr<BGTile> createBGTile() = 0;

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
        double platformWidthFactor;
};


#endif //DOODLEJUMP_ABSTRACTENTITYFACTORY_H
