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
