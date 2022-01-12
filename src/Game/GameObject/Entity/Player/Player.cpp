//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Player.h"
#include "../Bonus/Bonus.h"

/*
 *      PUBLIC methods
 */

Player::Player(Rect &rect) : Entity(rect, true, false) {
    // rf = r0 + vt + (1/2)at²
    // vf = v0 + at
    // Assume rf = (4/10) * windowHeight, vf = 0, t = 1s
    // { a = -2rf       { a  = -2rf
    // { v0 = -a        { v0 = 2rf
    _jumpHeight = 0.4 * static_cast<double>(World::getInstance()->getCameraDimensions().second);
    _terminalVelocity = 2 * _jumpHeight;
    _velocity = {0, 0};      // initially stand still
    resetDownwardPull();
    _xMovementSpeed = 0.5 * static_cast<double>(World::getInstance()->getCameraDimensions().first);
}

Player::~Player() {}

void Player::process(double delta) {

    double additionalXVelocity = 0;
    if (pollEvent(dj::Event::LEFT))
        additionalXVelocity -= _xMovementSpeed;
    else if (pollEvent(dj::Event::RIGHT))
        additionalXVelocity += _xMovementSpeed;
    _velocity.first = additionalXVelocity;

    // Applies the movement vector of the player based on delta time.
    // Returns whether the player landed onto the top of a solid object.
    bool isSupported = handleMovement(delta);

    // TODO  if player jumps off platform, then notify the Score and send along the platform jumped on

    // Let the bonuses apply their effects themselves.
    auto it = _observers.begin();
    while (it != _observers.end()) {
        if (it->expired())
            it = _observers.erase(it);
        else {
            // If the boost is activated, the player doesn't want to interact with it again
            // should it still exist.
            it->lock()->notifyCollision(*this, isSupported);      // Returns confirmation bool
            ++it;
        }
    }

}

double Player::getDownwardPull() const {
    double dwp = _downwardPull;
    for (auto scaler : _pullScalers)
        dwp *= scaler.first;

    return dwp;
}

void Player::resetDownwardPull() {
    _downwardPull = - 2.0 * _jumpHeight;
}

void Player::resetYVelocity() {
    _velocity.second =  2.0 * _jumpHeight;
}

void Player::addDownwardPullScale(float scale, double height) {
    _pullScalers.emplace_back(std::pair<float, double>{scale, height});
}

void Player::registerObserver(std::weak_ptr<Bonus> observer) {
    _observers.emplace_back(observer);
}

double Player::getJumpHeight() const {
    return _jumpHeight;
}



/*
 *      PRIVATE methods
 */

bool Player::handleMovement(double delta) {
    std::pair<double, double> moveVector = findMoveVector(delta);

    // Apply movement first
    move(moveVector);


    bool isSupported = false;
    auto solidCollisions = getSolidCollisions(moveVector);

    // Only keep top collisions
    auto it = solidCollisions.begin();
    while (it != solidCollisions.end()) {
        if (!it->topCollision)
            it = solidCollisions.erase(it);
        else
            ++it;
    }


    // Handle pushback
    if (!solidCollisions.empty()) {
        std::vector<std::pair<double, double>> pushbackVectors = {};
        for (auto& collision: solidCollisions) {
            pushbackVectors.emplace_back(collision.pushback);
        }

        size_t longestIndex = Utility::getLongestVectorIndex(pushbackVectors);
        auto longestVector = pushbackVectors.at(longestIndex);
        isSupported = true;
        solidCollisions.at(longestIndex).collidedWith->notifyCollision(*this, isSupported);

        auto solidBB = solidCollisions.at(longestIndex).collidedWith->getCollisionObject().getBoundingBox();
        auto playerBB = getCollisionObject().getBoundingBox();

        // Only do pushback if foot of player inside solid object
        if (solidBB.at(1) <= playerBB.at(1) && playerBB.at(1) <= solidBB.at(3)) {
            move(longestVector);
            moveVector.second += longestVector.second;
        }

        resetYVelocity();
    }


    // Process bonus effects
    // The to remove indexes are specified back to front in the list of scalers,
    // so erasure is completed correctly.
    for (size_t idx = _pullScalers.size(); idx > 0; --idx) {
        auto& scaler = _pullScalers.at(idx - 1);
        scaler.second -= std::min(scaler.second, std::abs(moveVector.second));
        if (Utility::approximates(scaler.second, 0))
            _pullScalers.erase(_pullScalers.begin() + idx - 1);
    }


    return isSupported;
}

std::pair<double, double> Player::findMoveVector(double delta) {
    std::pair<double, double> moveVector{0, 0};
    // vf = v0 + at
    // 0  = v0 + -1t
    // t  = -v0 / -1 = v0
    double stopDelta = std::abs(_velocity.first);
    if (delta < stopDelta) stopDelta = delta;
    moveVector.first = _velocity.first * stopDelta;
    if (_velocity.first < 0)
        _velocity.first += stopDelta;
    if (_velocity.first > 0)
        _velocity.first -= stopDelta;

    const double downwardPull = getDownwardPull();

    // t = (vf - v0) / a
    double terminalDelta = downwardPull != 0 ? (((- _terminalVelocity) - _velocity.second) / downwardPull) : 0;
    // Terminal velocity not yet reached.
    // Move until terminal velocity
    if (terminalDelta > 0) {
        if (delta < terminalDelta) terminalDelta = delta;
        // rf = r0 + vt + (1/2)at²
        moveVector.second += _velocity.second * terminalDelta + downwardPull / 2.0 * terminalDelta * terminalDelta;
        _velocity.second += downwardPull * terminalDelta;        // vf = v0 + at
        delta -= terminalDelta;
    }

    // Travel at current velocity until delta depleted.
    // This may or may not be terminal velocity
    if (delta > 0)
        moveVector.second += _velocity.second * delta;      // rf = r0 + vt

    return moveVector;
}


