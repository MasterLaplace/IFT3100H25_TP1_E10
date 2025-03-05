#include "SelectionState.hpp"

namespace plugin::states {

void SelectionState::enter() {}

void SelectionState::update() {}

void SelectionState::draw() {}

void SelectionState::exit() {}

void SelectionState::mousePressed(int x, int y, int button) {}

void SelectionState::mouseReleased(Canvas *canvas)
{
    selectedPrimitiveId = findSelectedNode(glm::vec3(mousePosition.x, mousePosition.y, 0), canvas->nodes);
}

void SelectionState::drawCursor() {}

void SelectionState::drawPreview() {}

int SelectionState::findSelectedNode(const glm::vec3 &position, const std::vector<NodePrimitive *> &nodes)
{
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        int nodeId = findSelectedNode(position, nodes[i]->getChildren());

        if (nodeId != -1)
        {
            return nodeId;
        }

        if (nodes[i]->getPrimitive()->isInside(position))
        {
            return nodes[i]->getId();
        }
    }
    return -1;
}

} // namespace plugin::states
