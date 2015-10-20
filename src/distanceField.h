#pragma once
#include "ofMain.h"

class distanceField {
    public:
        ofVec3f position;
        ofVec3f scale;
        ofVec3f rotation;

        virtual string toString() = 0;
        virtual string getName() = 0;
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
            stringstream distanceField;
            distanceField << "sphere(point - vec3(" << position << "), " << radius << ")";

            return distanceField.str();
        }

        string getName() {
            return "SPHERE";
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
            stringstream distanceField;
            distanceField << "plane(point - vec3(" << position << "))";

            return distanceField.str();
        }

        string getName() {
            return "PLANE";
        }
};

class box: public distanceField {
    public:
        ofVec3f dimensions;

        box() {
            position = ofVec3f(0.0, 0.0, 0.0);
            dimensions = ofVec3f(1.0, 1.0, 1.0);
        }

        box(ofVec3f _position, ofVec3f _dimensions) {
            position = _position;
            dimensions = _dimensions;
        }

        string toString() {
            stringstream distanceField;
            distanceField << "box(point - vec3(" << position << "), vec3(" << dimensions << "))";

            return distanceField.str();
        }

        string getName() {
            return "BOX";
        }
};
