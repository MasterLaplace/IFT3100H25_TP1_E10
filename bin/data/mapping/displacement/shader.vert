#version 330
// Attributs en entrée
in vec4 position;
in vec3 normal;
in vec2 texcoord;

// Attributs en sortie vers le fragment shader
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform sampler2DRect heightMap;
uniform float displacementScale = 5.0; // Paramètre ajustable pour contrôler l'amplitude

void main()
{
    // Lecture de la hauteur depuis la heightmap
    vec4 texColor = texture(heightMap, texcoord);
    float height = dot(texColor.rgb, vec3(0.299, 0.587, 0.114)); // Conversion en luminance
    // Calcul du déplacement avec une échelle ajustable
    vec3 displacedPosition = position.xyz + normalize(normal) * (height * displacementScale);

	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

	// passer directement les coordonnées de texture
	fragTexCoord = texcoord;
  
	// transformer la normale
	fragNormal = normalize(normalMatrix * vec3(normal));
  
	// position du fragment
    fragPos = vec3(modelViewMatrix * vec4(displacedPosition, 1.0));
  
	// position finale
    gl_Position = modelViewProjectionMatrix * vec4(displacedPosition, 1.0);
}