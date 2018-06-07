float min(float a, float b) { return a < b ? a : b; }

float max(float a, float b) { return a > b ? a : b; }

float clamp(float i, float min, float max) { return i < min ? min : i > max ? max : i; }
