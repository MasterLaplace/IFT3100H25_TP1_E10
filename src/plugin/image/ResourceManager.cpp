#include "ResourceManager.hpp"

namespace plugin::image {

bool ResourceManager::addImage(const std::shared_ptr<Image> &image, const std::string &name)
{
    if (_images.find(name) != _images.end())
        return false;

    _images[name] = image;
    return true;
}

void ResourceManager::removeImage(const std::string &name) { _images.erase(name); }

bool ResourceManager::addModel(const std::shared_ptr<primitive::ObjModel> &model, const std::string &name)
{
    if (_models.find(name) != _models.end())
        return false;

    _models[name] = model;
    return true;
}

void ResourceManager::removeModels(const std::string &name) { _models.erase(name); }

bool ResourceManager::addPrefab(const std::shared_ptr<primitive::Primitive> &prefab, const std::string &name)
{
    if (_prefabs.find(name) != _prefabs.end())
        return false;

    _prefabs[std::string("Prefab_") + name] = prefab;
    return true;
}

void ResourceManager::removePrefab(const std::string &name) { _prefabs.erase(name); }

bool ResourceManager::addCubeMap(const std::shared_ptr<std::array<ofTexture, 6>> &cubmap, const std::string &name)
{
    if (_cubeMaps.find(name) != _cubeMaps.end())
        return false;

    _cubeMaps[name] = cubmap;
    return true;
}

void ResourceManager::removeCubeMap(const std::string &name) { _cubeMaps.erase(name); }

void ResourceManager::renameImage(const std::string &oldName, const std::string &newName)
{
    if (_images.find(oldName) != _images.end())
    {
        _images[newName] = _images[oldName];
        _images.erase(oldName);
    }
}

void ResourceManager::renameModel(const std::string &oldName, const std::string &newName)
{
    if (_models.find(oldName) != _models.end())
    {
        _models[newName] = _models[oldName];
        _models.erase(oldName);
    }
}

void ResourceManager::renamePrefab(const std::string &oldName, const std::string &newName)
{
    if (_prefabs.find(oldName) != _prefabs.end())
    {
        _prefabs[newName] = _prefabs[oldName];
        _prefabs.erase(oldName);
    }
}

void ResourceManager::renameCubeMap(const std::string &oldName, const std::string &newName)
{
    if (_cubeMaps.find(oldName) != _cubeMaps.end())
    {
        _cubeMaps[newName] = _cubeMaps[oldName];
        _cubeMaps.erase(oldName);
    }
}

std::optional<std::shared_ptr<Image>> ResourceManager::getImage(const std::string &name)
{
    if (_images.find(name) != _images.end())
        return _images[name];
    return std::nullopt;
}

std::optional<std::shared_ptr<primitive::ObjModel>> ResourceManager::getModel(const std::string &name)
{
    if (_models.find(name) != _models.end())
        return _models[name];
    return std::nullopt;
}

std::optional<std::shared_ptr<primitive::Primitive>> ResourceManager::getPrefab(const std::string &name)
{
    if (_prefabs.find(name) != _prefabs.end())
        return _prefabs[name];
    return std::nullopt;
}

std::optional<std::shared_ptr<std::array<ofTexture, 6>>> ResourceManager::getCubeMap(const std::string &name)
{
    if (_cubeMaps.find(name) != _cubeMaps.end())
        return _cubeMaps[name];
    return std::nullopt;
}

std::map<std::string, std::shared_ptr<Image>> ResourceManager::getImages() { return _images; }
std::map<std::string, std::shared_ptr<primitive::ObjModel>> ResourceManager::getModels() { return _models; }
std::map<std::string, std::shared_ptr<primitive::Primitive>> ResourceManager::getPrefabs() { return _prefabs; }
std::map<std::string, std::shared_ptr<std::array<ofTexture, 6>>> ResourceManager::getCubeMaps() { return _cubeMaps; }

} // namespace plugin::image
