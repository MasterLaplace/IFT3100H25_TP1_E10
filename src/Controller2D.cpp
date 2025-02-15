#include "Controller2D.hpp"

void Controller2D::setup()
{

    // On initialise l'état du Controlleur pour dessiner des points.
    // On pourrait changer l'état initial au besoin.
    stateMachine.changeState(new DrawPointState());

    // C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);
}

void Controller2D::update() { stateMachine.update(); }

void Controller2D::draw()
{
    // On dessine le canvas en premier.
    canvas.draw();

    // C'est Controlleur qui demande à son état de dessiner des choses en lien avec l'état.
    // Par exemple, si on est dans l'état DrawRectangleState, on va dessiner le fantome du rectangle.
    stateMachine.draw();

    // C'est le Controlleur qui demande au GUI de s'afficher aussi.
    gui.draw();
}

void Controller2D::exit() {}

void Controller2D::keyPressed(int key)
{

    // C'est les racourcies claviers.
    // Les input proviennent de Application.
    if (key == 'p')
    {
        drawPointButtonPressed();
        gui.selectedTool = DrawingTools::tool::POINT;
    }

    if (key == 'l')
    {
        drawLineButtonPressed();
        gui.selectedTool = DrawingTools::tool::LINE;
    }
}

void Controller2D::mouseMoved(glm::vec2 pos)
{

    // On transmet la position de la sourie à l'état.
    // L'input provient de Application.
    stateMachine.mousePosition = pos;
}

void Controller2D::mousePressed(int x, int y, int button) 
{
    // On transmet la position de la sourie à l'état.
    // L'input provient de Application.
    stateMachine.mousePressedPosition = glm::vec2(x, y);
    stateMachine.isMousePressed = true;
}

void Controller2D::mouseReleased(int x, int y, int button) 
{ stateMachine.isMousePressed = false; }

void Controller2D::drawPointButtonPressed() { stateMachine.changeState(new DrawPointState()); }

void Controller2D::onSizeChanged(float newSize) {

    stateMachine.onStrokeSizeChanged(newSize);

}


// Cette méthode reçoit un tableau de trois float parce que c'est ce que ImGui utilise.
// On transforme ce tableau en un ofColor pour l'envoyer à l'état.
void Controller2D::onColorChanged(float _newColor[3])
{

    ofColor newColor = ofColor(_newColor[0]*255, _newColor[1]*255, _newColor[2]*255);
    stateMachine.onColorChanged(newColor);

}

void Controller2D::drawLineButtonPressed() { stateMachine.changeState(new DrawLineState()); }
