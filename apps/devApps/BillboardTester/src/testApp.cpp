#include "testApp.h"


//--------------------------------------------------------------
//---------------------   THOUGHTS    --------------------------
//--------------------------------------------------------------
/*
 just some thought on how we could wrap this
 into ofShader...
 shader.setVertexAttribute1fv("name", data);  
 shader.setVertexAttribute2fv("name", data);
 shader.setVertexAttribute3fv("name", data);
 shader.setVertexAttribute4fv("name", data);
 
 shader.setVertexAttribute1fv("name", data);  
 shader.setVertexAttribute2fv("name", data);
 shader.setVertexAttribute3fv("name", data);
 shader.setVertexAttribute4fv("name", data);
 
 shader.bindAttribute("name");
 shader.enableVertexAttrib("name");
 
 // GL Functions... 
 void glVertexAttrib1f(GLint location, GLfloat v0);
 void glVertexAttrib2f(GLint location, GLfloat v0, GLfloat v1);
 void glVertexAttrib3f(GLint location, GLfloat v0, GLfloat v1,GLfloat v2);
 void glVertexAttrib4f(GLint location, GLfloat v0, GLfloat v1,,GLfloat v2, GLfloat v3); 
 
 GLint glVertexAttrib{1,2,3,4}fv(GLint location, GLfloat *v); 
 glBindAttribLocation(shader.getProgram(), pointAttLocation, "pointSize");
 */
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------



//--------------------------------------------------------------
void testApp::setup() {
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetLineWidth(3.0);
	
	
	// billboard particles
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		pos[i].x = ofRandomWidth();
		pos[i].y = ofRandomHeight();
		pointSizes[i] = ofNextPow2(ofRandom(2, 64));
		rotations[i]  = ofRandom(0, 1);
	}
	
	// set the vertex data
	vbo.setVertexData(pos, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	shader.setup("Billboard");
	
	
	ofDisableArbTex();
	texture.loadImage("fly.png");
}

//--------------------------------------------------------------
void testApp::update() {

	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	ofVec2f mouseVec(ofGetPreviousMouseX()-ofGetMouseX(), ofGetPreviousMouseY()-ofGetMouseY());
	mouseVec.limit(10.0);
	
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		
		rotations[i]  += 0.03;
		
		if(mouse.distance(pos[i]) < 100.0) {
			vel[i] -= mouseVec;	
		}
		
		pos[i] += vel[i];
		vel[i] *= 0.94f;
		
		if(pos[i].x < 0) pos[i].x = ofGetWidth();
		if(pos[i].x > ofGetWidth()) pos[i].x = 0;
		if(pos[i].y < 0) pos[i].y = ofGetHeight();
		if(pos[i].y > ofGetHeight()) pos[i].y = 0;
	}
		
}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	ofEnableAlphaBlending();
	ofSetHexColor(0xffffff);
	
	ofEnablePointSprites();
	shader.begin();
	
	
	// we are getting the location of the point size attribute
	// we then set the  pointSizes to the vertex attritbute
	// we then bind and then enable
	int pointAttLoc = shader.getAttributeLocation("pointSize");
	glVertexAttribPointer(pointAttLoc, 1, GL_FLOAT, false, 0, pointSizes);
	glBindAttribLocation(shader.getProgram(), pointAttLoc, "pointSize");
	glEnableVertexAttribArray(pointAttLoc);

	
	// rotate the fly based on the velocity
	int angleLoc = shader.getAttributeLocation("angle");
	
	
	
	
	texture.getTextureReference().bind();
	vbo.updateVertexData(pos, NUM_BILLBOARDS);
	vbo.draw(GL_POINTS, 0, NUM_BILLBOARDS);
	texture.getTextureReference().unbind();

	
	shader.end();
	ofDisablePointSprites();
	
	// disable vertex attributes
	glDisableVertexAttribArray(pointAttLoc); 
	glDisableVertexAttribArray(angleLoc);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

