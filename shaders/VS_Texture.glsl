/**
    VS_Texture.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtim�ki
    @date       2015-04-18
**/


#version 330 core

layout(location = 0) in vec3 position;

out vec2 UV;

void main() {
    UV = vec2((position.x+1)*0.5, (1-position.y)*0.5); //inverted y
    gl_Position = vec4(position, 1.0);
}
