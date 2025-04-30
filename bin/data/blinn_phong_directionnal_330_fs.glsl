// Lumiere directionnelle avec Blinn-Phong.

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;
uniform vec3 material_color_specular;
uniform float brightness;

// position d'une source de lumière
uniform vec3 light_direction;
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;
uniform vec3 light_color_specular;

float saturate(float x)
{
  return clamp(x, 0.0, 1.0);
}

void main()
{
  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(-light_direction);

  // calculer la couleur ambiante.
  vec3 color_ambient = light_color_ambient * material_color_ambient;

  // calculer la couleur diffuse.
  vec3 color_diffuse = light_color_diffuse * material_color_diffuse;

  // calculer la direction de la surface vers la caméra (v)
  vec3 v = normalize(-surface_position);

  // calculer la direction du demi-vecteur de réflection (h) en fonction du vecteur de vue (v) et de lumière (l)
  vec3 h = normalize(v + l);

  // calculer la direction de la lumière (l) en fonction de la normale (n)
  // Specifique pour la lumière directionnelle
  float cosTheta = saturate(dot(n, l));

  // calculer je sais pas quoi pour le calcul de la reflexion speculaire.
  // J'ai pris ca dans les notes de cours.
  float cosO = saturate(dot(n, h));

  // calculer le niveau de réflexion spéculaire (n • h)
  float reflection_specular = pow(cosO, brightness);

  // calculer la couleur speculaire.
  vec3 color_specular = light_color_specular * material_color_specular * reflection_specular;

  // calculer la couleur du fragment
  fragment_color = vec4( color_ambient + ((color_diffuse + color_specular) * cosTheta), 1.0);
}
