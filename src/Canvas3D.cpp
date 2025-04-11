#include "Canvas3D.hpp"

// Constructeur
Canvas3D::Canvas3D()
{
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    if (!tesShader.loadTessellation("tessellation_control_410.glsl", "tessellation_evaluation_410.glsl"))
        std::cerr << "Erreur dans le chargement du shader de None." << std::endl;
}

// Getter
plugin::light::LightModel::Type Canvas3D::getLightModel(int i) { return lights[i]->getLightModel(); }

plugin::light::Light::lightType Canvas3D::getLightType(int i) { return lights[i]->getLightType(); }

glm::vec3 Canvas3D::getLightDirection(int i) { return lights[i]->getLightDirection(); }

glm::vec3 Canvas3D::getLightPosition(int i) { return lights[i]->getLightPosition(); }

glm::vec3 Canvas3D::getLightColor(int i) { return lights[i]->getLightColor(); }

glm::vec3& Canvas3D::getAmbientColor(int i) { return lights[i]->getAmbientColor(); }

glm::vec3 Canvas3D::getDiffuseColor(int i) { return lights[i]->getDiffuseColor(); }

glm::vec3 Canvas3D::getSpecularColor(int i) {return lights[i]->getSpecularColor(); }

float Canvas3D::getShininess(int i) { return lights[i]->getShininess(); }

float Canvas3D::getLightAngle(int i) { return lights[i]->getCutOffAngle(); }

float Canvas3D::getLightIntensity(int i) { return lights[i]->getIntensity(); }

// Setter
void Canvas3D::setLightModel(plugin::light::LightModel::Type model, int i)
{
    plugin::light::Light *l = lights[i];
    l->setLightModel(model);

    if (l->getLightModel() == plugin::light::LightModel::Type::None)
    {
        l->close();
        ofDisableLighting();
    }
    else
    {
        ofEnableLighting();
        l->apply();
    }
}

void Canvas3D::setLightType(plugin::light::Light::lightType lightType, int i) { lights[i]->setLightType(lightType); }

void Canvas3D::setLightPosition(const glm::vec3 &position, int i) { lights[i]->setLightPosition(position); }

void Canvas3D::setLightDirection(const glm::vec3 &lightDirection, int i)
{
    lights[i]->setLightDirection(lightDirection);
}

void Canvas3D::setLightColor(const glm::vec3 &lightColor, int i) { lights[i]->setLightColor(lightColor); }

void Canvas3D::setAmbientColor(const glm::vec3 &color, int i) { lights[i]->setAmbientColor(color); }

void Canvas3D::setDiffuseColor(const glm::vec3 &color, int i) { lights[i]->setDiffuseColor(color); }

void Canvas3D::setSpecularColor(const glm::vec3 &color, int i) { lights[i]->setSpecularColor(color); }

void Canvas3D::setShininess(float shininess, int i) { lights[i]->setShininess(shininess); }

void Canvas3D::setLightAngle(float angle, int i) { lights[i]->setLightAngle(angle); }

void Canvas3D::setLightIntensity(float intensity, int i) { lights[i]->setLightIntensity(intensity); }

void Canvas3D::addLight(plugin::light::Light::lightType type, plugin::light::LightModel::Type model) 
{ 
    plugin::light::Light *l = new plugin::light::Light(type, model); 
    lights.push_back(l);
    lights.back()->id = lights.size() - 1;
}

void Canvas3D::deleteLight(int i) 
{ 
    delete lights[i];

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->id = i;
    }
}

// Redefinition de la methode draw pour prendre en consideration la lumiere.
void Canvas3D::draw()
{
    ofBackground(backgroundColor);

    // On active l'eclairage dynamique.
    ofEnableLighting();

    // On active toutes les lumieres et leurs shaders. 
    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->apply();
    }

    // Le shader de tessellation.
    tesShader.begin();

    // On dessine toutes les primitives.
    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }

    // On desactive le shader de tessellation
    tesShader.end();

    // On desactive toutes les lumieres et leurs shaders.
    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->close();
    }

    // On desactive l'eclairage dynamique.
    ofDisableLighting();
}

plugin::light::Light *Canvas3D::getLight(int id)
{ 
    plugin::light::Light *l = nullptr;
    
    for (int i = 0; i < lights.size(); i++)
    {
        if (lights[i]->id == id)
        {
            l = lights[i];
            break;
        }
    }

    return l;
}

int Canvas3D::getLightId(int i) 
{
    return lights[i]->id; 
}
