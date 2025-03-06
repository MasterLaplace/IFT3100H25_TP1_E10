/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include "../primitive/Primitive.hpp"
#include "Exporting.hpp"
#include "Importing.hpp"
#include <ofSingleton.hpp>

namespace plugin::image {

class ResourceManager : public of::utils::Singleton<ResourceManager> {
    friend class of::utils::Singleton<ResourceManager>;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    [[nodiscard]] bool addImage(const std::shared_ptr<Image> &image, const std::string &name);
    void removeImage(const std::string &name);
    [[nodiscard]] bool addModel(const std::shared_ptr<primitive::ObjModel> &model, const std::string &name);
    void removeModels(const std::string &name);
    [[nodiscard]] bool addPrefab(const std::shared_ptr<plugin::primitive::Primitive> &prefab, const std::string &name);
    void removePrefab(const std::string &name);

    void renameImage(const std::string &oldName, const std::string &newName);
    void renameModel(const std::string &oldName, const std::string &newName);
    void renamePrefab(const std::string &oldName, const std::string &newName);

    [[nodiscard]] std::optional<std::shared_ptr<Image>> getImage(const std::string &name);
    [[nodiscard]] std::optional<std::shared_ptr<primitive::ObjModel>> getModel(const std::string &name);
    [[nodiscard]] std::optional<std::shared_ptr<plugin::primitive::Primitive>> getPrefab(const std::string &name);

    [[nodiscard]] std::map<std::string, std::shared_ptr<Image>> getImages();
    [[nodiscard]] std::map<std::string, std::shared_ptr<primitive::ObjModel>> getModels();
    [[nodiscard]] std::map<std::string, std::shared_ptr<plugin::primitive::Primitive>> getPrefabs();

protected:
private:
    std::map<std::string, std::shared_ptr<Image>> _images;
    std::map<std::string, std::shared_ptr<primitive::ObjModel>> _models;
    std::map<std::string, std::shared_ptr<plugin::primitive::Primitive>> _prefabs;
};

} // namespace plugin::image

#endif /* !RESOURCEMANAGER_HPP_ */
