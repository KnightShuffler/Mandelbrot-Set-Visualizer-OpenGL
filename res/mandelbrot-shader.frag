#version 330

in vec2 coord;

out vec4 fragColor;

#define MAX_ITER 255

// Converts (normalized) HSV color vector to a (normalized) RGB color vector
vec3 HSV_to_RGB(float h, float s, float v);

void main() {
	// Iteration count
	int i;
	
	// The constant term
	vec2 c = coord;
	// Where to store the iterated value
	vec2 z = coord;

	// Iterating loop
	for (i = 0; i <= MAX_ITER; i++) {
		// Calcualte the z = z^2 + c
		z = vec2( pow(z.x, 2) - pow(z.y, 2), 2.f * z.x * z.y ) + c;
		// Break if the 
		if (length(z) >= 2.f)
			break;
	}

	// Normalize the iterator (for hue)
	float norm_i = float(i) / float(MAX_ITER);

	// Plot colors, if in the set, mark it black (0 value)
	fragColor = vec4(HSV_to_RGB(norm_i, 1.f, i > MAX_ITER ? 0.f : 1.f), 1.f);
}


vec3 HSV_to_RGB(float h, float s, float v) {
	float c = v * s;
	h = mod((h * 6.f), 6.f);
	float x = c * (1.f - abs(mod(h,2.f) - 1.f));

	if (0 <= h && h < 1)
		return vec3(c, x, 0.f);

	else if (1 <= h && h < 2)
		return vec3(x, c, 0.f);

	else if (2 <= h && h < 3)
		return vec3(0.f, c, x);

	else if (3 <= h && h < 4)
		return vec3(0.f, x, c);

	else if (4 <= h && h < 5)
		return vec3(x, 0.f, c);

	else if (5 <= h && h < 6)
		return vec3(c, 0.f, x);

	else
		return vec3(0.f, 0.f, 0.f);
}