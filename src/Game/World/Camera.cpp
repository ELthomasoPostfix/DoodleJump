//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Camera.h"


/*
 *      PUBLIC methods
 */

Camera::Camera(const std::shared_ptr<Scoreboard>& observer,
               const double wWidth, const double wHeight, Rect& viewArea)
    : _cameraArea(viewArea, true, false), _observer(observer) {
    recalibrateFocusY();
    setIndependentDimensions(wWidth, wHeight);
}


std::pair<unsigned int, unsigned int> Camera::getDimensions() {
    return {_cameraArea.getBoundingWidth(), _cameraArea.getBoundingHeight()};
}

std::pair<double, double> Camera::getIndependentDimensions() {
    return {_wWidth, _wHeight};
}

void Camera::setIndependentDimensions(const double width, const double height) {
    if (width > 0)
        _wWidth = std::ceil(width);

    if (height > 0)
        _wHeight = std::ceil(height);
}

void Camera::move(const double moveX, const double moveY) {
    _cameraArea.move(moveX, moveY);
    moveYFocus(moveY);
}

void Camera::move(const std::pair<double, double> &moveVector) {
    _cameraArea.move(moveVector);
    moveYFocus(moveVector.second);
}

void Camera::setPosition(const std::pair<double, double> &destination) {
    _cameraArea.setPosition(destination);
    recalibrateFocusY();
}

bool Camera::isVisible(CollisionObject &viewArea) {
    return _cameraArea.checkCollision(viewArea, true);
}

const std::array<double, 4> & Camera::getBoundingBox() {
    return _cameraArea.getBoundingBox();
}

void Camera::project(CollisionObject &viewArea) {
    auto pos = viewArea.getPosition();
    // independent dimensions
    auto iDims = getIndependentDimensions();
    // camera area dimensions
    std::pair<double ,double> aDims = {_cameraArea.getBoundingWidth(),
                                       _cameraArea.getBoundingHeight()};

    auto& cameraBoundingBox = _cameraArea.getBoundingBox();

    const double projX = (pos.first - cameraBoundingBox.at(0)) / aDims.first * iDims.first;
    const double projY = (pos.second - cameraBoundingBox.at(1)) / aDims.second * iDims.second;

    // Apply projection in place
    viewArea.setPosition(projX, projY);
}

void Camera::replaceCameraArea(Rect &newArea) {
    _cameraArea = CollisionObject(newArea, true, false);
    recalibrateFocusY();
}


double Camera::getFocusY() const {
    return _focusY;
}



/*
 *      PRIVATE methods
 */


void Camera::recalibrateFocusY() {
    _focusY = CollisionObject::determineAbsoluteCenterOfMass(_cameraArea.getCollisionShape()).second;
}

void Camera::printCameraError(const std::string &what) {
    std::cout << "Error concerning a camera : " << what << std::endl;
}

void Camera::moveYFocus(double moveY) {
    _focusY += moveY;
    try {
        if (moveY > 0)
            _observer->update(moveY);
    } catch (std::runtime_error& e) {
        printCameraError(e.what());
    }
}






