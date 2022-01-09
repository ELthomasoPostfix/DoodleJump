//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "CollisionObject.h"


/*
 *      PUBLIC methods
 */

CollisionObject::CollisionObject(Rect shape, bool isPhysical)
    : GameObject(0, 0), _collisionShape(std::move(shape)),
    _updated(false), _isPhysical(isPhysical), _origin(0, 0)
{
    auto& boundingBox = getBoundingBox();
    setPosition(boundingBox.at(0), boundingBox.at(1), false);
}

bool CollisionObject::checkCollision(CollisionObject& other, const bool forceCollision) {

    // TODO Only rectangular shapes with sides either perpendicular to or parallel to the x-axis
    //  are used, so no slope different from 0 or +/- inf occur
    //  ==> If they do occur, then collision must be reworked.

    if (!forceCollision && !(isPhysical() && other.isPhysical()) )
            return false;

    auto colShape = getCollisionShape();
    auto otherColShape = other.getCollisionShape();

    // If one of the collision shapes is located inside the other,
    // then only one of these check resolves to true.
    return hasPointsInBounds(getBoundingBox(), otherColShape) || hasPointsInBounds(other.getBoundingBox(), colShape);
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

void CollisionObject::setIsPhysical(const bool isPhysical) { _isPhysical = isPhysical; }

bool CollisionObject::isPhysical() const { return _isPhysical; }

Rect CollisionObject::getCollisionShape() const { return _collisionShape; }

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

double CollisionObject::getBoundingWidth()  {
    const auto& boundingBox = getBoundingBox();
    return std::abs(boundingBox.at(2) - boundingBox.at(0));
}

double CollisionObject::getBoundingHeight() {
    const auto& boundingBox = getBoundingBox();
    return std::abs(boundingBox.at(3) - boundingBox.at(1));
}

std::pair<double, double> CollisionObject::getOrigin() const {
    return _origin;
}

std::pair<double, double> CollisionObject::getAbsoluteOrigin() const {
    auto pos = getPosition();
    return {pos.first + _origin.first, pos.second + _origin.second};
}

void CollisionObject::setOrigin(const double originX, const double originY) {
    const double prevOX = _origin.first;
    const double prevOY = _origin.second;

    _origin.first = originX;
    _origin.second = originY;

    // The ::CollisionShape position remains the same, but the relative location of the
    // collision shape points, and thus their absolute location as well, in relation
    // to the ::CollisionObject 's position is altered.
    // Move the collision shape to reflect this.
    setBehaviour(-(_origin.first - prevOX), -(_origin.second - prevOY), prevOX, prevOY);

}

void CollisionObject::setOrigin(const std::pair<double, double>& origin) {
    setOrigin(origin.first, origin.second);
}

bool CollisionObject::isAbove(CollisionObject &other) {
    return getBoundingBox().at(1) >= other.getBoundingBox().at(3);
}




/*
 *      PROTECTED methods
 */

void CollisionObject::adjustCollisionShapePoints(const double moveX, const double moveY)
{
        for (unsigned int i = 0; i < _collisionShape.size(); ++i) {
                adjustPoint(i, moveX, moveY);
        }
}

void CollisionObject::moveBehaviour(const double moveX, const double moveY)
{
        adjustCollisionShapePoints(moveX, moveY);
}

void CollisionObject::setBehaviour(double moveX, double moveY, double prevX, double prevY)
{
        // Adjust collision shape
        adjustCollisionShapePoints(moveX, moveY);
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
        _collisionShape.at(index).first = x;
        _collisionShape.at(index).second = y;
    } catch (std::exception& e) {
            throw; // TODO  how do i handle exceptions ???
    }
}

void CollisionObject::adjustPoint(unsigned int index, double moveX, double moveY)
{
        try {
                _updated = false;
                _collisionShape.at(index).first += moveX;
                _collisionShape.at(index).second += moveY;
        } catch (std::exception& e) {
                throw; // TODO  how do i handle exceptions ???
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

std::array<double, 4> CollisionObject::determineBoundingBox(const Rect &shape) {
    std::array<double, 4> boundingBox{};

    // Set initial bounding values:
    //  [ minX, minY, maxX, maxY ]
    //  [ +inf, +inf, -inf, -inf ]
    boundingBox.at(0) = std::numeric_limits<double>::infinity();
    boundingBox.at(1) = std::numeric_limits<double>::infinity();
    boundingBox.at(2) = - std::numeric_limits<double>::infinity();
    boundingBox.at(3) = - std::numeric_limits<double>::infinity();

    // Create aliases
    double& minX = boundingBox.at(0);
    double& minY = boundingBox.at(1);
    double& maxX = boundingBox.at(2);
    double& maxY = boundingBox.at(3);

    // Update values
    for (const auto& point : shape) {
        minX = std::min(minX, point.first);
        minY = std::min(minY, point.second);
        maxX = std::max(maxX, point.first);
        maxY = std::max(maxY, point.second);
    }
    return boundingBox;
}

void CollisionObject::updateBoundingBox() {
    _boundingBox = determineBoundingBox(_collisionShape);
    _updated = true;
}






