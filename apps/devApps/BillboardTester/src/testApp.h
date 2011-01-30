#pragma once
#include "ofMain.h"
#include "ofVbo.h"

#define	NUM_BILLBOARDS	300

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	ofVbo		vbo;
	ofShader	shader;
	ofImage		texture;
	ofVec2f		pos[NUM_BILLBOARDS];
	ofVec2f		vel[NUM_BILLBOARDS];
	float		pointSizes[NUM_BILLBOARDS];
	float		rotations[NUM_BILLBOARDS];
};









