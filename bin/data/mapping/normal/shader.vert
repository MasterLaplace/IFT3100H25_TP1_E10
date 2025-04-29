#version 330
// attributs de sommet
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
layout(location = 10) in vec4 tangent;

// attributs en sortie
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;
out mat3 TBN; // Matrice Tangent-Bitangent-Normal pour le normal mapping

// attributs uniformes
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

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