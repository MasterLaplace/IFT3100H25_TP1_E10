#include "AppGui.hpp"
#include "Controller.hpp"

void AppGui::setup(Controller *_controller)
{
    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    selectedTool = tool::POINT;
    gui.setup();                                 // On initialise le gui.
    plugin::image::ResourceManager::construct(); // On initialise le gestionnaire de ressources.
}

void AppGui::draw()
{
    gui.begin();
    drawMenuBar();

    if (controller->is3d)
        drawToolsPanel3D(), drawDynamicPanel3D();
    else
        drawToolsPanel2D(), drawDynamicPanel2D();

    drawProprietiesPanel();
    drawSceneGraph();
    gui.end();
}

// Sert a dessiner le menu de la barre de menu
void AppGui::drawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Importer image"))
            {
                controller->importImage();
            }

            if (ImGui::MenuItem("Importer model"))
            {
                controller->importModel();
            }

            if (ImGui::MenuItem("Importer cubemap"))
            {
                controller->importCubemap();
            }

            if (ImGui::MenuItem("Exporter image"))
            {
                controller->exportImage();
            }

            if (ImGui::MenuItem("Quitter"))
            {
                ofExit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Vues"))
        {
            string view = controller->is3d ? "Aller 2D" : "Aller 3D";

            if (ImGui::MenuItem(view.c_str()))
            {
                controller->onToolSelected(tool::SELECT);
                controller->toggleCanvas();
            }

            if (controller->is3d)
            {
                string isOrthographic = controller->isCameraOrthographic() ? "Vers Perspective" : "Vers Orthographique";
                if (ImGui::MenuItem(isOrthographic.c_str()))
                {
                    controller->toggleCameraProjection();
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Histogram"))
        {
            if (ImGui::MenuItem("Rouge"))
            {
                controller->drawHistogram(0);
            }

            if (ImGui::MenuItem("Vert"))
            {
                controller->drawHistogram(1);
            }

            if (ImGui::MenuItem("Bleu"))
            {
                controller->drawHistogram(2);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Courbe / Surface"))
        {
            if (ImGui::MenuItem("Bezier"))
            {
                controller->drawCurve(plugin::states::BEZIER);
            }

            if (ImGui::MenuItem("Catmull-Rom"))
            {
                controller->drawCurve(plugin::states::CATMULL_ROM);
            }

            if (ImGui::MenuItem("Coons"))
            {
                controller->drawCurve(plugin::states::COONS);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

// Sert a dessiner le panel des outils de dessin
void AppGui::drawToolsPanel2D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Outils de dessin");

    // bool buttonClicked = false;

    if (ImGui::Button("Selection"))
    {
        onToolSelected(tool::SELECT);
    }

    if (ImGui::Button("Arriere plan"))
    {
        onToolSelected(tool::BACKGROUND);
    }

    // Si le bouton "Point" est activé.
    if (ImGui::Button("Point"))
    {
        onToolSelected(tool::POINT);
    }

    // Même chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        onToolSelected(tool::LINE);
    }

    // Si le bouton "Rectangle" est activé.
    if (ImGui::Button("Rectangle"))
    {
        onToolSelected(tool::RECTANGLE);
    }

    if (ImGui::Button("Ellipse"))
    {
        onToolSelected(tool::ELLIPSE);
    }

    if (ImGui::Button("Polygone"))
    {
        onToolSelected(tool::POLYGON);
    }

    ImGui::End();
}

void AppGui::drawToolsPanel3D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Outils de dessin");

    ImGui::Columns(2, nullptr, false);

    if (ImGui::Button("Selection"))
    {
        onToolSelected(tool::SELECT);
    }

    if (ImGui::Button("Arriere plan"))
    {
        onToolSelected(tool::BACKGROUND);
    }

    if (ImGui::Button("Box"))
    {
        onToolSelected(tool::BOX);
    }

    if (ImGui::Button("Ellipsoid"))
    {
        onToolSelected(tool::ELLIPSOID);
    }

    ImGui::NextColumn();

    if (ImGui::Button("Lumiere"))
    {
        onToolSelected(tool::LIGHT);
    }

    ImGui::End();
}

// Sert a dessiner le panel dynamique
void AppGui::drawDynamicPanel2D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth + panelWidth + 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Option de dessin");
    bool propertiesChanged = false;

    switch (selectedTool)
    {
    case AppGui::SELECT: ImGui::Text("Selection");

    case AppGui::POINT:
        ImGui::Text("Option pour le point");

        // Si on change la taille du point.
        if (ImGui::SliderFloat("Taille", &outlineWidth, 1.0f, 30.0f))
        {
            propertiesChanged = true;
        }

        // Si on change la couleur du point.
        if (ImGui::ColorEdit3("Couleur", (float *) &fillColor))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::LINE:
        ImGui::Text("Option de ligne");

        // Si on change la taille de la ligne.
        if (ImGui::SliderFloat("Epaisseur", &outlineWidth, 1.0f, 30.0f))
        {
            propertiesChanged = true;
        }

        // Si on change la couleur de la ligne.
        if (ImGui::ColorEdit3("Couleur", &fillColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::RECTANGLE:
        ImGui::Text("Option de rectangle");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::ELLIPSE:
        ImGui::Text("Option de ellipse");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;
    case AppGui::POLYGON:
        ImGui::Text("Option de polygone");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::BACKGROUND:
        ImGui::Text("Option de fond");

        if (ImGui::ColorEdit3("Couleur de fond", (float *) &backgroundColor))
        {
            controller->onBackgroundColorChanged(
                ofColor(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255));
        }
        break;

    default: break;
    }

    if (propertiesChanged)
    {
        PrimitiveParams params;
        params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        params.ambientColor = ofColor(ambientColor[0] * 255, ambientColor[1] * 255, ambientColor[2] * 255);
        params.diffuseColor = ofColor(diffuseColor[0] * 255, diffuseColor[1] * 255, diffuseColor[3] * 255);
        params.specularColor = ofColor(specularColor[0] * 255, specularColor[1] * 255, specularColor[3] * 255);
        params.shininess = shininess;
        params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
        params.outlineWidth = outlineWidth;
        params.isFilled = isFilled;

        controller->onPrimitivePropertiesChanged(params);
    }

    ImGui::End();
}

void AppGui::drawDynamicPanel3D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth + panelWidth + 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Option de dessin");
    bool propertiesChanged = false;

    switch (selectedTool)
    {
    case AppGui::SELECT: ImGui::Text("Selection"); break;

    case AppGui::BOX:
        ImGui::Text("Option de box");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur ambiente", &ambientColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur diffuse", &diffuseColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur speculaire", &specularColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::DragFloat("Brillance", &shininess))
        {
            propertiesChanged = true;
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::ELLIPSOID:
        ImGui::Text("Option de ellipsoid");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur ambiente", &ambientColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur diffuse", &diffuseColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur speculaire", &specularColor[0]))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::DragFloat("Brillance", &shininess))
        {
            propertiesChanged = true;
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case AppGui::BACKGROUND:
        ImGui::Text("Option de fond");

        if (ImGui::ColorEdit3("Couleur de fond", (float *) &backgroundColor))
        {
            controller->onBackgroundColorChanged(
                ofColor(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255));
        }
        break;

    case AppGui::LIGHT:
        ImGui::Text("Option de lumiere");

        // Pour permettre de conserver les changements de selection du modele d'eclairage.
        const char *lightningTypes[] = {"Aucun", "Ambient", "Point", "Directional", "Spotlight"};
        static int currentLightningType = 0;
        plugin::light::Light::lightType type = plugin::light::Light::lightType::NONE;

        const char *lightningModels[] = {"Aucun", "Lambert", "Phong", "Blinn-Phong"};
        static int currentLightningModel = 0;
        plugin::light::LightModel::Type model = plugin::light::LightModel::Type::None;

        ImGui::Text("Type de lumiere :");
        if (ImGui::BeginCombo("Type", lightningTypes[currentLightningType]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(lightningTypes); n++)
            {
                bool isSelected = (currentLightningType == n);
                if (ImGui::Selectable(lightningTypes[n], isSelected))
                {
                    currentLightningType = n;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (currentLightningType == 1)
        {
            ImGui::Text("Modele d'eclairage :");
            if (ImGui::BeginCombo("Modele", lightningModels[currentLightningModel]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(lightningModels) - 2; n++)
                {
                    bool isSelected = (currentLightningModel == n);
                    if (ImGui::Selectable(lightningModels[n], isSelected))
                    {
                        currentLightningModel = n;
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }

        else if (currentLightningType != 0 && currentLightningType != 1)
        {
            ImGui::Text("Modele d'eclairage :");
            if (ImGui::BeginCombo("Modele", lightningModels[currentLightningModel]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(lightningModels); n++)
                {
                    bool isSelected = (currentLightningModel == n);
                    if (ImGui::Selectable(lightningModels[n], isSelected))
                    {
                        currentLightningModel = n;
                    }
                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }

        switch (currentLightningType)
        {
        case 0: type = plugin::light::Light::lightType::NONE; break;
        case 1: type = plugin::light::Light::lightType::AMBIENT; break;
        case 2: type = plugin::light::Light::lightType::POINT_LIGHT; break;
        case 3: type = plugin::light::Light::lightType::DIRECTIONAL; break;
        case 4: type = plugin::light::Light::lightType::SPOT; break;
        }

        switch (currentLightningModel)
        {
        case 0: model = plugin::light::LightModel::Type::None; break;
        case 1: model = plugin::light::LightModel::Type::Lambert; break;
        case 2: model = plugin::light::LightModel::Type::Phong; break;
        case 3: model = plugin::light::LightModel::Type::BlinnPhong; break;
        }

        if (currentLightningType != 0)
        {
            ImGui::SetNextItemWidth(180);
            if (ImGui::Button("Creer", ImVec2(180, 40)))
            {
                controller->addLight(type, model);
            }
        }

        // S'il n'y a aucun eclairage selectionne, on n'affiche pas les options.
        if (currentLightningModel == 0)
            break;

        // Pour permettre de conserver les changements de position de la lumiere.
        // float *lightPosition = controller->getLightPosition();

        ImGui::Text("Position de la lumiere :");
        // if (ImGui::SliderFloat3("Position", lightPosition, -100.0f, 100.0f))
        {
            // controller->setLightPosition(lightPosition);
            // propertiesChanged = true;
        }

        // Pour permettre de conserver les changements de couleur de la lumiere ambiante.
        // float *ambientColor = controller->getAmbientColor();

        ImGui::Text("Couleur ambiante :");
        // if (ImGui::ColorEdit3("Ambiante", ambientColor))
        {
            // controller->setAmbientColor(ambientColor);
            // propertiesChanged = true;
        }

        // Pour permettre de conserver les changements de couleur de la lumiere diffuse.
        // float *diffuseColor = controller->getDiffuseColor();
        ImGui::Text("Couleur diffuse :");
        // if (ImGui::ColorEdit3("Diffuse", diffuseColor))
        {
            // controller->setDiffuseColor(diffuseColor);
            // propertiesChanged = true;
        }

        // On affiche uniquement si le modele d'eclairage est Phong ou Blinn-Phong.
        if (currentLightningModel == 2 || currentLightningModel == 3)
        {
            // Pour permettre de conserver les changements de couleur de la lumiere speculaire.
            // float *specularColor = controller->getSpecularColor();

            ImGui::Text("Couleur speculaire :");
            // if (ImGui::ColorEdit3("Speculaire", specularColor))
            {
                //   controller->setSpecularColor(specularColor);
                // propertiesChanged = true;
            }

            // Pour permettre de conserver les changements de brillance.
            // float shininess = controller->getShininess();

            ImGui::Text("Brillance :");
            // if (ImGui::SliderFloat("Brillance", &shininess, 0.0f, 128.0f))
            {
                //    controller->setShininess(shininess);
                // propertiesChanged = true;
            }
        }
        break;
    }

    if (propertiesChanged)
    {
        PrimitiveParams params;
        params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        params.ambientColor = ofColor(ambientColor[0] * 255, ambientColor[1] * 255, ambientColor[2] * 255);
        params.diffuseColor = ofColor(diffuseColor[0] * 255, diffuseColor[1] * 255, diffuseColor[2] * 255);
        params.specularColor = ofColor(specularColor[0] * 255, specularColor[1] * 255, specularColor[2] * 255);
        params.shininess = shininess;
        params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
        params.outlineWidth = outlineWidth;
        params.isFilled = isFilled;

        controller->onPrimitivePropertiesChanged(params);
    }

    ImGui::End();
}

// Sert a dessiner le graphe de scene
void AppGui::drawSceneGraph()
{
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Graphe de scene");

    ImGui::Text("Primitives :");
    ImGui::Separator();

    for (auto &node : controller->getCanvasNodes())
    {
        displayNode(node, 0);
    }

    ImGui::Text("Lumieres :");
    ImGui::Separator();
    ImGui::Indent(10.0f);
    for (int i = 0; i < controller->getLights().size(); i++)
    {
        std::string label = "Lumiere " + std::to_string(i) + "##L" + std::to_string(i);
        bool selected = (i == controller->getSelectedLightId());
        if (ImGui::Selectable(label.c_str(), selected))
        {
            controller->onLightSelected(i);
        }
    }
    ImGui::Unindent();

    ImGui::Separator();
    ImGui::Text("Images Importe :");

    for (auto &node : plugin::image::ResourceManager::instance()->getImages())
    {
        if (ImGui::Selectable(node.first.c_str()))
        {
            controller->onImageSelected(node.first);
        }
    }

    ImGui::Separator();
    ImGui::Text("Models Importe :");

    for (auto &node : plugin::image::ResourceManager::instance()->getModels())
    {
        if (ImGui::Selectable(node.first.c_str()))
        {
            controller->onModelSelected(node.first);
        }
    }

    ImGui::Separator();
    ImGui::Text("Cubemaps Importe :");

    for (auto &node : plugin::image::ResourceManager::instance()->getCubeMaps())
    {
        if (ImGui::Selectable(node.first.c_str()))
        {
            controller->onCubeMapSelected(node.first);
        }
    }

    ImGui::Separator();
    ImGui::Text("Prefabs Importe :");

    for (auto &node : plugin::image::ResourceManager::instance()->getPrefabs())
    {
        if (ImGui::Selectable(node.first.c_str()))
        {
            controller->onPrefabSelected(node.first);
        }
    }

    if (ImGui::Button("deselectionner"))
    {
        controller->onPrimitiveSelected(-1);
    }

    ImGui::End();
}

// Sert a afficher les noeuds du graphe de scene
void AppGui::displayNode(NodePrimitive *node, uint32_t indentLevel)
{
    ImGui::Indent(indentLevel * 10.0f);
    std::string nodeLabel = node->getName();
    int selectedNodeId = controller->getSelectedNodeId();
    if (ImGui::Selectable(nodeLabel.c_str(), selectedNodeId == static_cast<int>(node->getId())))
    {
        controller->onPrimitiveSelected(node->getId());
    }

    for (auto &child : node->getChildren())
    {
        displayNode(child, indentLevel + 1);
    }
    ImGui::Unindent(indentLevel * 10.0f);
}

// Sert a dessiner le panel des proprietes
void AppGui::drawProprietiesPanel()
{
    // Les settings de la fenetre
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(ofGetWidth() - panelWidth - 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Propriétés");

    ImGui::Text("Propriétés :");
    ImGui::Separator();

    // On va chercher la node selectionnee.
    int selectedNodeId = controller->getSelectedNodeId();

    NodePrimitive *node = controller->getNodeById(selectedNodeId);
    std::string &imageName = controller->getSelectedImageName();
    std::string &modelName = controller->getSelectedModelName();
    std::string &prefabName = controller->getSelectedPrefabName();
    int selectedLight = controller->getSelectedLight();

    // On s'occupe des proprietes generiques en premier.

    // Si la node selectionnee est valide on affiche les proprietes de base des Primitives2D.
    if (node != nullptr)
    {
        ImGui::Text("%s", node->getName().c_str());
        ImGui::Separator();
        const auto &primitive = (node != nullptr) ? node->getPrimitive() :
                                                    *plugin::image::ResourceManager::instance()->getPrefab(prefabName);

        if (dynamic_cast<Point2D *>(primitive.get()) != nullptr)
        {
            drawPointProperties(std::dynamic_pointer_cast<Point2D>(primitive));
        }
        else if (dynamic_cast<Line2D *>(primitive.get()) != nullptr)
        {
            drawLineProperties(std::dynamic_pointer_cast<Line2D>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Rectangle *>(primitive.get()) != nullptr)
        {
            drawRectangleProperties(std::dynamic_pointer_cast<plugin::primitive::Rectangle>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Ellipse *>(primitive.get()) != nullptr)
        {
            drawEllipseProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipse>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Polygon *>(primitive.get()) != nullptr)
        {
            drawPolygonProperties(std::dynamic_pointer_cast<plugin::primitive::Polygon>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Box *>(primitive.get()) != nullptr)
        {
            drawBoxProperties(std::dynamic_pointer_cast<plugin::primitive::Box>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Ellipsoid *>(primitive.get()) != nullptr)
        {
            drawEllipsoidProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipsoid>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::ObjModel *>(primitive.get()) != nullptr)
        {
            drawObjModelProperties(std::dynamic_pointer_cast<plugin::primitive::ObjModel>(primitive));
        }

        if (ImGui::Button("Creer Prefab", ImVec2((ofGetWidth() / 6) - 20, 50)))
        {
            controller->createPrefabButtonPressed(primitive, node->getName());
        }

        // Pour supprimer une primitive.
        if (ImGui::Button("Supprimer", ImVec2(panelWidth - 20, 50)))
        {
            controller->deletePrimitiveButtonPressed(selectedNodeId);
        }
    }
    else if (selectedLight != -1)
    {
        drawLightProperties(selectedLight);
    }

    else if (!prefabName.empty())
    {
        auto prefab = plugin::image::ResourceManager::instance()->getPrefab(prefabName);
        if (prefab.has_value())
        {
            drawPrefabProperties(*prefab, prefabName);
        }
    }
    else if (!imageName.empty())
    {
        auto image = plugin::image::ResourceManager::instance()->getImage(imageName);
        if (image.has_value())
        {
            drawImageProperties(*image, imageName);
        }
    }
    else if (!modelName.empty())
    {
        auto model = plugin::image::ResourceManager::instance()->getModel(modelName);
        if (model.has_value())
        {
            drawModelProperties(*model, modelName);
        }
    }

    ImGui::End();
}

void AppGui::onToolSelected(tool tool)
{
    selectedTool = tool;
    controller->onToolSelected(tool);

    PrimitiveParams params;
    params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
    params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    controller->onPrimitivePropertiesChanged(params);
}

void AppGui::drawPointProperties(const std::shared_ptr<Point2D> &point)
{
    drawTransformProperties2D(point); // On dessine les proprietes de transformation generales.

    float size = point->size;
    float color[3] = {point->param.fillColor.r / 255.0f, point->param.fillColor.g / 255.0f,
                      point->param.fillColor.b / 255.0f};

    ImGui::Text("Taille :");
    if (ImGui::SliderFloat("Taille", &size, 1.0f, 30.0f))
    {
        point->size = size;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        point->param.fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
    }
}

void AppGui::drawImageProperties(const std::shared_ptr<plugin::image::Image> &image, const std::string &imageName)
{
    char newImageName[128];
    strncpy(newImageName, imageName.c_str(), sizeof(imageName));
    newImageName[sizeof(imageName) - 1] = '\0';

    ImGui::Text("Nom :");
    if (ImGui::InputText("Nom", newImageName, sizeof(imageName)))
    {
        plugin::image::ResourceManager::instance()->renameImage(imageName, newImageName);
    }

    // On dessine les sliders pour l'exposition et le gamma.
    static float exposure = 1.0f;
    static float gamma = 2.2f;

    ImGui::Text("Exposition :");
    if (ImGui::SliderFloat("Exposition", &exposure, 0.1f, 10.0f))
    {
        controller->setImageExposure(imageName, exposure);
    }

    ImGui::Text("Gamma :");
    if (ImGui::SliderFloat("Gamma", &gamma, 0.1f, 5.0f))
    {
        controller->setImageGamma(imageName, gamma);
    }

    // On dessine le menu pour le mappage tonal.
    static int currentToneMapping = 0;

    ImGui::Text("Mappage tonal :");
    const char *toneMappingNames[] = {"Aucun", "Reinhard", "Filmic"};
    if (ImGui::BeginCombo("Mappage tonal", toneMappingNames[currentToneMapping]))
    {
        for (int n = 0; n < IM_ARRAYSIZE(toneMappingNames); n++)
        {
            bool isSelected = (currentToneMapping == n);
            if (ImGui::Selectable(toneMappingNames[n], isSelected))
            {
                currentToneMapping = n;
                switch (currentToneMapping)
                {
                case 0: controller->setImageToneMapping(imageName, plugin::image::ToneMapping::Type::None); break;
                case 1: controller->setImageToneMapping(imageName, plugin::image::ToneMapping::Type::Reinhard); break;
                case 2: controller->setImageToneMapping(imageName, plugin::image::ToneMapping::Type::Filmic); break;
                }
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    // On dessine le menu pour l'espace de couleur.
    ImGui::Text("Taille : %.2fx%.2f", image->getWidth(), image->getHeight());

    ImGui::Text("Espace de Couleur :");
    if (ImGui::BeginCombo("Espace de Couleur", "RGB"))
    {
        if (ImGui::Selectable("RGB"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::RGB);
        }
        if (ImGui::Selectable("RGBA"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::RGBA);
        }
        if (ImGui::Selectable("Grayscale"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::Grayscale);
        }
        if (ImGui::Selectable("HSB"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::HSB);
        }
        if (ImGui::Selectable("HLS"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::HLS);
        }
        if (ImGui::Selectable("YUV"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::YUV);
        }
        if (ImGui::Selectable("YCoCg"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::YCoCg);
        }
        if (ImGui::Selectable("CoCg_Y"))
        {
            controller->setImageColorSpace(imageName, plugin::image::ColourSpaces::Type::CoCg_Y);
        }
        ImGui::EndCombo();
    }

    // On dessine la preview de l'image.
    ImGui::Text("Prévisualisation :");
#if 0
    ImGui::Image((ImTextureID)(intptr_t)image->getTexture().getTextureData().textureID, ImVec2(image->getWidth(), image->getHeight()));
#else
    ImGui::Text("<-");
    ofSetColor(255);
    float x = (ofGetWidth() - image->getWidth()) / 2;
    float y = (ofGetHeight() - image->getHeight()) / 2;
    image->draw(x, y);
#endif
}

void AppGui::drawModelProperties(const std::shared_ptr<plugin::primitive::ObjModel> &model,
                                 const std::string &modelName)
{
    char newModelName[128];
    strncpy(newModelName, modelName.c_str(), sizeof(modelName));
    newModelName[sizeof(modelName) - 1] = '\0';

    ImGui::Text("Nom :");
    if (ImGui::InputText("Nom", newModelName, sizeof(modelName)))
    {
        plugin::image::ResourceManager::instance()->renameModel(modelName, newModelName);
    }

    ImGui::Text("Vertices : %d", model->getNumVertices());
    ImGui::Text("Faces : %d", model->getNumFaces());

    if (ImGui::Button("Creer", ImVec2((ofGetWidth() / 6) - 20, 50)))
    {
        controller->createModelButtonPressed(modelName);
    }
}

void AppGui::drawPrefabProperties(const std::shared_ptr<plugin::primitive::Primitive> &prefab,
                                  const std::string &prefabName)
{
    char newPrefabName[128];
    strncpy(newPrefabName, prefabName.c_str(), sizeof(prefabName));
    newPrefabName[sizeof(prefabName) - 1] = '\0';

    ImGui::Text("Nom :");
    if (ImGui::InputText("Nom", newPrefabName, sizeof(prefabName)))
    {
        plugin::image::ResourceManager::instance()->renameModel(prefabName, newPrefabName);
    }

    if (dynamic_cast<Point2D *>(prefab.get()) != nullptr)
    {
        drawPointProperties(std::dynamic_pointer_cast<Point2D>(prefab));
    }
    else if (dynamic_cast<Line2D *>(prefab.get()) != nullptr)
    {
        drawLineProperties(std::dynamic_pointer_cast<Line2D>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::Rectangle *>(prefab.get()) != nullptr)
    {
        drawRectangleProperties(std::dynamic_pointer_cast<plugin::primitive::Rectangle>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::Ellipse *>(prefab.get()) != nullptr)
    {
        drawEllipseProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipse>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::Polygon *>(prefab.get()) != nullptr)
    {
        drawPolygonProperties(std::dynamic_pointer_cast<plugin::primitive::Polygon>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::Box *>(prefab.get()) != nullptr)
    {
        drawBoxProperties(std::dynamic_pointer_cast<plugin::primitive::Box>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::Ellipsoid *>(prefab.get()) != nullptr)
    {
        drawEllipsoidProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipsoid>(prefab));
    }
    else if (dynamic_cast<plugin::primitive::ObjModel *>(prefab.get()) != nullptr)
    {
        drawObjModelProperties(std::dynamic_pointer_cast<plugin::primitive::ObjModel>(prefab));
    }
}

void AppGui::setMaterial(Primitive *p, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
    p->param.ambientColor = ofColor(ambient[0] * 255, ambient[1] * 255, ambient[2] * 255);
    p->param.diffuseColor = ofColor(diffuse[0] * 255, diffuse[1] * 255, diffuse[2] * 255);
    p->param.specularColor = ofColor(specular[0] * 255, specular[1] * 255, specular[2] * 255);
    p->param.shininess = shininess;
}

void AppGui::drawLineProperties(const std::shared_ptr<Line2D> &line)
{
    drawTransformProperties2D(line); // On dessine les proprietes de transformation generales.

    float width = line->param.outlineWidth;
    float color[3] = {line->param.fillColor.r / 255.0f, line->param.fillColor.g / 255.0f,
                      line->param.fillColor.b / 255.0f};

    ImGui::Text("Epaisseur :");
    if (ImGui::SliderFloat("Epaisseur", &width, 1.0f, 30.0f))
    {
        line->param.outlineWidth = width;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        line->param.fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
    }

    ImGui::Text("Debut :");
    if (ImGui::DragFloat2("Debut", &line->startPosition.x, 0.1f))
    {
        line->startPosition = line->startPosition;
    }

    ImGui::Text("Fin :");
    if (ImGui::DragFloat2("Fin", &line->endPosition.x, 0.1f))
    {
        line->endPosition = line->endPosition;
    }
}

void AppGui::drawRectangleProperties(const std::shared_ptr<plugin::primitive::Rectangle> &rectangle)
{
    drawTransformProperties2D(rectangle); // On dessine les proprietes de transformation generales.

    float width = rectangle->param.outlineWidth;
    float fillColor[3] = {rectangle->param.fillColor.r / 255.0f, rectangle->param.fillColor.g / 255.0f,
                          rectangle->param.fillColor.b / 255.0f};
    float outlineColor[3] = {rectangle->param.outlineColor.r / 255.0f, rectangle->param.outlineColor.g / 255.0f,
                             rectangle->param.outlineColor.b / 255.0f};
    bool filled = rectangle->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        rectangle->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        rectangle->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        rectangle->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            rectangle->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void AppGui::drawEllipseProperties(const std::shared_ptr<plugin::primitive::Ellipse> &ellipse)
{
    drawTransformProperties2D(ellipse); // On dessine les proprietes de transformation generales.

    float width = ellipse->param.outlineWidth;
    float fillColor[3] = {ellipse->param.fillColor.r / 255.0f, ellipse->param.fillColor.g / 255.0f,
                          ellipse->param.fillColor.b / 255.0f};
    float outlineColor[3] = {ellipse->param.outlineColor.r / 255.0f, ellipse->param.outlineColor.g / 255.0f,
                             ellipse->param.outlineColor.b / 255.0f};
    bool filled = ellipse->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        ellipse->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        ellipse->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        ellipse->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            ellipse->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }

    ImGui::Text("Rayon Horizontal :");
    if (ImGui::DragFloat("Rayon Horizontal", &ellipse->radius.x, 0.1f))
    {
        ellipse->radius.x = ellipse->radius.x;
    }

    ImGui::Text("Rayon Vertical :");
    ImGui::DragFloat("Rayon Vertical", &ellipse->radius.y, 0.1f);
}

void AppGui::drawPolygonProperties(const std::shared_ptr<plugin::primitive::Polygon> &polygon)
{
    drawTransformProperties2D(polygon); // On dessine les proprietes de transformation generales.

    float width = polygon->param.outlineWidth;
    float fillColor[3] = {polygon->param.fillColor.r / 255.0f, polygon->param.fillColor.g / 255.0f,
                          polygon->param.fillColor.b / 255.0f};
    float outlineColor[3] = {polygon->param.outlineColor.r / 255.0f, polygon->param.outlineColor.g / 255.0f,
                             polygon->param.outlineColor.b / 255.0f};
    bool filled = polygon->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        polygon->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        polygon->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        polygon->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            polygon->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void AppGui::drawEllipsoidProperties(const std::shared_ptr<plugin::primitive::Ellipsoid> &ellipsoid)
{
    drawTransformProperties3D(ellipsoid);

    float width = ellipsoid->param.outlineWidth;
    float ambientColor[3] = {ellipsoid->param.ambientColor.r / 255.0f, ellipsoid->param.ambientColor.g / 255.0f,
                             ellipsoid->param.ambientColor.b / 255.0f};
    float diffuseColor[3] = {ellipsoid->param.diffuseColor.r / 255.0f, ellipsoid->param.diffuseColor.g / 255.0f,
                             ellipsoid->param.diffuseColor.b / 255.0f};
    float specularColor[3] = {ellipsoid->param.specularColor.r / 255.0f, ellipsoid->param.specularColor.g / 255.0f,
                              ellipsoid->param.specularColor.b / 255.0f};
    float shininess = ellipsoid->param.shininess;
    float outlineColor[3] = {ellipsoid->param.outlineColor.r / 255.0f, ellipsoid->param.outlineColor.g / 255.0f,
                             ellipsoid->param.outlineColor.b / 255.0f};
    bool filled = ellipsoid->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        ellipsoid->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        ellipsoid->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        ellipsoid->param.isFilled = filled;
    }

    if (filled)
    {
        // La liste des materiaux possibles.
        const char *materialNames[] = {"Personnalise",   "Or", "Argent", "Cuivre", "Chrome", "Plastique rouge",
                                       "Caoutchouc noir"};
        static int currentMaterial = 0;

        // Menu deroulant pour selectionner un materiau.
        ImGui::Text("Materiau :");
        if (ImGui::BeginCombo("Materiau", materialNames[currentMaterial]))
        {
            for (int i = 0; i < IM_ARRAYSIZE(materialNames); i++)
            {
                bool isSelected = (i == currentMaterial);
                if (ImGui::Selectable(materialNames[i], isSelected))
                {
                    currentMaterial = i;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Si c'est un materiaux personnalise.
        if (currentMaterial == 0)
        {
            ImGui::Text("Couleur ambiante :");
            if (ImGui::ColorEdit3("Ambiante", &ambientColor[0]))
            {
                ellipsoid->setAmbientColor({ambientColor[0], ambientColor[1], ambientColor[2]});
                ellipsoid->param.ambientColor =
                    ofColor(ambientColor[0] * 255, ambientColor[1] * 255, ambientColor[2] * 255);
            }

            ImGui::Text("Couleur diffuse :");
            if (ImGui::ColorEdit3("Diffuse", &diffuseColor[0]))
            {
                ellipsoid->setDiffuseColor(glm::vec3{diffuseColor[0], diffuseColor[1], diffuseColor[2]});
                ellipsoid->param.diffuseColor =
                    ofColor(diffuseColor[0] * 255, diffuseColor[1] * 255, diffuseColor[2] * 255);
            }

            ImGui::Text("Couleur speculaire :");
            if (ImGui::ColorEdit3("Speculaire", &specularColor[0]))
            {
                ellipsoid->setSpecularColor(glm::vec3{specularColor[0], specularColor[1], specularColor[2]});
                ellipsoid->param.specularColor =
                    ofColor(specularColor[0] * 255, specularColor[1] * 255, specularColor[2] * 255);
            }

            float shininess = ellipsoid->getShininess();
            if (ImGui::DragFloat("Brillance", &shininess))
            {
                ellipsoid->setShininess(shininess);
                ellipsoid->param.shininess = shininess;
            }
        }

        // Si on selectionne l'or.
        if (currentMaterial == 1)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.247, 0.199, 0.074};
            glm::vec3 diffuseColor{0.247, 0.199, 0.074};
            glm::vec3 specularColor{0.628, 0.555, 0.366};
            float shininess = 51.2f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne l'argent.
        if (currentMaterial == 2)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.192, 0.192, 0.192};
            glm::vec3 diffuseColor{0.507, 0.507, 0.507};
            glm::vec3 specularColor{0.508, 0.508, 0.508};
            float shininess = 51.2f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le cuivre.
        if (currentMaterial == 3)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.229, 0.088, 0.027};
            glm::vec3 diffuseColor{0.550, 0.211, 0.066};
            glm::vec3 specularColor{0.580, 0.223, 0.069};
            float shininess = 51.2f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le chrome.
        if (currentMaterial == 4)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.25, 0.25, 0.25};
            glm::vec3 diffuseColor{0.4, 0.4, 0.4};
            glm::vec3 specularColor{0.774, 0.774, 0.774};
            float shininess = 76.8f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne plastique rouge.
        if (currentMaterial == 5)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.1, 0.0, 0.0};
            glm::vec3 diffuseColor{0.6, 0.0, 0.0};
            glm::vec3 specularColor{0.6, 0.6, 0.6};
            float shininess = 32.0f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le caoutchouc.
        if (currentMaterial == 6)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.02, 0.02, 0.02};
            glm::vec3 diffuseColor{0.01, 0.01, 0.01};
            glm::vec3 specularColor{0.4, 0.4, 0.4};
            float shininess = 10.0f;

            // On set les proprietes dans l'ellipsoid.
            ellipsoid->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes dans l'ellipsoid d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(ellipsoid.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        currentMaterial = 0;
    }

    ImGui::Text("Taille :");
    if (ImGui::DragFloat3("Taille", &ellipsoid->getRadius().x, 0.1f))
        ;
}

void AppGui::drawBoxProperties(const std::shared_ptr<plugin::primitive::Box> &box)
{
    drawTransformProperties3D(box);

    float width = box->param.outlineWidth;
    float fillColor[3] = {box->param.fillColor.r / 255.0f, box->param.fillColor.g / 255.0f,
                          box->param.fillColor.b / 255.0f};
    float outlineColor[3] = {box->param.outlineColor.r / 255.0f, box->param.outlineColor.g / 255.0f,
                             box->param.outlineColor.b / 255.0f};
    bool filled = box->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        box->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        box->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        box->param.isFilled = filled;
    }

    if (filled)
    {
        // La liste des materiaux possibles.
        const char *materialNames[] = {"Personnalise",   "Or", "Argent", "Cuivre", "Chrome", "Plastique rouge",
                                       "Caoutchouc noir"};
        static int currentMaterial = 0;

        // Menu deroulant pour selectionner un materiau.
        ImGui::Text("Materiau :");
        if (ImGui::BeginCombo("Materiau", materialNames[currentMaterial]))
        {
            for (int i = 0; i < IM_ARRAYSIZE(materialNames); i++)
            {
                bool isSelected = (i == currentMaterial);
                if (ImGui::Selectable(materialNames[i], isSelected))
                {
                    currentMaterial = i;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Si c'est un materiaux personnalise.
        if (currentMaterial == 0)
        {
            ImGui::Text("Couleur ambiante :");
            if (ImGui::ColorEdit3("Ambiante", &ambientColor[0]))
            {
                box->setAmbientColor({ambientColor[0], ambientColor[1], ambientColor[2]});
                box->param.ambientColor = ofColor(ambientColor[0] * 255, ambientColor[1] * 255, ambientColor[2] * 255);
            }

            ImGui::Text("Couleur diffuse :");
            if (ImGui::ColorEdit3("Diffuse", &diffuseColor[0]))
            {
                box->setDiffuseColor(glm::vec3{diffuseColor[0], diffuseColor[1], diffuseColor[2]});
                box->param.diffuseColor = ofColor(diffuseColor[0] * 255, diffuseColor[1] * 255, diffuseColor[2] * 255);
            }

            ImGui::Text("Couleur speculaire :");
            if (ImGui::ColorEdit3("Speculaire", &specularColor[0]))
            {
                box->setSpecularColor(glm::vec3{specularColor[0], specularColor[1], specularColor[2]});
                box->param.specularColor =
                    ofColor(specularColor[0] * 255, specularColor[1] * 255, specularColor[2] * 255);
            }

            float shininess = box->getShininess();
            if (ImGui::DragFloat("Brillance", &shininess))
            {
                box->setShininess(shininess);
                box->param.shininess = shininess;
            }
        }

        // Si on selectionne l'or.
        if (currentMaterial == 1)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.247, 0.199, 0.074};
            glm::vec3 diffuseColor{0.247, 0.199, 0.074};
            glm::vec3 specularColor{0.628, 0.555, 0.366};
            float shininess = 51.2f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne l'argent.
        if (currentMaterial == 2)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.192, 0.192, 0.192};
            glm::vec3 diffuseColor{0.507, 0.507, 0.507};
            glm::vec3 specularColor{0.508, 0.508, 0.508};
            float shininess = 51.2f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le cuivre.
        if (currentMaterial == 3)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.229, 0.088, 0.027};
            glm::vec3 diffuseColor{0.550, 0.211, 0.066};
            glm::vec3 specularColor{0.580, 0.223, 0.069};
            float shininess = 51.2f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le chrome.
        if (currentMaterial == 4)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.25, 0.25, 0.25};
            glm::vec3 diffuseColor{0.4, 0.4, 0.4};
            glm::vec3 specularColor{0.774, 0.774, 0.774};
            float shininess = 76.8f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne plastique rouge.
        if (currentMaterial == 5)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.1, 0.0, 0.0};
            glm::vec3 diffuseColor{0.6, 0.0, 0.0};
            glm::vec3 specularColor{0.6, 0.6, 0.6};
            float shininess = 32.0f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        // Si on selectionne le caoutchouc.
        if (currentMaterial == 6)
        {
            // Les proprietes du materiau.
            glm::vec3 ambientColor{0.02, 0.02, 0.02};
            glm::vec3 diffuseColor{0.01, 0.01, 0.01};
            glm::vec3 specularColor{0.4, 0.4, 0.4};
            float shininess = 10.0f;

            // On set les proprietes.
            box->setMaterial(ambientColor, diffuseColor, specularColor, shininess);

            // On set les proprietes d'une maniere differente.
            // Je pense qu'on s'est un peu perdu dans notre architecture mais ca fonctionne.
            setMaterial(box.get(), ambientColor, diffuseColor, specularColor, shininess);
        }

        currentMaterial = 0;
    }

    ImGui::Text("Taille :");
    if (ImGui::DragFloat3("Taille", &box->getSize().x, 0.1f))
        ;
}

void AppGui::drawLightProperties(int i)
{
    glm::vec3 &position = controller->getLightPosition(i);
    ImGui::Text("Position :");
    if (ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f, 0.0f, 2000.0f))
    {
        controller->setLightPosition(position, i);
    }

    glm::vec3 &ambientColor = controller->getAmbientColor(i);
    ImGui::Text("Couleur ambiante :");
    if (ImGui::ColorEdit3("Ambiante", glm::value_ptr(ambientColor)))
    {
        controller->setAmbientColor(ambientColor, i);
    }

    glm::vec3 &diffuseColor = controller->getDiffuseColor(i);
    ImGui::Text("Couleur diffuse :");
    if (ImGui::ColorEdit3("Diffuse", glm::value_ptr(diffuseColor)))
    {
        controller->setDiffuseColor(diffuseColor, i);
    }

    plugin::light::Light::lightType type = controller->getLightType(i);
    if (type == plugin::light::Light::lightType::DIRECTIONAL || type == plugin::light::Light::lightType::SPOT)
    {
        glm::vec3 &direction = controller->getLightDirection(i);
        ImGui::Text("Direction de la lumiere :");
        if (ImGui::DragFloat3("Direction", glm::value_ptr(direction), 0.1f, 0.0f, 2000.0f))
        {
            controller->setLightDirection(direction, i);
        }
    }

    if (type == plugin::light::Light::lightType::SPOT)
    {
        float angle = controller->getLightAngle(i);
        ImGui::Text("Angle du projecteur :");
        if (ImGui::DragFloat("Angle", &angle, 0.1f, 0.0f, 180.0f))
        {
            controller->setLightAngle(angle, i);
        }
    }

    if (type == plugin::light::Light::lightType::SPOT || type == plugin::light::Light::lightType::POINT_LIGHT)
    {
        float intensity = controller->getLightIntensity(i);
        ImGui::Text("Intensite lumineuse :");
        if (ImGui::DragFloat("Intensite", &intensity, 0.1f, 0.0f, 100.0f))
        {
            controller->setLightIntensity(intensity, i);
        }
    }

    plugin::light::LightModel::Type model = controller->getLightModel(i);
    if (model == plugin::light::LightModel::Type::Phong || model == plugin::light::LightModel::Type::BlinnPhong)
    {
        glm::vec3 &specularColor = controller->getSpecularColor(i);
        ImGui::Text("Couleur speculaire :");
        if (ImGui::ColorEdit3("Speculaire", glm::value_ptr(specularColor)))
        {
            controller->setSpecularColor(specularColor, i);
        }

        float shininess = controller->getShininess(i);
        ImGui::Text("Brillance :");
        if (ImGui::DragFloat("Brillance", &shininess, 0.1f, 0.0f, 100.0f))
        {
            controller->setShininess(shininess, i);
        }
    }

    if (ImGui::Button("Supprimer"))
    {
        controller->deleteLight(i);
    }
}

void AppGui::drawObjModelProperties(const std::shared_ptr<plugin::primitive::ObjModel> &model)
{
    drawTransformProperties3D(model);

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &(model->param.isFilled)))
        ;
}

void AppGui::drawTransformProperties2D(const std::shared_ptr<Primitive> &primitive)
{
    glm::vec3 position = primitive->param.position;
    glm::vec3 rotation = primitive->param.rotation;
    glm::vec3 scale = primitive->param.scale;
    char imageName[128];
    strncpy(imageName, primitive->param.imageName.c_str(), sizeof(imageName));
    imageName[sizeof(imageName) - 1] = '\0';

    ImGui::Text("Position :");
    if (ImGui::DragFloat2("Position", &position.x, 0.1f))
    {
        primitive->param.position = position;
    }

    ImGui::Text("Rotation :");
    if (ImGui::DragFloat("Rotation", &rotation.z, 0.1f))
    {
        primitive->param.rotation.z = rotation.z;
    }

    ImGui::Text("Echelle :");
    if (ImGui::DragFloat2("Echelle", &scale.x, 0.1f))
    {
        primitive->param.scale = scale;
    }

    ImGui::Text("Image :");
    if (ImGui::InputText("Image", imageName, sizeof(imageName)))
    {
        primitive->param.imageName = imageName;
    }
}

void AppGui::drawTransformProperties3D(const std::shared_ptr<Primitive> &primitive)
{
    glm::vec3 position = primitive->param.position;
    glm::vec3 rotation = primitive->param.rotation;
    glm::vec3 scale = primitive->param.scale;
    char imageName[128];
    strncpy(imageName, primitive->param.imageName.c_str(), sizeof(imageName));
    imageName[sizeof(imageName) - 1] = '\0';

    ImGui::Text("Position :");
    if (ImGui::DragFloat3("Position", &position.x, 0.1f))
    {
        primitive->param.position = position;
    }

    ImGui::Text("Rotation :");
    if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f))
    {
        primitive->param.rotation = rotation;
    }

    ImGui::Text("Echelle :");
    if (ImGui::DragFloat3("Echelle", &scale.x, 0.1f))
    {
        primitive->param.scale = scale;
    }

    ImGui::Text("Image :");
    if (ImGui::InputText("Image", imageName, sizeof(imageName)))
    {
        primitive->param.imageName = imageName;
    }

    ImGui::Text("Boîte de délimitation :");
    if (ImGui::Checkbox("Dessiner", &(primitive->param.drawGizmo)))
        ;
}
