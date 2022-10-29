#version 460 core

in vec2 textureCoords;
out vec4 out_color;

uniform sampler2D entityTexture;

void main(){
    out_color = texture(entityTexture, textureCoords);
}