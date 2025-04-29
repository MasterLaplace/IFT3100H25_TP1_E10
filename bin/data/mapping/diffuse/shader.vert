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
uniform mat4 modelViewProjectionMatrix;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

	// passer directement les coordonnées de texture
	fragTexCoord = texcoord;
  
	// transformer la normale
	fragNormal = normalize(normalMatrix * vec3(normal));
  
	// position du fragment
	fragPos = vec3(modelViewMatrix * position);
  
	// position finale
	gl_Position = modelViewProjectionMatrix * position;
}