#version 330

layout (location = 0) in vec2 position;

out vec2 coord;

uniform float r;
uniform float s;
uniform vec2 center;

void main() {
	gl_Position = vec4(position, 0.f, 1.f);

	coord = vec2(
		0.5f * s * r * position.x + center.x,
		0.5f * s     * position.y + center.y
	);
}