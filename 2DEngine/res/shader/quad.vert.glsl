#version 460 core
layout (location = 0) in vec2 a_Position;

uniform int texture_type;
uniform int tileSize;
uniform ivec2 tileLoc;
uniform mat4 u_mvp;

out vec2 textureCoords;

void main() {
    gl_Position = u_mvp * vec4(a_Position.xy, 0.0, 1.0);
	

	textureCoords = vec2((a_Position.x + 1.0) / 2.0,
			1 - (a_Position.y + 1.0) / 2.0);

	if (texture_type == 1) { 
		textureCoords = vec2(
			(textureCoords.x + tileLoc.x) / tileSize - 0.0000001 * a_Position.x,
			(textureCoords.y + tileLoc.y) / tileSize + 0.0000001 * a_Position.y);
	}
}