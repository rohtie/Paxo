#include "ofApp.h"
#include "distanceField.h"

void ofApp::setup() {
    sidebarWidth = 300;
    sidebarBrightness = 64;
    palanquinRegularBrightness = 200;

    palanquinRegular.loadFont("Palanquin-Regular.ttf", 15);

    selectedDistanceField = distancePtr(new sphere(ofVec3f(-2.0, 0.0, 0.0), 0.5));

    distanceFields.push_back(selectedDistanceField);
    distanceFields.push_back(distancePtr(new plane(ofVec3f(0.0, -1.0, 0.0))));
    distanceFields.push_back(distancePtr(new box(ofVec3f(2.0, 0.0, -2.0),
                                                 ofVec3f(0.2, 1.0, 1.5))));

    // Normalize texture coordinates so that they are within 0 to 1 range
    ofDisableArbTex();

    tex0.loadImage("tex11.png");

    // Make sure textures can be repeated
    ofSetTextureWrap(GL_REPEAT, GL_REPEAT);

    compileDistanceFieldShader();
}

void ofApp::update() {
    compileDistanceFieldShader();
}

void ofApp::draw() {
    int width = ofGetWidth(), height = ofGetHeight();
    int sceneWidth = width - sidebarWidth;

    render(sceneWidth, height);

    // Render sidebar
    ofSetColor(sidebarBrightness);
    ofRect(sceneWidth, 0, width - sceneWidth, height);

    for (uint i = 0; i < distanceFields.size(); i++) {
        int y = i * 42;

        ofSetColor(sidebarBrightness + 25);
        ofRect(sceneWidth, y, width - sceneWidth, 40);

        ofSetColor(25);
        palanquinRegular.drawString(distanceFields[i]->getName(), sceneWidth + 40, y + 42 - 15);
    }

    // Display FPS
    stringstream fps;
    fps << round(ofGetFrameRate()) << " FPS";
    ofSetColor(palanquinRegularBrightness);
    palanquinRegular.drawString(fps.str(), sceneWidth - 15*6, 30);
}

/**
 * Generate string of distance fields.
 *
 * Recursive function which generates an union of all distance fields.
 */
string ofApp::generateDistanceString(uint index) {
    if (index < distanceFields.size() - 1) {
        stringstream distanceFieldMap;
        distanceFieldMap
            << "min(" << distanceFields[index]->toString() << ", "
                      << generateDistanceString(index + 1)
            << ")";

        return distanceFieldMap.str();
    }

    return distanceFields[index]->toString();
}

/**
 * Compile distance field shader from string.
 */
void ofApp::compileDistanceFieldShader() {
    stringstream distanceFieldMap;
    distanceFieldMap
        << "float map(vec3 point) {\n"
        << "    return " << generateDistanceString(0) << ";\n"
        << "}\n";

    stringstream shaderSource;

    shaderSource
        << shaderHeader
        << distanceFieldPrimitives
        << distanceFieldMap.str()
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
    shader.setUniformTexture("tex0", tex0.getTextureReference(), 0);
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
    float stepSize = 0.05;

    switch (key) {
        case 'w': selectedDistanceField->position.z -= stepSize; break;
        case 's': selectedDistanceField->position.z += stepSize; break;
        case 'a': selectedDistanceField->position.x -= stepSize; break;
        case 'd': selectedDistanceField->position.x += stepSize; break;
        case 'e': selectedDistanceField->position.y -= stepSize; break;
        case 'q': selectedDistanceField->position.y += stepSize; break;

        case 'p':
            saveRender(7680, 4320);
            break;

        case 'o':
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
