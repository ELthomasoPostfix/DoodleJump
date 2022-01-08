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


// TODO  This code was found somewhere on the internet. I do not know from where.
// TODO  The loadFromFile() method in the load methods is perhaps not general??
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
