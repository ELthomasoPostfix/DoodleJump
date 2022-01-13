//
// Created by Thomas Gueutal on 12/01/2022.
//

#include "Spawner.h"
#include "World.h"
#include "../AbstractEntityFactory/AbstractEntityFactory.h"
#include <random>


/*
 *      PUBLIC methods
 */

Spawner::Spawner(World &world) {
    resetSpawnLocation(world);
}

void Spawner::handleSpawning(World& world) {

    auto& ef = world._entityFactory;
    const double jumpHeight = world._player->getJumpHeight();
    auto camDimensions = world.getCameraDimensions();
    auto& camBB = world.getCameraBoundingBox();

    double maxBgY = - std::numeric_limits<double>::infinity();
    for (auto& bgTile : world._bgEntities) {  // TODO If other bg entities exist, then separate bg tile generation
        maxBgY = std::max(maxBgY, bgTile->getCollisionObject().getBoundingBox().at(3));
    }

    if (Utility::isInf(maxBgY))
        maxBgY = camBB.at(1);

    double bgTileHeight = std::numeric_limits<double>::infinity();
    double bgTileWidth = std::numeric_limits<double>::infinity();
    while (maxBgY < camBB.at(3)) {
        std::pair<double, double> tilePos = {camBB.at(0), maxBgY};
        while (tilePos.first < camBB.at(2)) {
            std::shared_ptr<BGTile> bgTile = ef->createBGTile();
            bgTile->setPosition(tilePos);
            addBGEntity(world, bgTile);

            if (Utility::isInf(bgTileHeight))
                bgTileHeight = bgTile->getClipObject().getBoundingHeight();
            if (Utility::isInf(bgTileWidth))
                bgTileWidth = bgTile->getClipObject().getBoundingWidth();

            tilePos.first += bgTileWidth;
        }
        if (Utility::isInf(bgTileHeight))
            break;
        else
            maxBgY += bgTileHeight;
    }



    if ((camBB.at(3) - _spawnLocation.second) > jumpHeight / 2.0) {

        auto &ran = Random::getInstance();
        auto distParams = ran->getDistributionParameters();
        const double mean   = distParams.first;
        const double stddev = distParams.second;

        double maxY = - std::numeric_limits<double>::infinity();
        bool spawnedVertical = false;
        for (int i = 0; i < 2; ++i) {

            double xOffset = ran->randomNormalized() * camDimensions.first / 2.0;
            if (_spawnLocation.first + xOffset > camBB.at(2))
                xOffset = - xOffset;
            const double xPos = Utility::clamp(_spawnLocation.first + xOffset, camBB.at(0), camBB.at(2));
            double yOffset = ran->randomNormalized() * jumpHeight / 2.0;
            if (_spawnLocation.second + yOffset > camBB.at(3))
                yOffset = camBB.at(3) - camDimensions.second / 100.0;
            const double yPos = Utility::clamp(_spawnLocation.second + yOffset, camBB.at(1), camBB.at(3));
            double platformFactor = ran->random(false);

            maxY = std::max(maxY, yPos);

            std::shared_ptr<Platform> platform;
            std::shared_ptr<Bonus> bonus;

            // +/- 15% chance
            if (platformFactor < mean - stddev)
                platform = ef->createHorizontalPlatform();
            // +/- 35% chance
            else if (platformFactor < mean) {
                platform = ef->createStaticPlatform();
                double bonusFactor = ran->random();
                // +/- 10.5% chance
                if (bonusFactor < mean - stddev)
                    bonus = ef->createSpring();
                else if (mean + stddev < bonusFactor)
                    bonus = ef->createJetpack();
            // +/- 15% chance
            } else if (platformFactor > mean + stddev) {
                platform = ef->createTemporaryPlatform();
            // +/- 35% chance
            } else if (!spawnedVertical && platformFactor > mean) {
                spawnedVertical = true;
                auto vplatform = ef->createVerticalPlatform();
                auto bounds = vplatform->getBounds();
                bounds.second = 0.5 * (camDimensions.second) + 0.375 * camDimensions.second * ran->randomNormalized();
                vplatform->setBounds(bounds);
                platform = vplatform;
            } else {
                platform = ef->createStaticPlatform();
            }
            platform->setPosition(xPos, yPos);
            addEntity(world, platform);

            if (bonus != nullptr) {
                bonus->setPosition(xPos, yPos);
                addBonus(world, bonus);
            }
            _spawnLocation = {xPos, yPos};
        }
    }

}

void Spawner::spawnPlayer(World &world) {
    resetSpawnLocation(world);

    auto starterPlatform = world._entityFactory->createStaticPlatform();
    starterPlatform->setPosition(_spawnLocation);
    addEntity(world, starterPlatform);

    _spawnLocation.second += starterPlatform->getCollisionObject().getBoundingHeight();
    _spawnLocation.second += world.getCameraDimensions().second * 1.0/10.0;
    auto player = world._entityFactory->createPlayer();
    player->setPosition(_spawnLocation);
    world._player = player;
    world.addEntity(player);
}



/*
 *      PROTECTED methods
 */

void Spawner::addEntity(World &world, const std::shared_ptr<Entity> &entity) {
    entity->registerScoreboardObserver(world._scoreboard);
    world.addEntity(entity);
}

void Spawner::addBonus(World &world, const std::shared_ptr<Bonus> &bonus) {
    bonus->registerScoreboardObserver(world._scoreboard);
    world._player->registerObserver(std::weak_ptr<Bonus>(bonus));
    world.addEntity(bonus);
}

void Spawner::addBGEntity(World &world, const std::shared_ptr<Entity> &bgEntity) {
    world.addBGEntity(bgEntity);
}

void Spawner::resetSpawnLocation(World &world) {
    _spawnLocation = {
            world._camera->getBoundingBox().at(0) + world._camera->getDimensions().first / 2.0,
            world._camera->getBoundingBox().at(1) + world._camera->getDimensions().second / 20.0
    };
}

