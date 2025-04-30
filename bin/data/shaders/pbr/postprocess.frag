#version 150

uniform sampler2DRect scene;
uniform float gamma;

in vec2 surface_texcoord;
out vec4 output_color;

void main()
{
    vec3 color = texture(scene, surface_texcoord).rgb;

    // Application de la correction gamma
    color = pow(color, vec3(1.0 / gamma));

    output_color = vec4(color, 1.0);
}
