#version 330

// attributs de sommet
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

// attributs en sortie
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;

// attributs uniformes
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

void main()
{
  // passer directement les coordonnées de texture
  fragTexCoord = texcoord;
  fragNormal = normalize(fragNormal);
  fragPos = vec3(modelViewMatrix * position);

  gl_Position = projectionMatrix * modelViewMatrix * position;
}
