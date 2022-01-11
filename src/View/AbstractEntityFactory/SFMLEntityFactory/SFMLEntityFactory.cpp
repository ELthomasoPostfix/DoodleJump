//
// Created by Thomas Gueutal on 07/01/2022.
//

#include "SFMLEntityFactory.h"

/*
 *      PUBLIC methods
 */


SFMLEntityFactory::SFMLEntityFactory(Game& observer, const TexturesInfo& info)
    : AbstractEntityFactory(observer, info) {}

std::shared_ptr<Player> SFMLEntityFactory::createPlayer() {
    const unsigned int viewHeight = 100;
    const unsigned int viewWidth  = TexturesInfo::determineWidth(viewHeight, info.playerTextureDims);
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<PlayerView> player =
            std::make_shared<PlayerView>(observer, collArea, viewArea);
    std::shared_ptr<TemplateView<Player>> playerr =
            std::make_shared<TemplateView<Player>>(observer, collArea, viewArea);
    player->setTextureID(PLAYER_TEXTURE_ID);
    return player;
}

std::shared_ptr<Platform> SFMLEntityFactory::createStaticPlatform() {
    const unsigned int viewHeight = 50;
    const unsigned int viewWidth  = 200;
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<StaticPlatform>> staticPlatform =
            std::make_shared<TemplateView<StaticPlatform>>(observer, collArea, viewArea);
    return staticPlatform;
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


