//
// Created by Thomas Gueutal on 11/01/2022.
//

#include "VerticalPlatform.h"

VerticalPlatform::VerticalPlatform(Rect &rect) : Platform(rect) {
    _up = Random::getInstance()->randomAbsolute() < 0.5;  // Choose a random start direction
    auto cameraBounds = World::getInstance()->getCameraBoundingBox();
    _bounds = {cameraBounds.at(3), cameraBounds.at(1)};
    recalculateMovementSpeed();
}

void VerticalPlatform::process(double delta) {
    // If bound reached, swap direction.
    if ((_up && getClipObject().getBoundingBox().at(3) >= _bounds.first) ||
        (!_up && getClipObject().getBoundingBox().at(1) <= _bounds.second))
        _up = !_up;

    move(0, delta * (_up ? _movementPerSecond : - _movementPerSecond));
}

void VerticalPlatform::setBounds(const std::pair<double, double> &bounds) {
    if (bounds.first < bounds.second) {
        _bounds.first = bounds.second;
        _bounds.second = bounds.first;
    } else
        _bounds = bounds;
}

void VerticalPlatform::recalculateMovementSpeed() {
    // (top - bottom) / 5s
    _movementPerSecond = 0.2 * (_bounds.first - _bounds.second);
}
