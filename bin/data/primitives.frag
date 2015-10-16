float plane(vec3 point) {
    return point.y;
}

float sphere(vec3 point, float radius) {
    return length(point) - radius;
}

float box(vec3 point, vec3 dimensions) {
  dimensions = abs(point) - dimensions;
  return min(max(dimensions.x, max(dimensions.y, dimensions.z)), 0.0)
         + length(max(dimensions, 0.0));
}

float ellipsoid(vec3 point, vec3 dimensions) {
    return (length(point / dimensions) - 1.0)
           * min(min(dimensions.x, dimensions.y), dimensions.z);
}

float roundBox(vec3 point, vec3 dimensions, float radius) {
    return length(max(abs(point) - dimensions, 0.0)) - radius;
}

float torus(vec3 point, vec2 dimensions) {
    return length(vec2(length(point.xz) - dimensions.x, point.y))
           - dimensions.y;
}
