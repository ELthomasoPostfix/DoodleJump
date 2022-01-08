//
// Created by Thomas Gueutal on 05/01/2022.
//

#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../../Game/GameObject/Collision/CollisionObject.h"



class EntityView {
    public:
        virtual ~EntityView();

        //! Move the ::View by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the ::View to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Get the bounding box in world space coordinates of the view.
        const std::unique_ptr<CollisionObject>& getViewArea();

        //! Get the id of the texture used by this view. A view may not use a texture.
        /*!
         * If the view was assigned a texture, then a valid texture id
         * will be returned for use in the texture manager of ::Window/
         * If no texture was assigned, it is not guaranteed that a
         * valid texture id will be returned. There is no default
         * id value to indicate a texture-less view. Instead, utilize
         * the ::EntityView::hasTexture() method to verify.
         */
        size_t getTextureID() const;

        //! Check whether the view was assigned a texture.
        bool hasTexture() const;

        //! In case the view has not texture, then it will be assigned a fill color.
        /*!
         * The fill color can be used to represent the view as a rectangle of
         * the specified color. Even without a texture, the view may still
         * be simply represented. The color is represented by RGB values.
         */
        const std::array<uint8_t, 3>& getRGBFillColor() const;

    protected:
        std::unique_ptr<CollisionObject> _viewArea;
        size_t _textureID;
        bool _hasTexture;
        std::array<uint8_t, 3> _rgbFillColor;


};


#endif //DOODLEJUMP_ENTITYVIEW_H
