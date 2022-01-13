//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_SFMLENTITYFACTORY_H
#define DOODLEJUMP_SFMLENTITYFACTORY_H

#include "../../Game/AbstractEntityFactory/AbstractEntityFactory.h"
#include "../EntityView/TemplateView.h"

// TODO  If the Entity registration functionality is deleted,
//  then the ::World must store unique_ptr instances instead???
//  ==> Return unique ptrs from these methods (and AbstrEFact also) then.
class SFMLEntityFactory : public AbstractEntityFactory {
    public:
        SFMLEntityFactory(Game& observer, const TexturesInfo& info);

        //! Create a ::Player object with the correct view attached.
        std::shared_ptr<Player> createPlayer() override;

        // TODO revise comment
        //! Create a ::StaticPlatform object with the correct view attached.
        std::shared_ptr<StaticPlatform> createStaticPlatform() override;

        // TODO revise comment
        //! Create a ::HorizontalPlatform object with the correct view attached.
        std::shared_ptr<HorizontalPlatform> createHorizontalPlatform() override;

        // TODO revise comment
        //! Create a ::VerticalPlatform object with the correct view attached.
        std::shared_ptr<VerticalPlatform> createVerticalPlatform() override;

        // TODO revise comment
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
