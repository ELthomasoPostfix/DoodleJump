//
// Created by Thomas Gueutal on 05/01/2022.
//

#include "EntityView.h"


/*
 *      PUBLIC methods
 */

void EntityView::move(const std::pair<double, double> &moveVector) {
    _viewArea->move(moveVector);
}

void EntityView::setPosition(const std::pair<double, double> &destination) {
    _viewArea->setPosition(destination);
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
