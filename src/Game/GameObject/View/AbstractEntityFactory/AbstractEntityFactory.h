//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_ABSTRACTENTITYFACTORY_H
#define DOODLEJUMP_ABSTRACTENTITYFACTORY_H

#include "../../Entity/Player/Player.h"
#include "../../Entity/Platform/Platform.h"
#include "../../Entity/BGTile/BGTile.h"
#include "../../Entity/Bonus/Bonus.h"



// TODO  Rename to AbstractEntityFactory ???
class AbstractEntityFactory {

    // TODO  contain the logic of entity spawning within the EntityFactory?
    //  ==> e.g. The EntityFactory keeps "totalCreated" and "lastCreatedPosition" members.
    //  If it "tC" is < 1, then spawn a platform. If "tC" == 1, then spawn the player on that
    //  platform. If it is > 1, then do whatever. Boost spawns must always follow a platform
    //  spawn and may alter the difficulty (distance to) the next platforms (e.g. by
    //  increasing/taking min(flat value, normal distr chance)) for platform spawn location.
    //  ==> IF THIS IS DONE, ONLY A CREATEENTITY() METHOD IS NEEDED!!!

        virtual std::shared_ptr<Player> createPlayer(double positionX, double positionY) = 0;

        // TODO OPTIONS
        //      1) let the factory decide between types of platforms and contain the business logic
        //      2) add more specific creation methods
        virtual std::shared_ptr<Platform> createPlatform(double positionX, double positionY) = 0;

        // TODO OPTIONS
        //      1) let the factory decide between types of bonuses and contain the business logic
        //      2) add more specific creation methods
        virtual std::shared_ptr<Bonus> createBonus(double positionX, double positionY) = 0;

        // TODO OPTIONS
        //      1) let the factory decide between types of bonuses and contain the business logic
        //      2) add more specific creation methods
        virtual std::shared_ptr<BGTile> createBGTile(double positionX, double positionY) = 0;
};


#endif //DOODLEJUMP_ABSTRACTENTITYFACTORY_H
