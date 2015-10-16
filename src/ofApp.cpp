#include "ofApp.h"
#include "distanceField.h"

void ofApp::setup() {
	// Normalize texture coordinates so that they are within 0 to 1 range
	ofDisableArbTex();

    iChannel0.loadImage("tex11.png");

    // Make sure textures can be repeated
    ofSetTextureWrap(GL_REPEAT, GL_REPEAT);

    // Setup shader
    sphere testSphere(ofVec3f(1.24, 0.1, -0.5), 1.0);

    std::stringstream distanceFieldMap;
    distanceFieldMap
        << "float map(vec3 point) {\n"
        << "    return " << testSphere.toString() << ";\n"
        << "}\n";

    compileDistanceFieldShader(distanceFieldMap.str());
}

void ofApp::update() {

}

void ofApp::draw() {
	render(ofGetWidth(), ofGetHeight());
}

/**
 * Compile distance field shader from string.
 */
void ofApp::compileDistanceFieldShader(string distanceFieldMap) {
    std::stringstream shaderSource;

    shaderSource
        << shaderHeader
        << distanceFieldPrimitives
        << distanceFieldMap
        << raymarchingFramework;

    shader.setupShaderFromFile(GL_VERTEX_SHADER, "shad.vert");
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderSource.str());
    shader.bindDefaults();
    shader.linkProgram();
}

/**
 * Render the shader.
 */
void ofApp::render(int width, int height) {
    shader.begin();
    shader.setUniformTexture("tex0", iChannel0.getTextureReference(), 0);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform2f("resolution", width, height);
    shader.setUniform2f("mouse", mouseX / (float) width, 1.0f - mouseY / (float) height);
    ofRect(0, 0, width, height);
    shader.end();
}

/**
 * Render screen to file at given resolution.
 */
void ofApp::saveRender(int width, int height) {
    ofFbo fbo;
    fbo.allocate(width, height);

    fbo.begin();
    render(width, height);
    fbo.end();

    ofPixels pixels;
    fbo.readToPixels(pixels);

    ofImage image;
    image.setFromPixels(pixels);

    // OpenGL is designed around bottom up framebuffers and textures
    // Therefore we need to flip the pixels from the fbo vertically
    // to avoid that the saved image is upside down.
    image.mirror(true, false);

    image.saveImage("render.png");
}

void ofApp::keyPressed(int key) {
	switch (key) {
		case 's':
			saveRender(7680, 4320);
			break;

		case 'f':
			ofImage screenshot;
			screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			screenshot.saveImage("screenshot.png");
			break;
	}
}

void ofApp::keyReleased(int key) {

}

void ofApp::mouseMoved(int x, int y ) {

}

void ofApp::mouseDragged(int x, int y, int button) {

}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::mouseReleased(int x, int y, int button) {

}

void ofApp::windowResized(int w, int h) {

}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}
