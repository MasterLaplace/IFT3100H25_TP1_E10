// Lumiere ambiante avec Phong.

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 material_color_ambient;

// couleurs de la lumiere.
uniform vec3 light_color_ambient;

void main()
{
  // calculer la couleur ambiante.
  vec3 color_ambient = light_color_ambient * material_color_ambient;

  // calculer la couleur du fragment
  fragment_color = vec4( color_ambient, 1.0);
}