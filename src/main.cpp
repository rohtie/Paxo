#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

int main( ){
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1366, 726, OF_WINDOW);
	ofRunApp(new ofApp());
}
