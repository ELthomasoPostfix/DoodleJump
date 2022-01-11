//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_TEMPLATEVIEW_H
#define DOODLEJUMP_TEMPLATEVIEW_H

#include "EntityView.h"

//! A base class for ::Entity objects that require a visual component AND which implement a constructor requiring only a single Rect.
/*!
 * Since the integration of the ::EntityView class and the ::Entity class results in
 * common implementations for several methods, this class enforces their conformity.
 * It also ensures that the view area of the entity view will be used by the camera
 * to clip entities instead of the collision shape, since the visual component, the
 * window, is now at play.
 * \note Should the instantiation of a view entity require a more complex constructor, then
 * this class may be derived into a variant implementing the required constructor. This will
 * not create unexpected behaviour, as the constructor of the TemplateView class solely calls
 * the constructors of its parent classes, without doing any computation.
 */
template<class DerivedEntity>
class TemplateView : public DerivedEntity, public EntityView {
public:
    TemplateView(Game &observer, Rect& collShape, Rect& viewArea);

    ~TemplateView() override = default;

    void display() override;

    CollisionObject& getClipObject() override;

    void moveBehaviour(double moveX, double moveY) override;

    void setBehaviour(double moveX, double moveY, double prevX, double prevY) override;
};



template<class DerivedEntity>
TemplateView<DerivedEntity>::TemplateView(Game &observer, Rect &collShape, Rect &viewArea)
    : DerivedEntity(collShape), EntityView(observer, viewArea)
{

}

template<class DerivedEntity>
void TemplateView<DerivedEntity>::display() {
    notify();
}

template<class DerivedEntity>
CollisionObject &TemplateView<DerivedEntity>::getClipObject() {
    return _viewArea;
}

template<class DerivedEntity>
void TemplateView<DerivedEntity>::moveBehaviour(double moveX, double moveY) {
    DerivedEntity::getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}

template<class DerivedEntity>
void TemplateView<DerivedEntity>::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    DerivedEntity::getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}


#endif //DOODLEJUMP_TEMPLATEVIEW_H
