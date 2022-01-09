//
// Created by Thomas Gueutal on 08/01/2022.
//

#include "PlayerView.h"

PlayerView::PlayerView(Game &observer, Rect& collShape, Rect& viewArea)
    : Player(collShape), EntityView(observer, viewArea) {
    // TODO construct _viewArea
    //_textureID = PLAYER

}

void PlayerView::display() {
    notify();
}

CollisionObject &PlayerView::getClipObject() {
    return _viewArea;
}
