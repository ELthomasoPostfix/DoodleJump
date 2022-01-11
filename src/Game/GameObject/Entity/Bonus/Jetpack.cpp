//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Jetpack.h"

/*
 *      PUBLIC methods
 */

Jetpack::Jetpack(Rect& rect, double totalBoost) : Bonus(rect) {
    _totalBoost = totalBoost;
    _currentBoost = 0;
}

void Jetpack::process(double delta) {
    if (_active) {
        auto pos = getPosition();
        setPosition(CollisionObject::determineAbsoluteCenterOfMass(
                _observable.lock()->getClipObject().getCollisionShape()));
        double diffY = getPosition().second - pos.second;
        _currentBoost += diffY;
        if (_currentBoost >= _totalBoost) {
            _active = false;      // TODO  signal that the jetpack is to die
        }
    // After boost is spent, jetpack falls off screen to despawn
    } else if (_currentBoost >= _totalBoost) {
        move(-delta/4.0, -delta);
    }
}

bool Jetpack::update(bool callerIsSupported) {
    auto observable = _observable.lock();

    // The observable must have landed so that the spring would be stepped on.
    if (observable->getCollisionObject().checkCollision(this->getCollisionObject())) {
        observable->addDownwardPullScale(0);
        return true;
    }
    // TODO  somehow signal that spring should now die

    return false;}
