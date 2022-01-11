//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_TEMPLATEVIEW_H
#define DOODLEJUMP_TEMPLATEVIEW_H

#include "EntityView.h"


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
