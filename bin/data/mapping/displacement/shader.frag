#version 330

// Entrées et sortie
in vec3 fragPos;
in vec2 fragTexCoord;
out vec4 outputColor;

uniform sampler2DRect tex0;

void main()
{
  outputColor = texture(tex0, fragTexCoord);
}
