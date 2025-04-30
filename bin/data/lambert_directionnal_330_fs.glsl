// IFT3100H24 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;

// couleurs de la lumiere
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;

// position d'une source de lumière
uniform vec3 light_direction;

void main()
{
  // re-normaliser la normale après interpolation (n)
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(-light_direction);

  // calculer la couleur de la lumiere ambiante.
  vec3 color_ambient = light_color_ambient * material_color_ambient;

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // calculer la couleur de la reflexion diffuse.
  vec3 color_diffuse = light_color_diffuse * material_color_diffuse * reflection_diffuse;

  // déterminer la couleur du fragment
  fragment_color = vec4(color_ambient + color_diffuse, 1.0);
}
