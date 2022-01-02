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

bool CollisionObject::checkCollision(CollisionObject& other) {

    // TODO Only rectangular shapes with sides either perpendicular to or parallel to the x-axis
    //  are used, so no slope different from 0 or +/- inf occur
    //  ==> If they do occur, then collision must be reworked.

    auto colShape = getCollisionShape();
    auto otherColShape = other.getCollisionShape();

    return hasPointsInBounds(getBoundingBox(), otherColShape) ||
    hasPointsInBounds(other.getBoundingBox(), colShape);
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

Rect CollisionObject::getCollisionShape() const {
    return _collisionShape;
}

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
    // create Aliases
    const double& minX = bounds.at(0);
    const double& maxX = bounds.at(1);
    const double& minY = bounds.at(2);
    const double& maxY = bounds.at(3);

    // Check collision of rectanglesZ
    for (const auto& point : shape) {
        const double& x = point.first;
        const double& y = point.second;

        if (minX <= x && x <= maxX && minY <= y && y <= maxY)
            return true;
    }

    return false;
}

void CollisionObject::updateBoundingBox() {
    // Reset values
    _boundingBox.at(0) = std::numeric_limits<double>::infinity();
    _boundingBox.at(1) = - std::numeric_limits<double>::infinity();
    _boundingBox.at(2) = std::numeric_limits<double>::infinity();
    _boundingBox.at(3) = - std::numeric_limits<double>::infinity();

    // Create aliases
    double& minX = _boundingBox.at(0);
    double& maxX = _boundingBox.at(1);
    double& minY = _boundingBox.at(2);
    double& maxY = _boundingBox.at(3);

    // Update values
    for (const auto& point : _collisionShape) {
        minX = std::min(minX, point.first);
        maxX = std::max(maxX, point.first);
        minY = std::min(minY, point.second);
        maxY = std::max(maxY, point.second);
    }

    _updated = true;
}





