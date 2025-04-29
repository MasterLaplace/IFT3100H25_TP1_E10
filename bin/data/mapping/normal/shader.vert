#version 330
// attributs de sommet
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
in vec4 tangent; // Nécessaire pour le normal mapping

// attributs en sortie
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;
out mat3 TBN; // Pour le normal mapping

// attributs uniformes
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
  // passer directement les coordonnées de texture
  fragTexCoord = texcoord;
  
  // transformer la normale
  fragNormal = normalize(normalMatrix * vec3(normal));
  
  // calculer TBN pour le normal mapping
  vec3 T = normalize(normalMatrix * vec3(tangent));
  T = normalize(T - dot(T, fragNormal) * fragNormal);
  vec3 B = cross(fragNormal, T);
  TBN = mat3(T, B, fragNormal);
  
  // position du fragment
  fragPos = vec3(modelViewMatrix * position);
  
  // position finale
  gl_Position = projectionMatrix * modelViewMatrix * position;
}