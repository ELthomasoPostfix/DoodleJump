//
// Created by Thomas Gueutal on 05/01/2022.
//

#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../resources.h"
#include "../../Model/World/Event.h"
#include "../../Model/GameObject/Collision/CollisionObject.h"

class Game;

//! The sub class of entity that provides support for introducing a visualisation of the gale state.
/*!
 * To make the distinction between the collision shape and view shape of and entity,
 * a view entity view contains its own collision object. This can then be used by the
 * ::TemplateView to substitute collision clipping for view clipping.
 */
class EntityView {
    public:
        //! The bare minimum constructor to support a separated visual representation of an entity.
        /*!
         * \param observer The game functioning as the controller.
         * \param viewArea The collision shape to be used for clipping.
         */
        EntityView(Game& observer, Rect& viewArea);

        virtual ~EntityView();

        //! Notify all observers that the view is ready to be drawn.
        void notify();

        //! Move the view by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the view to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Get the bounding box in world space coordinates of the view.
        CollisionObject& getViewArea();

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

        //! Set the id of the texture to use when displaying the entity.
        void setTextureID(size_t textureID);

        //! Set the color of the rectangle representation when displaying the entity.
        void setFillColor(unsigned int red, unsigned int green, unsigned int blue);

    protected:
        //! Make a copy of the to display view information, to pass to the observer.
        EntityView getViewCopy() const;

    protected:
        CollisionObject _viewArea;
        size_t _textureID;
        bool _hasTexture;
        std::array<uint8_t, 3> _rgbFillColor;

        Game& _observer;        // TODO  is Game a View observer? Should Camera be one instead?


};


#endif //DOODLEJUMP_ENTITYVIEW_H
