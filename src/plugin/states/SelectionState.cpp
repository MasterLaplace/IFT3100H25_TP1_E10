#include "SelectionState.hpp"

namespace plugin::states {

void SelectionState::enter() {}

void SelectionState::update() {}

void SelectionState::draw() {}

void SelectionState::exit() {}

void SelectionState::mousePressed(int x, int y, int button) {}

void SelectionState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();
    int nodeId = findSelectedNode(glm::vec2(x, y), canvas->nodes);
    selectedPrimitiveId = nodeId;

    ofLog() << "Selected primitive: " << selectedPrimitiveId;
}

void SelectionState::drawCursor() {}

void SelectionState::drawPreview() {}

int SelectionState::findSelectedNode(glm::vec2 position, std::vector<Node2D *> nodes)
{
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        int nodeId = findSelectedNode(position, nodes[i]->children);

        if (nodeId != -1)
        {
            return nodeId;
        }

        if (nodes[i]->primitive->isInside(&position))
        {
            return nodes[i]->primitive->id;
        }
    }
    return -1;
}

} // namespace plugin::states
