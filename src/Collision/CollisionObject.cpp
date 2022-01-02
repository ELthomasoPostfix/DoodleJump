//
// Created by Thomas Gueutal on 13/11/2021.
//

#include <vector>
#include <algorithm>
#include "CollisionObject.h"
#include <iostream>

/*
 *      PUBLIC methods
 */

CollisionObject::CollisionObject(const double positionX,
                                 const double positionY,
                                 Rect shape)
                                 : GameObject(positionX, positionY),
                                 _collisionShape(shape),
                                 _updated(false) {}

Rect CollisionObject::getCollisionShape() const {
    return _collisionShape;
}

bool CollisionObject::checkCollision(CollisionObject& other) {

    // TODO Only rectangular shapes with sides either perpendicular to or parallel to the x-axis
    //  are used, so no slope different from 0 or +/- inf occur
    //  ==> If they do occur, then collision must be reworked.

    auto colShape = getCollisionShape();
    auto otherColShape = other.getCollisionShape();

    return hasPointsInBounds(getBoundingBox(), otherColShape) ||
    hasPointsInBounds(other.getBoundingBox(), colShape);
}

std::pair<double, double>
CollisionObject::determinePushback(const std::pair<double, double> &moveDir,
                                   CollisionObject &container,
                                   double scaleFactor,
                                   bool requireCollision) {

    std::pair<double, double> neutralPushback{0.0, 0.0};

    if (requireCollision && !checkCollision(container))
        return neutralPushback;

    // Edge case
    if (moveDir.first == 0 && moveDir.second == 0)
        return neutralPushback;


    const double moveSlope = Utility::determineSlope(0.0, 0.0, moveDir.first, moveDir.second);
    std::pair<double, double> pushback;

    auto &bb = getBoundingBox();
    auto &cbb = container.getBoundingBox();


    /*   II |  I
     *  ----|----
     *  III | IV
     */

    // Horizontal movement
    if (moveSlope == 0) {
        const double xPushback = moveDir.first > 0 ?
                                 cbb.at(0) - bb.at(2) : cbb.at(2) - bb.at(0);
        pushback = {xPushback, 0};

        // Vertical movement
    } else if (Utility::isInf(moveSlope)) {
        // move dir slope of +inf
        if (moveDir.second > 0)
            pushback = {0, cbb.at(1) - bb.at(3)};   // (0, cbb.minY - bb.maxY) : move this.maxY to other.minY
            // move dir slope of -inf
        else
            pushback = {0, cbb.at(3) - bb.at(1)};  // (0, cbb.maxY - bb.minY) : move this.minY to other.maxY

        // Angled movement
    } else {
        const double guessXPushback = moveDir.first > 0 ?
                                      cbb.at(0) - bb.at(2) : cbb.at(2) - bb.at(0);
        const double guessYPushback = moveSlope * guessXPushback;

        // Quadrant I (x > 0) or II (x < 0), overcompensated
        if (moveDir.second > 0 && bb.at(3) + guessYPushback < cbb.at(1)) {
            // (matchingX, other.minY - this.maxY) : move this.maxY to other.minY AND find the matching x
            const double minYPushback = cbb.at(1) - bb.at(3);
            pushback = {minYPushback / moveSlope, minYPushback};

            // Quadrant IV (x > 0) or III (x < 0), overcompensated
        } else if (moveDir.second < 0 && bb.at(1) + guessYPushback > cbb.at(3)) {
            // (matchingX, other.maxY - this.minY) : move this.minY to other.maxY AND find the matching x
            const double maxYPushback = cbb.at(3) - bb.at(1);
            pushback = {maxYPushback / moveSlope, maxYPushback};
        } else {
            pushback = {guessXPushback, guessYPushback};
        }
    }

    // If the dot product of the moveDir vector and the pushback vector is positive,
    // then the angle between them lies between [-90, 90], meaning that
    // container is located roughly in the same direction as moveDir points to.
    if (Utility::dot2(moveDir, pushback) > 0)
        return neutralPushback;
    else {
        if (!requireCollision) {

            // pushed back bounding box
            auto pbb = bb;
            pbb.at(0) += pushback.first;
            pbb.at(1) += pushback.second;
            pbb.at(2) += pushback.first;
            pbb.at(3) += pushback.second;

            // If the pushed back bounding box does not touch/border the container's bounding box,
            // then the push back is considered invalid.
            if ((pbb.at(0) < cbb.at(0) - Utility::epsilon() && pbb.at(2) < cbb.at(0) - Utility::epsilon()) ||
                (pbb.at(0) > cbb.at(2) + Utility::epsilon() && pbb.at(2) > cbb.at(2) + Utility::epsilon()) ||
                (pbb.at(1) < cbb.at(1) - Utility::epsilon() && pbb.at(3) < cbb.at(1) - Utility::epsilon()) ||
                (pbb.at(1) > cbb.at(3) + Utility::epsilon() && pbb.at(3) > cbb.at(3) + Utility::epsilon()))
                return neutralPushback;
        }
        return {pushback.first * scaleFactor, pushback.second * scaleFactor};
    }
}

