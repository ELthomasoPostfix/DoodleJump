//
// Created by Thomas Gueutal on 11/01/2022.
//

#include "StaticPlatformView.h"


StaticPlatformView::StaticPlatformView(Game &observer, Rect& collShape, Rect& viewArea)
        : StaticPlatform(collShape), EntityView(observer, viewArea) {
    // TODO construct _viewArea
    //_textureID = PLAYER

}

void StaticPlatformView::display() {
    notify();
}

CollisionObject &StaticPlatformView::getClipObject() {
    return _viewArea;
}

void StaticPlatformView::moveBehaviour(double moveX, double moveY) {
    getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}

void StaticPlatformView::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}


