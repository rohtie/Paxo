const float maxDistance      = 10.0;
const float distanceTreshold = 0.001;
const int   maxIterations    = 50;

float intersect(vec3 rayOrigin, vec3 rayDirection) {
    float distance = 0.0;
    float currentDistance = 1.0;

    for (int i = 0; i < maxIterations; i++) {
        if (currentDistance < distanceTreshold || distance > maxDistance) {
            break;
        }

        currentDistance = map(rayOrigin + rayDirection * distance);

        distance += currentDistance;
    }

    if (distance > maxDistance) {
        return -1.0;
    }

    return distance;
}

float softshadow(vec3 point, vec3 light, float minDistance, float maxDistance, float smoothness) {
    float shadow = 1.0;

    for (float distance = minDistance; distance < maxDistance;) {
        float currentDistance = map(point + light * distance);

        if (currentDistance < 0.001) {
            return 0.0;
        }

        shadow = min(shadow, smoothness * currentDistance / distance);
        distance += currentDistance;
    }

    return shadow;
}

vec3 getNormal(vec3 point) {
    vec2 extraPolate = vec2(0.002, 0.0);

    return normalize(vec3(
        map(point + extraPolate.xyy),
        map(point + extraPolate.yxy),
        map(point + extraPolate.yyx)
    ) - map(point));
}

vec3 light = normalize(vec3(1.5, 1.5, 2.5));

void main() {
    vec2 point = gl_FragCoord.xy;

    point /= resolution.xy;
    point = 2.0 * point - 1.0;
    point.x *= resolution.x / resolution.y;

    vec3 cameraPosition = vec3(0.0, 0.0, 2.0);
    vec3 rayDirection = normalize(vec3(point, -1.0));

    float distance = intersect(cameraPosition, rayDirection);

    vec3 col = vec3(0.0);
    if (distance > 0.0) {
        vec3 point = cameraPosition + rayDirection * distance;
        vec3 normal = getNormal(point);

        // Diffuse
        col += vec3(0.7, 1.0, 0.95) * max(dot(normal, light), 0.0);

        // Specular
        vec3 halfVector = normalize(light + normal);
        col += pow(max(dot(normal, halfVector), 0.0), 1024.0);

        // Attenuation and shadow
        float attenuation = clamp(1.0 - length(light - point) / 20.0, 0.0, 1.0);
        col *= attenuation * attenuation * softshadow(point, light, 0.02, 2.5, 8.0);

        // Ambient
        col += vec3(0.01, 0.01, 0.3);
    }

    outputColor = vec4(col, 1.0);
}
