//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Spring.h"

/*
 *      PUBLIC methods
 */

Spring::Spring(Rect& rect) : Bonus(rect) {

}

void Spring::process(double delta) {
}

bool Spring::update(bool callerIsSupported) {
    if (!callerIsSupported)
        return false;

    auto observable = _observable.lock();

    // The observable must have landed so that the spring would be stepped on.
    if (observable->getCollisionObject().checkCollision(this->getCollisionObject()) &&
        observable->getCollisionObject().isAsHighAs(this->getCollisionObject())) {
        observable->addDownwardPullScale(.2f);
        return true;
    }
    // TODO  somehow signal that spring should now die

    return false;
}
