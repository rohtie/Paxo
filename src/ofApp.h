#pragma once
#include "ofMain.h"
#include "distanceField.h"

class ofApp : public ofBaseApp{
	public:
		ofTrueTypeFont palanquinRegular;

		ofShader shader;
		ofImage tex0;
		sphere testSphere;

		int sidebarWidth;
		int sidebarBrightness;
		int palanquinRegularBrightness;

		void saveRender(int width, int height);
		void render(int width, int height);
		void compileDistanceFieldShader();

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
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

#if !defined(SHADER_INCLUDES)
#define SHADER_INCLUDES 1
const string shaderHeader 			 = "#pragma include <header.frag>\n";
const string distanceFieldPrimitives = "#pragma include <primitives.frag>\n";
const string raymarchingFramework 	 = "#pragma include <raymarch.frag>\n";
#endif