void CollisionObject::move(double destinationX, double destinationY) {
    const double moveVec[2] = {destinationX - this->getPosition().first,
                               destinationY - this->getPosition().second};
    setPosition(destinationX, destinationY);

    // TODO  Rework collisionShape???
    for (unsigned int i = 0; i < _collisionShape.size(); ++i) {
        const auto& point = _collisionShape.at(i);
        setPoint(i, point.first + moveVec[0], point.second + moveVec[1]);
    }
}

void CollisionObject::move(const std::pair<double, double> &destination) {
    move(destination.first, destination.second);
}

std::pair<double, double> CollisionObject::determineAbsoluteCenterOfMass(const Rect& shape) {
    double x = 0.0, y = 0.0;

    for (const auto& line : shape) {
        x += line.first;
        y += line.second;
    }

    return {x / static_cast<double>(shape.size()), y / static_cast<double>(shape.size())};
}

std::pair<double, double> CollisionObject::determineRelativeCenterOfMass(const Rect &shape) {
    double x = 0.0, y = 0.0;
    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();

    for (const auto& line : shape) {
        x += line.first;
        y += line.second;

        minX = std::min(minX, line.first);
        minY = std::min(minY, line.second);
    }

    return {(x / static_cast<double>(shape.size())) - minX,
            (y / static_cast<double>(shape.size())) - minY };
}




/*
 *      PRIVATE methods
 */

const std::array<double, 4> &CollisionObject::getBoundingBox() {
    if (!_updated)
        updateBoundingBox();
    return _boundingBox;
}

void CollisionObject::setPoint(const unsigned int index, const double x, const double y) {
    try {
        _updated = false;
        std::pair<double, double> &point = _collisionShape.at(index);
        point.first = x;
        point.second = y;
    } catch (std::exception& e) {
        throw;  // TODO  how do i handle exceptions ???
    }
}

const std::pair<double, double> &CollisionObject::getPoint(const unsigned int index) {
    return _collisionShape.at(index);
}

bool CollisionObject::hasPointsInBounds(const std::array<double, 4> &bounds, const Rect &shape) {

    // Check collision of rectanglesZ
    for (const auto& point : shape) {
        if (pointIsInBounds(bounds, point))
            return true;
    }

    return false;
}

bool CollisionObject::pointIsInBounds(const std::array<double, 4> &bounds, const std::pair<double, double> &point) {
    // create Aliases
    const double& minX = bounds.at(0);
    const double& minY = bounds.at(1);
    const double& maxX = bounds.at(2);
    const double& maxY = bounds.at(3);
    const double& x = point.first;
    const double& y = point.second;

    return minX <= x && x <= maxX && minY <= y && y <= maxY;
}

void CollisionObject::updateBoundingBox() {
    // Reset values
    _boundingBox.at(0) = std::numeric_limits<double>::infinity();
    _boundingBox.at(1) = std::numeric_limits<double>::infinity();
    _boundingBox.at(2) = - std::numeric_limits<double>::infinity();
    _boundingBox.at(3) = - std::numeric_limits<double>::infinity();

    // Create aliases
    double& minX = _boundingBox.at(0);
    double& minY = _boundingBox.at(1);
    double& maxX = _boundingBox.at(2);
    double& maxY = _boundingBox.at(3);

    // Update values
    for (const auto& point : _collisionShape) {
        minX = std::min(minX, point.first);
        minY = std::min(minY, point.second);
        maxX = std::max(maxX, point.first);
        maxY = std::max(maxY, point.second);
    }

    _updated = true;
}







