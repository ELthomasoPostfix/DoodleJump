//
// Created by Thomas Gueutal on 29/12/2021.
//

#include "Camera.h"


/*
 *      PUBLIC methods
 */

std::unique_ptr<Camera>& Camera::getInstance(const unsigned int width, const unsigned int height) {
    static std::unique_ptr<Camera> camera(new Camera(width, height));
    return camera;
}

//void Camera::clip(const std::vector<std::shared_ptr<Entity>>& entities) {
//    std::vector<std::shared_ptr<Entity>> clippedEntities;
//    for (const auto& entity : entities) {
//        if (!isVisible(entity->getView()))
//            clippedEntities.emplace_back(entity);
//        // TODO
//        //  1) assign ::Entity class a View
//        //  ==> virtual inheritance (public GameObject, public virtual CollisionObject) ??
//        //   OR Extract BoundingBox into own class ??
//        //  ==> https://stackoverflow.com/questions/27545888/is-multiple-inheritance-from-the-same-base-class-via-different-parent-classes-re
//        //  2) if (!isVisible(object.view)) clip object
//        //  3) rescale (make copies of Entities??)
//    }
//}

std::pair<unsigned int, unsigned int> Camera::getDimensions() const {
    return {_width, _height};
}

void Camera::setDimensions(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

void Camera::move(const std::pair<double, double> &moveVector) {
    _cameraArea->move(moveVector);
}

void Camera::setPosition(const std::pair<double, double> &destination) {
    _cameraArea->setPosition(destination);
}

// TODO Check header file
/*
bool Camera::isVisible(EntityView &view) {
    return _cameraArea->checkCollision(*view.getViewArea());
}
*/

const std::array<double, 4> & Camera::getBoundingBox() {
    return _cameraArea->getBoundingBox();
}


/*
 *      PRIVATE methods
 */

Camera::Camera(const unsigned int width, const unsigned int height)
        : _width(width), _height(height) {}


