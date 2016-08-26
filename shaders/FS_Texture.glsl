/**
    FS_Texture.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18
**/


#version 330 core


#define PI 3.14159265359


in vec2 UV;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;


void main() {
    color = vec4(UV, 1.0, 1.0);
}
