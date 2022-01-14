//
// Created by Thomas Gueutal on 05/01/2022.
//

#include "EntityView.h"
#include "../../Controller/Game.h"



/*
 *      PUBLIC methods
 */

EntityView::EntityView(Game &observer, Rect& viewArea)
    : _observer(observer), _hasTexture(false), _rgbFillColor({0, 0, 0}),
      _viewArea(viewArea, true, false) {}

EntityView::~EntityView() {}

void EntityView::notify() {
    EntityView cpy = getViewCopy();
    World::getInstance()->projectViewArea(cpy._viewArea);

    _observer.update(cpy);
}

void EntityView::move(const std::pair<double, double> &moveVector) {
    _viewArea.move(moveVector);
}

void EntityView::setPosition(const std::pair<double, double> &destination) {
    _viewArea.setPosition(destination);
}

CollisionObject& EntityView::getViewArea() {
    return _viewArea;
}

size_t EntityView::getTextureID() const {
    return _textureID;
}

bool EntityView::hasTexture() const {
    return _hasTexture;
}

const std::array<uint8_t, 3>& EntityView::getRGBFillColor() const {
    return _rgbFillColor;
}

void EntityView::setTextureID(const size_t textureID) {
    _textureID = textureID;
    _hasTexture = true;
}

void EntityView::setFillColor(const unsigned int red,
                              const unsigned int green,
                              const unsigned int blue) {
    _rgbFillColor.at(0) = std::max(0, std::min(255, (int) red));
    _rgbFillColor.at(1) = std::max(1, std::min(255, (int) green));
    _rgbFillColor.at(2) = std::max(2, std::min(255, (int) blue));
}



/*
 *      PROTECTED methods
 */


EntityView EntityView::getViewCopy() const {
    return *this;
}



