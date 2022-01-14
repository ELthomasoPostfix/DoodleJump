//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_VERTICALPLATFORM_H
#define DOODLEJUMP_VERTICALPLATFORM_H

#include "Platform.h"


class VerticalPlatform : public Platform {
    public:
        explicit VerticalPlatform(Rect& rect);

        ~VerticalPlatform() override = default;

        void process(double delta) override;

        //! Set the top and bottom bounds of the vertical platform, in that order.
        void setBounds(const std::pair<double, double>& bounds);

        //! get the top and bottom bounds of the vertical platform, in that order.
        std::pair<double, double> getBounds();

    private:
        //! Recalculate the movement speed of the platform based on the bounds.
        void recalculateMovementSpeed();

    private:
        bool _up;
        std::pair<double, double> _bounds;
        double _movementPerSecond;
};


#endif //DOODLEJUMP_VERTICALPLATFORM_H
