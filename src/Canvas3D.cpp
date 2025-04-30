#include "Canvas3D.hpp"

// Constructeur
Canvas3D::Canvas3D()
{
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    if (!tesShader.loadTessellation("tessellation_control_410.glsl", "tessellation_evaluation_410.glsl"))
        std::cerr << "Erreur dans le chargement du shader de None." << std::endl;
}

// Redefinition de la methode draw pour prendre en consideration la lumiere.
void Canvas3D::draw()
{
    ofBackground(backgroundColor);

    // On active l'eclairage dynamique.
    ofEnableLighting();

    // Le shader de tessellation.
    tesShader.begin();

    // On active le shader de lumiere.
    light.begin();

    // On dessine toutes les primitives.
    for (size_t i = 0; i < nodes.size(); i++)
    { 
            // On set la couleur ambiante du materiau.
            glm::vec3 materialAmbientColor = getMaterialAmbientColor(i);
            light.setMaterialAmbientColor(materialAmbientColor);

            // On set la couleur diffuse du materiau.
            glm::vec3 materialDiffuseColor = getMaterialDiffuseColor(i);
            light.setMaterialDiffuseColor(materialDiffuseColor);

            // On set la couleur speculaire du materiau.
            glm::vec3 materialSpecularColor = getMaterialSpecularColor(i);
            light.setMaterialSpecularColor(materialSpecularColor);

            // On set la brillance du materiau.
            float materialShininess = getMaterialShininess(i);
            light.setShininess(materialShininess);

            // On dessine la primitive.
            nodes[i]->draw(); 
    }

    // On desactive le shader de tessellation
    tesShader.end();

    // On desactive le shader.
    light.end();
  

    // On desactive l'eclairage dynamique.
    ofDisableLighting();
}

glm::vec3 Canvas3D::getMaterialAmbientColor(int i)
{
    ofColor c = nodes[i]->getPrimitive()->param.ambientColor;
    float r = static_cast<float>(c.r) / 255.0f;
    float g = static_cast<float>(c.g) / 255.0f;
    float b = static_cast<float>(c.b) / 255.0f;
    return glm::vec3{r, g, b};
}

glm::vec3 Canvas3D::getMaterialDiffuseColor(int i)
{
    ofColor c = nodes[i]->getPrimitive()->param.diffuseColor;
    float r = static_cast<float>(c.r) / 255.0f;
    float g = static_cast<float>(c.g) / 255.0f;
    float b = static_cast<float>(c.b) / 255.0f;
    return glm::vec3{r, g, b};
}

glm::vec3 Canvas3D::getMaterialSpecularColor(int i)
{
    ofColor c = nodes[i]->getPrimitive()->param.specularColor;
    float r = static_cast<float>(c.r) / 255.0f;
    float g = static_cast<float>(c.g) / 255.0f;
    float b = static_cast<float>(c.b) / 255.0f;
    return glm::vec3{r, g, b};
}

float Canvas3D::getMaterialShininess(int i) { return nodes[i]->getPrimitive()->param.shininess; }
