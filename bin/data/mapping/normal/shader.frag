#version 330
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;
in mat3 TBN;
out vec4 outputColor;

uniform sampler2DRect diffuseTexture;
uniform sampler2DRect normalMap;

uniform vec3 lightDir;       // Direction vers la lumière (doit être normalisée)
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform float ambientStrength = 0.1;

void main()
{
  // Couleur de base (diffuse)
  vec4 texColor = texture(diffuseTexture, fragTexCoord);

  // Lire et transformer la normale depuis la normal map
  vec3 normalFromMap = texture(normalMap, fragTexCoord).rgb;
  normalFromMap = normalize(normalFromMap * 2.0 - 1.0); // [0,1] -> [-1,1]

  // Transformer la lumière en espace tangent
  vec3 lightDirTangent = normalize(TBN * -lightDir);

  // Calcul de la lumière
  float diff = max(dot(normalFromMap, lightDirTangent), 0.0);

  vec3 ambient = ambientStrength * lightColor;
  vec3 diffuse = diff * lightColor;
  vec3 result = (ambient + diffuse) * texColor.rgb;

  outputColor = vec4(result, texColor.a);
}
