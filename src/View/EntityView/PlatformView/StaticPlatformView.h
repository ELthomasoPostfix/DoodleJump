//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_STATICPLATFORMVIEW_H
#define DOODLEJUMP_STATICPLATFORMVIEW_H


#include "../../../Game/GameObject/Entity/Platform/StaticPlatform.h"
#include "../EntityView.h"

class StaticPlatformView : public StaticPlatform, public EntityView {
public:
    StaticPlatformView(Game &observer, Rect& collShape, Rect& viewArea);

    ~StaticPlatformView() override = default;

    void display() override;

    CollisionObject& getClipObject() override;

    void moveBehaviour(double moveX, double moveY) override;

    void setBehaviour(double moveX, double moveY, double prevX, double prevY) override;
};



#endif //DOODLEJUMP_STATICPLATFORMVIEW_H
