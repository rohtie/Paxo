#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

int main( ){
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(640, 480, OF_WINDOW);
	ofRunApp(new ofApp());
}
