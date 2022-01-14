//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_TEMPLATEVIEW_H
#define DOODLEJUMP_TEMPLATEVIEW_H

#include "EntityView.h"

//! A base class for ::Entity objects that require a visual component AND which implement a constructor requiring only a single collision shape.
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

        //! Provide the game object, the observer, with a copy of the current view component.
        /*!
         * As the logic library has no use for views nor need any knowledge of them,
         * this is the actual implementation of the view logic required for the game
         * object to display any visual component besides text.
         * \see Entity::display(), ::EntityView::notify()
         */
        void display() override;

        //! Return the ::EntityView view area instead of the ::Entity collision object to be used in clipping.
        /*!
         * \see ::Entity::getClipObject(), ::Camera::isVisible()
         */
        CollisionObject& getClipObject() override;

    private:
        //! Expansion of the entity move behavior to now also move the view component's view area.
        void moveBehaviour(double moveX, double moveY) override;

        //! Expansion of the entity set behavior to now also set the the position of the view component's view area.
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
