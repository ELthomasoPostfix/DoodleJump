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

//! A class that provides collision functionality between ::CollisionObject s.
/*!
 *
 */
class CollisionObject : public GameObject {
    public:
        //! A constructor that assumes (\p positionX, \p positionY) to be the coordinates of the (center of the) collision shape.
        /*!
         * The constructor assumes that for a given shape, the shape contains
         * its points sorted in clockwise fashion.
         * \param positionX The x-coordinate of the collision shape's position,
         * \param positionY The y-coordinate of the collision shape's position,
         * \param shape The collision shape,
         */
        explicit CollisionObject(double positionX,
                                 double positionY,
                                 Rect shape);

        //! Move the ::CollisionObject, this includes its position and collision shape, to the specified location.
        /*!
         * Move the position member inherited from ::GameObject to the specified destination.
         * The points of the collision shape will be moved according to the same movement vector that
         * the position is moved along.
         */
        void move(double destinationX, double destinationY) final;

        //! Check whether the caller's and \p other ::CollisionObject's collision shapes overlap.
        /*!
         * \note The use of lazy loading for the bounding box prevents the const qualification of the \p other parameter.
         */
        bool checkCollision(CollisionObject &other);



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

        //! get a copy of the collision shape.
        Rect getCollisionShape() const;

    private:

        //! Get the bounding box of the current collision shape.
        /*!
         * The bounding box of collision shape is the smallest rectangle that completely
         * contains the collision shape.
         */
        const std::array<double, 4>& getBoundingBox();

        //! Set the coordinates of a point in the collision shape.
        inline void setPoint(unsigned int index, double x, double y);

        inline const std::pair<double, double>& getPoint(unsigned int index);

        //! Check whether any point part of the contents are located within the bounding box of the container.
        static bool hasPointsInBounds(const std::array<double, 4> &bounds, const Rect& container);

        //! update the boundingBox of the ::CollisionObject.
        void updateBoundingBox();

    private:
        // TODO add a 'std::pair<double, double>& getPoint(index)' and give it graceful out of bounds index exception
        Rect _collisionShape;
        std::array<double, 4> _boundingBox;
        bool _updated;


};


#endif //DOODLEJUMP_COLLISIONOBJECT_H
