//
// Created by Thomas Gueutal on 29/12/2021.
//

#ifndef DOODLEJUMP_CAMERA_H
#define DOODLEJUMP_CAMERA_H

#include "../../View/EntityView/EntityView.h"



class Camera {
    public:
        /*!
         * The initial call will result in the assignment of the width and height
         * parameters passed to it. All subsequent changes to the dimensions
         * must happen through setDimensions().
         */
        static std::unique_ptr<Camera>& getInstance(unsigned int width = 600,
                                                    unsigned int height = 800);

        //void clip(const std::vector<std::shared_ptr<Entity>>& entities);

        //! Get the dimensions, (width, height), of the rectangle onto which the ::Camera object will project the ::World.
        std::pair<unsigned int, unsigned int> getDimensions() const;

        //! Set the dimensions of the rectangle onto which the ::Camera object will project the ::World.
        void setDimensions(unsigned int width, unsigned int height);

        //! Move the ::Camera by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the ::Camera to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Check whether the view is visible inside the ::Camera object's camera area.
        bool isVisible(EntityView& view);

        //! Get the bounding box of the ::Camera.
        /*!
         * The bounding box of the camera describes which section of the ::World
         * object's world space the camera will keep and transform into the
         * needed independent coordinate system. The rest of the world space will be
         * clipped.
         */
        const std::array<double, 4>& getBoundingBox();

    private:
        unsigned int _width;
        unsigned int _height;
        std::unique_ptr<CollisionObject> _cameraArea;


        Camera(unsigned int width, unsigned int height);
        Camera(Camera const&);              // don't implement
        Camera& operator= (Camera const&);  // don't implement

};


#endif //DOODLEJUMP_CAMERA_H
