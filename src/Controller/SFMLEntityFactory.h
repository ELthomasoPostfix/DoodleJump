//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_SFMLENTITYFACTORY_H
#define DOODLEJUMP_SFMLENTITYFACTORY_H

#include "../Model/AbstractEntityFactory/AbstractEntityFactory.h"
#include "../View/EntityView/TemplateView.h"

//! An implementation of the ::AbstractEntityFactory interface, used to construct entities with a related view attached.
/*!
 * The naming of this concrete entity factory is perhaps misleading, as it does not
 * utilize any SFML provided functionality. It instead makes use of the doodle jump logic
 * and view libraries to construct ::TemplateView view entities and assigns their members.
 */
class SFMLEntityFactory : public AbstractEntityFactory {
    public:
        SFMLEntityFactory(Game& observer, const TexturesInfo& info);

        //! Create a ::Player object with the correct view attached.
        std::shared_ptr<Player> createPlayer() override;

        //! Create a ::StaticPlatform object with the correct view attached.
        std::shared_ptr<StaticPlatform> createStaticPlatform() override;

        //! Create a ::HorizontalPlatform object with the correct view attached.
        std::shared_ptr<HorizontalPlatform> createHorizontalPlatform() override;

        //! Create a ::VerticalPlatform object with the correct view attached.
        std::shared_ptr<VerticalPlatform> createVerticalPlatform() override;

        //! Create a ::TemporaryPlatform object with the correct view attached.
        std::shared_ptr<TemporaryPlatform> createTemporaryPlatform() override;

        //! Create a ::Jetpack object with the correct view attached.
        std::shared_ptr<Jetpack> createJetpack() override;

        //! Create a ::Spring object with the correct view attached.
        std::shared_ptr<Spring> createSpring() override;

        //! Create a ::BGTile object with the correct view attached.
        std::shared_ptr<BGTile> createBGTile() override;

};


#endif //DOODLEJUMP_SFMLENTITYFACTORY_H
