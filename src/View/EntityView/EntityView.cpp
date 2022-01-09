//
// Created by Thomas Gueutal on 05/01/2022.
//

#include "EntityView.h"
#include "../../Game.h"



/*
 *      PUBLIC methods
 */

EntityView::EntityView(Game &observer)
    : _observer(observer), _hasTexture(false), _rgbFillColor({0, 0, 0}) {}

EntityView::~EntityView() {
    _viewArea.reset();
}

void EntityView::notify() {
    //_observer.update(*this);
}

void EntityView::move(const std::pair<double, double> &moveVector) {
    _viewArea->move(moveVector);
    notify();   // TODO  This is a weird implementation? Isn't the window cleared every frame???
}

void EntityView::setPosition(const std::pair<double, double> &destination) {
    _viewArea->setPosition(destination);
    notify();   // TODO  This is a weird implementation? Isn't the window cleared every frame???
}

const std::unique_ptr<CollisionObject> &EntityView::getViewArea() {
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
 *      PUBLIC methods
 */


void EntityView::setTextureID(const size_t textureID) {
    _textureID = textureID;
    _hasTexture = true;
}


