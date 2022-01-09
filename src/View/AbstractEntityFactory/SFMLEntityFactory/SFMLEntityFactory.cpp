//
// Created by Thomas Gueutal on 07/01/2022.
//

#include "SFMLEntityFactory.h"

/*
 *      PUBLIC methods
 */


SFMLEntityFactory::SFMLEntityFactory(Game& observer) : AbstractEntityFactory(observer) {}

std::shared_ptr<Player> SFMLEntityFactory::createPlayer(double positionX, double positionY) {
    std::shared_ptr<Player> player = std::make_shared<PlayerView>(observer, 1, 1);
    return player;
}

std::shared_ptr<Platform> SFMLEntityFactory::createStaticPlatform(double positionX, double positionY) {
    return std::shared_ptr<Platform>();
}

std::shared_ptr<Platform> SFMLEntityFactory::createHorizontalPlatform(double positionX, double positionY) {
    return std::shared_ptr<Platform>();
}

std::shared_ptr<Platform> SFMLEntityFactory::createVerticalPlatform(double positionX, double positionY) {
    return std::shared_ptr<Platform>();
}

std::shared_ptr<Platform> SFMLEntityFactory::createTemporaryPlatform(double positionX, double positionY) {
    return std::shared_ptr<Platform>();
}

std::shared_ptr<Jetpack> SFMLEntityFactory::createJetpack(double positionX, double positionY) {
    return std::shared_ptr<Jetpack>();
}

std::shared_ptr<Spring> SFMLEntityFactory::createSpring(double positionX, double positionY) {
    return std::shared_ptr<Spring>();
}

std::shared_ptr<BGTile> SFMLEntityFactory::createBGTile(double positionX, double positionY) {
    return std::shared_ptr<BGTile>();
}


