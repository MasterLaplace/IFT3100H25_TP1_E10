#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;
out vec4 outputColor;

uniform sampler2DRect diffuseTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor = vec3(1.0);
uniform float shininess = 3.0;
uniform float specularStrength = 0.3;

void main()
{
    // Échantillonnage de la couleur
    vec4 texColor = texture(diffuseTexture, fragTexCoord);

    vec3 fNormal = normalize(fragNormal);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);

    // Diffuse
    float diffuse = max(dot(fNormal, lightDir), 0.0);

    // Spéculaire Blinn-Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specAmount = pow(max(dot(fNormal, halfwayDir), 0.0), shininess);
    float specular = specularStrength * specAmount;

    vec3 lighting = texColor.rgb * (diffuse + 0.6 + specular) * lightColor;

    outputColor = vec4(lighting, texColor.a);
}