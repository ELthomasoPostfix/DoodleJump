//
// Created by Thomas Gueutal on 05/01/2022.
//

#include "EntityView.h"
#include "../../Game.h"



/*
 *      PUBLIC methods
 */

EntityView::EntityView(Game &observer, Rect& viewArea)
    : _observer(observer), _hasTexture(false), _rgbFillColor({0, 0, 0}),
      _viewArea(viewArea, true) {}

EntityView::~EntityView() {}

void EntityView::notify() {
    EntityView cpy = getViewCopy();
    // TODO  update the game observer with a scaled and inverted version of this entity view
    //  ==> need Camera for this?
    // TODO Make sure that _observer.update(*this) moves the this values?
    //  ==> then we can just pass an object and not have to call new for the copy
    //_observer.update(*this);
}

void EntityView::move(const std::pair<double, double> &moveVector) {
    _viewArea.move(moveVector);
    notify();   // TODO  This is a weird implementation? Isn't the window cleared every frame???
}

void EntityView::setPosition(const std::pair<double, double> &destination) {
    _viewArea.setPosition(destination);
    notify();   // TODO  This is a weird implementation? Isn't the window cleared every frame???
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


/*
 *      PROTECTED methods
 */


void EntityView::setTextureID(const size_t textureID) {
    _textureID = textureID;
    _hasTexture = true;
}

EntityView EntityView::getViewCopy() const {
    return *this;
}

void EntityView::setFillColor(const unsigned int red,
                              const unsigned int green,
                              const unsigned int blue) {
    _rgbFillColor.at(0) = std::max(0, std::min(255, (int) red));
    _rgbFillColor.at(0) = std::max(0, std::min(255, (int) green));
    _rgbFillColor.at(0) = std::max(0, std::min(255, (int) blue));
}


