float smin(float a, float b, float smoothness) {
    float result = clamp(0.5 + (0.5 * (b - a) / smoothness), 0.0, 1.0);
    return mix(b, a, result) - smoothness * result * (1.0 - result);
}
