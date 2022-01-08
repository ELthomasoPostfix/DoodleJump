//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_SFMLENTITYFACTORY_H
#define DOODLEJUMP_SFMLENTITYFACTORY_H

#include "../AbstractEntityFactory.h"
#include "../../EntityView/PlayerView/PlayerView.h"

class SFMLEntityFactory : public AbstractEntityFactory {

    //! Create a ::Player object with the correct view attached.
    std::shared_ptr<Player> createPlayer(double positionX, double positionY) override;

    // TODO revise comment
    //! Create a ::StaticPlatform object with the correct view attached.
    std::shared_ptr<Platform> createStaticPlatform(double positionX, double positionY) override;

    // TODO revise comment
    //! Create a ::HorizontalPlatform object with the correct view attached.
    std::shared_ptr<Platform> createHorizontalPlatform(double positionX, double positionY) override;

    // TODO revise comment
    //! Create a ::VerticalPlatform object with the correct view attached.
    std::shared_ptr<Platform> createVerticalPlatform(double positionX, double positionY) override;

    // TODO revise comment
    //! Create a ::TemporaryPlatform object with the correct view attached.
    std::shared_ptr<Platform> createTemporaryPlatform(double positionX, double positionY) override;

    //! Create a ::Jetpack object with the correct view attached.
    std::shared_ptr<Jetpack> createJetpack(double positionX, double positionY) override;

    //! Create a ::Spring object with the correct view attached.
    std::shared_ptr<Spring> createSpring(double positionX, double positionY) override;

    //! Create a ::BGTile object with the correct view attached.
    std::shared_ptr<BGTile> createBGTile(double positionX, double positionY) override;

};


#endif //DOODLEJUMP_SFMLENTITYFACTORY_H
