/*
Une classe qui permet de dessiner l'histogramme d'une image.

CHOSE A AMELIORER : J'utilise des valeurs constante pour les dimensions de l'histogramme. 
					Il serait probablement preferable de les calculer en fonction de la taille de la fenetre.
					Je ne suis pas certain de l'optimisation non plus.
*/

#pragma once

#include "ofMain.h"
#include <vector>

class Histogram
{
public:

	void setup(ofImage _image);
	void draw(char c);

private:

	const int OFFSET = 100;
	const int MAX_COLOR_VALUE = 256;
	const int MAX_Y = 974;
	const int MAX_X = 1280;
	const int BAR_WIDTH = MAX_X / MAX_COLOR_VALUE;

	ofImage image;
	ofTrueTypeFont font;
	ofColor color;

	vector<int> redAbsoluteHistogram;
	vector<int> greenAbsoluteHistogram;
	vector<int> blueAbsoluteHistogram;

	vector<float> redRelativeHistogram;
	vector<float> greenRelativeHistogram;
	vector<float> blueRelativeHistogram;

	vector<int>* histogramAbsolute = nullptr;
	vector<float>* histogramRelative = nullptr;

	int maxValue;

	vector<int> getRed();
	vector<int> getGreen();
	vector<int> getBlue();
	vector<float> getRelativeHistogram(vector<int> h);
	void drawHistogram();
	void drawXAxis();
	void drawYAxis();
	void drawVerticalText(const std::string& text, float x, float y);
	bool mouseIsHoveringBar(glm::vec2 barTop, float barHeight);
	void drawTooltip();
};
