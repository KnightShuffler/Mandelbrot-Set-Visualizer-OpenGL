#version 330

in vec2 coord;

out vec4 fragColor;

const int max_iter = 255;

void main() {
	int i;

	vec2 c = coord;
	vec2 z = coord;

	for (i = 0; i <= max_iter; i++) {
		z = vec2( pow(z.x, 2) - pow(z.y, 2), 2.f * z.x * z.y ) + c;
		if (length(z) >= 2.f)
			break;
	}

	if (i > max_iter) {
		i = 0;
	}

	float gray = float(i) / float(max_iter);

	fragColor = vec4( gray, gray, gray, 1.f );
}
