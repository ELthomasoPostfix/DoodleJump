//
// Created by Thomas Gueutal on 07/01/2022.
//

#ifndef DOODLEJUMP_RESOURCEMANAGER_H
#define DOODLEJUMP_RESOURCEMANAGER_H


#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cassert>


//! A resource manager to generally handle textures and fonts.
/*!
 * The texture manager provides an easy and fast definition of a storage object for any
 * texture, font or other resource. The definition of this class template is essential
 * in the construction of the window manager, facilitating switching to different graphics
 * implementation of the DoodleJump game.
 * \see ::WindowManager
 * \note The code for this ResourceManager was taken from
 * <a href="https://github.com/SFML/SFML-Game-Development-Book/tree/master/02_Resources/Include/Book">
 * this github page</a> and merged into this one file (initially separate .hpp and .ini files). Small
 * renames were applied due to preference.
 */
template <typename Resource, typename Identifier>
class ResourceManager
{
public:
    void load(Identifier id, const std::string& filename)
    {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("ResourceMangager::load() - Failed to load \"" + filename + "\"");
        insert_resource(id, std::move(resource));
    }
    void load(Identifier id, std::unique_ptr<Resource> r)
    {
        if (!r)
            throw std::runtime_error("ResourceMangager::load() - Failed to load object");
        insert_resource(id, std::move(r));
    }
    Resource& get(Identifier id)
    {
        auto found = resources.find(id);
        assert(found != resources.end());
        return *found->second[0];
    }
    bool check(Identifier id) {
        return resources.find(id) != resources.end();
    }
    const Resource& get(Identifier id) const
    {
        auto found = resources.find(id);
        assert(found != resources.end());
        return *found->second[0];
    }

protected:
    void insert_resource(Identifier id, std::unique_ptr<Resource> resource)
    {
        resources[id].emplace_back(std::move(resource));
    }
    std::map<Identifier, std::vector<std::unique_ptr<Resource>>> resources;
};

#endif //DOODLEJUMP_RESOURCEMANAGER_H
