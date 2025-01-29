// IFT3100H25_AlmostEmptyProject/application.cpp
// Classe principale de l'application.

#include "application.h"

// fonction d'initialisation de l'application
void Application::setup()
{
	image.load("test.jpg");
	ofSetWindowShape(image.getWidth(), image.getHeight());
	histogram.setup(image);
}

// fonction de mise à jour de la logique de l'application
void Application::update()
{

}

// fonction de mise à jour du rendu de la fenêtre d'affichage de l'application
void Application::draw()
{
	if (!is_histogram_drawn)
	{
		image.draw(0, 0);
	}

	else
	{
		histogram.draw(histogram_color);
	}

}

// fonction appelée juste avant de quitter l'application
void Application::exit()
{

}

void Application::keyPressed(int key)
{
	if (key == ' ')
	{
		is_histogram_drawn = false;
	}

	else if (key == 'r')
	{
		is_histogram_drawn = true;
		histogram_color = 'r';
	}

	else if (key == 'g')
	{
		is_histogram_drawn = true;
		histogram_color = 'g';
	}

	else if (key == 'b')
	{
		is_histogram_drawn = true;
		histogram_color = 'b';
	}
}
