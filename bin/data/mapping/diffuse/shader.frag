#version 330

// Entrées et sortie
in vec3 fragPos;
in vec2 fragTexCoord;
out vec4 outputColor;

uniform sampler2DRect diffuseTexture;

void main()
{
  outputColor = texture(diffuseTexture, fragTexCoord);
}
