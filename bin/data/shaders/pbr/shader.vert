// IFT3100H25 ~ pbr_330_vs.glsl

#version 330

in vec4 position;
in vec3 normal;
in vec2 texcoord;
layout(location = 10) in vec4 tangent;

out vec3 surface_position;
out vec3 surface_normal;
out vec2 surface_texcoord;
out mat3 TBN;

uniform sampler2D texture_height;
uniform float displacement_factor = 10.0f;
uniform int use_height_map;

uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 displacedPosition = position;

    if (use_height_map != 0) {
        float height = dot(texture(texture_height, texcoord).rgb, vec3(0.299, 0.587, 0.114));
        displacedPosition += vec4(normalize(normal) * (height * displacement_factor), 0.0);
    }

    mat3 normalMatrix3 = transpose(inverse(mat3(modelMatrix)));
    surface_normal = normalize(normalMatrix3 * normal);
    vec3 T = normalize(normalMatrix3 * tangent.xyz);
    T = normalize(T - dot(T, surface_normal) * surface_normal);
    vec3 B = cross(surface_normal, T);
    TBN = mat3(T, B, surface_normal);

    surface_texcoord = texcoord;

    surface_position = vec3(modelMatrix * displacedPosition);

    vec4 viewPosition = modelViewMatrix * displacedPosition;

    gl_Position = projectionMatrix * viewPosition;
}
