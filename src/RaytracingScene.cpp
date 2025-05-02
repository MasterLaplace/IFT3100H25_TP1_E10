#include "RaytracingScene.hpp"
#include <thread>

void RaytracingScene::setup(const raytracing::Raytracing::CreateInfo &params,
                            const std::vector<std::shared_ptr<primitive::Primitive>> &primitives)
{
    _scene = primitives;

    if (!_raytracer)
        _raytracer = std::make_unique<raytracing::Raytracing>(params, _scene);
    else if (!_raytracer->is_rendering())
    {
        _raytracer = std::make_unique<raytracing::Raytracing>(params, _scene);
    }
}

void RaytracingScene::draw()
{
    ofBackground(40);

    if (!_raytracer->is_rendering() && !_image.isAllocated())
    {
        _image = _raytracer->getImage();
    }

    if (_image.isAllocated())
    {
        _image.draw(0, 0);
    }

    drawGui();
}

void RaytracingScene::drawGui()
{
    ImGui::Begin("Raytracing Controls");

    // Section: Actions
    ImGui::Text("Actions");
    if (ImGui::Button("Generate Image"))
    {
        if (!_raytracer->is_rendering())
        {
            _image.clear();

            _raytracer->generate_image_async(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }
    if (_raytracer->is_rendering())
    {
        ImGui::Text("Status: Rendering...");
    }
    else
    {
        ImGui::Text("Status: Rendering finished.");
    }
    ImGui::Separator();

    // Section: Image Information
    ImGui::Text("Image Information");
    ImGui::Text("Size: %f x %f", _image.getWidth(), _image.getHeight());
    ImGui::Text("Number of primitives: %zu", _scene.size());
    ImGui::Separator();

    // Section: Scene Parameters
    ImGui::Text("Scene Parameters");
    if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        glm::vec3 position = glm::vec3(_position);
        if (ImGui::DragFloat3("Position", &position.x, 0.1f))
        {
            _position = glm::dvec3(position);
        }

        glm::vec3 direction = glm::vec3(_direction);
        if (ImGui::DragFloat3("Direction", &direction.x, 0.1f))
        {
            _direction = glm::dvec3(direction);
        }

        float fov = static_cast<float>(_fov);
        if (ImGui::DragFloat("Field of View", &fov, 0.1f, 1.0f, 180.0f))
        {
            _fov = static_cast<double>(fov);
        }
    }

    if (ImGui::CollapsingHeader("Rendering Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        glm::vec3 background_color = glm::vec3(_background_color);
        if (ImGui::ColorEdit3("Background Color", &background_color.x))
        {
            _background_color = glm::dvec3(background_color);
        }

        ImGui::DragInt("Depth", reinterpret_cast<int *>(&_depth), 1, 1, 10);
        ImGui::SliderInt("Width", reinterpret_cast<int *>(&_width), 1, 4096, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderInt("Height", reinterpret_cast<int *>(&_height), 1, 4096, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderInt("Rays per Pixel", reinterpret_cast<int *>(&_ray_per_pixel), 1, 1024, "%d",
                         ImGuiSliderFlags_Logarithmic);
    }

    ImGui::End();
}
