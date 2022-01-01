//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_COLLISIONOBJECT_H
#define DOODLEJUMP_COLLISIONOBJECT_H

#include <utility>
#include <limits>
#include <functional>
#include "../Utility/Utility.h"
#include "../GameObject.h"

using Rect = std::array<std::pair<double, double>, 4>;


class CollisionObject : public GameObject {
    public:
        //! A constructor that assumes (\p positionX, \p positionY) to be the coordinates of the (center of the) collision shape.
        /*!
         * The constructor assumes that for a given shape, the shape contains
         * its points sorted in clockwise fashion.
         */
        explicit CollisionObject(double positionX,
                                 double positionY,
                                 Rect shape);

        bool checkCollision(CollisionObject &other) const;

        void move(double destinationX, double destinationY) final;

        //! The center of mass of the shape.
        /*! The center of mass of the collision object shape, calculated as
         * the average of the xy coordinates of all points part of the shape,
         * utilizing the actual point coordinates.
         *
         */
         static std::pair<double, double> determineAbsoluteCenterOfMass(const Rect& shape);

        //! The center of mass of the shape relative to the bottom left corner of the bounding box.
        /*! The center of mass of the collision object shape, calculated as
         * the average of the xy coordinates of all points part of the shape,
         * utilizing the point coordinates translated such that the bottom left
         * corner of its bounding box was translated to the origin, (0, 0).
         */
        static std::pair<double, double> determineRelativeCenterOfMass(const Rect& shape);

        Rect getCollisionShape() const;

    private:
        inline void setPoint(unsigned int index, double x, double y);

        inline const std::pair<double, double>& getPoint(unsigned int index);

        //! Check whether any point part of the contents are located within the bounding box of the container.
        static bool hasPointsIn(const Rect& contents, const Rect& container);

    private:
        // TODO add a 'std::pair<double, double>& getPoint(index)' and give it graceful out of bounds index exception
        Rect _collisionShape;


};


#endif //DOODLEJUMP_COLLISIONOBJECT_H
