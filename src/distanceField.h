#pragma once
#include "ofMain.h"

class distanceField {
    public:
        ofVec3f position;
        ofVec3f scale;
        ofVec3f rotation;

        string toString();
};

class sphere: public distanceField {
    public:
        float radius;

        sphere() {
            position = ofVec3f(0.0, 0.0, 0.0);
            radius = 1.0;
        }

        sphere(ofVec3f _position, float _radius) {
            position = _position;
            radius = _radius;
        }

        string toString() {
            std::stringstream distanceField;
            distanceField << "sphere(point - vec3(" << position << "), " << radius << ")";

            return distanceField.str();
        }
};

class plane: public distanceField {
    public:
        plane() {
            position = ofVec3f(0.0, 0.0, 0.0);
        }

        plane(ofVec3f _position) {
            position = _position;
        }

        string toString() {
            std::stringstream distanceField;
            distanceField << "plane(point - vec3(" << position << "))";

            return distanceField.str();
        }
};
