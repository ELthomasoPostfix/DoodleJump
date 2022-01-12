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
    std::shared_ptr<TemplateView<Player>> player =
            std::make_shared<TemplateView<Player>>(observer, collArea, viewArea);
    player->setTextureID(PLAYER_TEXTURE_ID);
    player->setBaseScore(std::numeric_limits<int>::infinity());
    return player;
}

std::shared_ptr<StaticPlatform> SFMLEntityFactory::createStaticPlatform() {
    const unsigned int viewHeight = 20;
    const unsigned int viewWidth  = viewHeight * platformWidthFactor;
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<StaticPlatform>> staticPlatform =
            std::make_shared<TemplateView<StaticPlatform>>(observer, collArea, viewArea);
    staticPlatform->setFillColor(0, 255, 0);
    staticPlatform->setBaseScore(-100);
    return staticPlatform;
}

std::shared_ptr<HorizontalPlatform> SFMLEntityFactory::createHorizontalPlatform() {
    const unsigned int viewHeight = 20;
    const unsigned int viewWidth  = viewHeight * platformWidthFactor;
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<HorizontalPlatform>> horizPlatform =
            std::make_shared<TemplateView<HorizontalPlatform>>(observer, collArea, viewArea);
    horizPlatform->setFillColor(0, 0, 255);
    horizPlatform->setBaseScore(-200);
    return horizPlatform;
}

std::shared_ptr<VerticalPlatform> SFMLEntityFactory::createVerticalPlatform() {
    const unsigned int viewHeight = 20;
    const unsigned int viewWidth  = viewHeight * platformWidthFactor;
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<VerticalPlatform>> vertPlatform =
            std::make_shared<TemplateView<VerticalPlatform>>(observer, collArea, viewArea);
    vertPlatform->setFillColor(255, 255, 0);
    vertPlatform->setBaseScore(-500);
    return vertPlatform;
}

std::shared_ptr<TemporaryPlatform> SFMLEntityFactory::createTemporaryPlatform() {
    const unsigned int viewHeight = 20;
    const unsigned int viewWidth  = viewHeight * platformWidthFactor;
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<TemporaryPlatform>> tempPlatform =
            std::make_shared<TemplateView<TemporaryPlatform>>(observer, collArea, viewArea);
    tempPlatform->setFillColor(255, 255, 255);
    tempPlatform->setBaseScore(std::numeric_limits<int>::infinity());
    return tempPlatform;
}

std::shared_ptr<Jetpack> SFMLEntityFactory::createJetpack() {
    const unsigned int viewHeight = 40;
    const unsigned int viewWidth  = TexturesInfo::determineWidth(viewHeight, info.jetpackTextureDims);
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<Jetpack>> jetpack =
            std::make_shared<TemplateView<Jetpack>>(observer, collArea, viewArea);
    jetpack->setTextureID(JETPACK_TEXTURE_ID);
    jetpack->setBaseScore(jetpack->hasTexture() ? 200 : 400);
    return jetpack;
}

std::shared_ptr<Spring> SFMLEntityFactory::createSpring() {
    const unsigned int viewHeight = 20;
    const unsigned int viewWidth  = TexturesInfo::determineWidth(viewHeight, info.springTextureDims);
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<Spring>> spring =
            std::make_shared<TemplateView<Spring>>(observer, collArea, viewArea);
    spring->setTextureID(SPRING_TEXTURE_ID);
    spring->setBaseScore(spring->hasTexture() ? 100 : 200);
    return spring;
}

std::shared_ptr<BGTile> SFMLEntityFactory::createBGTile() {
    const unsigned int viewHeight = info.bgTileTextureDims.second;  // TODO  get BGTile texture
    const unsigned int viewWidth  = TexturesInfo::determineWidth(viewHeight, info.springTextureDims);
    Rect viewArea{createRect(viewWidth, viewHeight)};
    Rect collArea = viewArea;
    std::shared_ptr<TemplateView<BGTile>> bgTile =
            std::make_shared<TemplateView<BGTile>>(observer, collArea, viewArea);
    bgTile->setTextureID(SPRING_TEXTURE_ID);
    bgTile->setBaseScore(std::numeric_limits<int>::infinity());
    return bgTile;
}


