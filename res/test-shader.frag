#version 330
out vec4 fragColor;

in vec2 coord;

int max_iter = 256;

void main() {
	fragColor = vec4(abs(coord), 0.f, 1.f);
}