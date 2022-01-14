//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_HORIZONTALPLATFORM_H
#define DOODLEJUMP_HORIZONTALPLATFORM_H

#include "Platform.h"

//! A platform that moves left and right between two bounding values.
class HorizontalPlatform : public Platform {
    public:
        explicit HorizontalPlatform(Rect& rect);

        ~HorizontalPlatform() override = default;

        //! Handle the platform's side-to-side movement.
        void process(double delta) override;

        //! Set the left and right bounds of the horizontal platform, in that order.
        void setBounds(const std::pair<double, double>& bounds);

    private:
        //! Recalculate the movement speed of the platform based on the bounds.
        void recalculateMovementSpeed();

    private:
        bool _left;
        std::pair<double, double> _bounds;
        double _movementPerSecond;
};


#endif //DOODLEJUMP_HORIZONTALPLATFORM_H
