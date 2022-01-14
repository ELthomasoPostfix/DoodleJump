//
// Created by Thomas Gueutal on 11/01/2022.
//

#include "HorizontalPlatform.h"

HorizontalPlatform::HorizontalPlatform(Rect &rect) : Platform(rect) {
    _left = Random::getInstance()->randomAbsolute() < 0.5;  // Choose a random start direction
    auto cameraBounds = World::getInstance()->getCameraBoundingBox();
    _bounds = {cameraBounds.at(0), cameraBounds.at(2)};
    recalculateMovementSpeed();
}

void HorizontalPlatform::process(double delta) {
    // If bound reached, swap direction.
    if ((_left && getClipObject().getBoundingBox().at(0) <= _bounds.first) ||
        (!_left && getClipObject().getBoundingBox().at(2) >= _bounds.second))
        _left = !_left;

    move(delta * (_left ? - _movementPerSecond : _movementPerSecond), 0);
}

void HorizontalPlatform::setBounds(const std::pair<double, double> &bounds) {
    if (bounds.second < bounds.first) {
        _bounds.first = bounds.second;
        _bounds.second = bounds.first;
    } else
        _bounds = bounds;
}

void HorizontalPlatform::recalculateMovementSpeed() {
    // (right - left) / 5s
    _movementPerSecond = 0.2 * (_bounds.second - _bounds.first);
}
