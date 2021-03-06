#version 330 core

in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vPos;

uniform bool uTextureFlag = false;
uniform sampler2D uTextureSampler;
uniform vec3 uLightPosition;

layout(location = 0) out vec4 fColor;

void main() {
    //float intensity = 100.0f/dot(uLightPosition-vPos, uLightPosition-vPos);
    //float diffuse = dot(vNormal, normalize(uLightPosition-vPos));
    //fColor = vec4(vTexCoord, 1.0, 1.0);
    vec3 d = vec3(0.5+0.5*clamp(dot(vNormal, normalize(vec3(-0.4, 1.0, -0.8))), 0.0, 1.0));
    d = 0.4*d + 0.6*gl_FragCoord.w*gl_FragCoord.w;
    fColor = vec4(d, 1.0);

    //fColor = vec4(vColor, 1.0);
}
