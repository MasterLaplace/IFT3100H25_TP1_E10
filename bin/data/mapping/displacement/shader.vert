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
    
    // Outputs vers fragment shader
    fragNormal = mat3(modelViewMatrix) * normal; // Transformer la normale vers l'espace vue
    fragNormal = normalize(fragNormal);
    fragPos = vec3(modelViewMatrix * vec4(displacedPosition, 1.0));
    fragTexCoord = texcoord;
    
    gl_Position = modelViewProjectionMatrix * vec4(displacedPosition, 1.0);
}