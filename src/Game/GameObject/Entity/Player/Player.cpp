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
    _jumpHeight = 4.0 /10.0 * static_cast<double>(World::getInstance()->getCameraDimensions().second);
    _terminalVelocity = 2 * _jumpHeight;
    _velocity = {0, 0};      // initially stand still
    resetDownwardPull();
}

Player::~Player() {
    signalRoundEnd();
    // TODO Doesn't the player need to live during the end animation???
    //  ==> Wouldn't keeping a weak_ptr work better?
    //  ==> transformable into shared_ptr for operations
}

void Player::process(double delta) {

    // Applies the movement vector of the player based on delta time.
    // Whether the player landed onto the top of a solid object.
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

void Player::addDownwardPullScale(float scale, unsigned int height) {
    _pullScalers.emplace_back(std::pair<float, unsigned int>{scale, height});
}

void Player::registerObserver(std::weak_ptr<Bonus> &observer) {
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

    // only keep top collisions
    auto it = solidCollisions.begin();
    while (it != solidCollisions.end()) {
        if (!it->topCollision)
            it = solidCollisions.erase(it);
        else
            ++it;
    }


    // handle pushback
    if (!solidCollisions.empty()) {
        std::vector<std::pair<double, double>> pushbackVectors = {};
        for (auto& collision: solidCollisions) {
            pushbackVectors.emplace_back(collision.pushback);
        }

        size_t longestIndex = Utility::getLongestVectorIndex(pushbackVectors);
        auto longestVector = pushbackVectors.at(longestIndex);
        move(longestVector);
        moveVector.second += longestVector.second;
        resetYVelocity();
        isSupported = true;
    }

    for (auto scaleIt = _pullScalers.begin(); scaleIt != _pullScalers.end(); ++scaleIt) {
        scaleIt->second -= std::min(scaleIt->second, static_cast<unsigned int>(std::ceil(moveVector.second)));
        if (scaleIt->second == 0)
            scaleIt = _pullScalers.erase(scaleIt);
    }

    return isSupported;
}

std::pair<double, double> Player::findMoveVector(double delta) {
    std::pair<double, double> moveVector{0, 0};
    // vf = v0 + at
    // 0  = v0 + -1t
    // t  = -v0 / -1 = v0
    double stopDelta = _velocity.first;
    if (delta < stopDelta) stopDelta = delta;
    moveVector.first = _velocity.first * stopDelta;
    _velocity.first = std::max(0.0, _velocity.first - stopDelta);    // TODO  poll world for RIGHT event     ==> _velocity.first = pollRightEvent() == true
    // _velocity.first = std::min(_velocity.first + pollEvent(dj::Event::RIGHT), 1.0);  // TODO this??

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


