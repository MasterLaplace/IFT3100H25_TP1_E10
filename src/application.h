#pragma once

#include "ofMain.h"
#include "histogram.h"

class Application : public ofBaseApp
{
public:
	
	ofImage image;
	Histogram histogram;

	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

private:
	bool is_histogram_drawn = false;
	char histogram_color = 'r';
};
