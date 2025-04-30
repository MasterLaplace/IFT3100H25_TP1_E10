// IFT3100H24 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// proprietes de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;

// propriete de la lumiere
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;
uniform vec3 light_position;
uniform float light_range;

uniform mat4 view_matrix;

void main()
{
  // re-normaliser la normale après interpolation (n)
  vec3 n = normalize(surface_normal);

  vec3 light_position_view = (view_matrix * vec4(light_position, 1.0)).xyz;

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position_view - surface_position);

  // calculer la couleur de la lumiere ambiante.
  vec3 color_ambient = light_color_ambient * material_color_ambient;

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // calculer la couleur de la reflexion diffuse.
  vec3 color_diffuse = light_color_diffuse * material_color_diffuse * reflection_diffuse;

  // claculer la distance entre la lumière et le fragment
  // float d = length(light_position_view - surface_position);
  float d = 10.0;
   
  // calculer les facteurs d'atténuation
  float kc = 1.0; // facteur d'atténuation constant
  float kl = 2.0 / light_range; // facteur d'atténuation linéaire
  float kq = 1.0 / (light_range * light_range); // facteur d'atténuation quadratique

  // calculer l'atténuation
  float k = 1.0 / max(kc + kl * d + kq * (d * d), 0.01);

  // appliquer l'atténuation à la couleur
  vec3 result = k * (color_ambient + color_diffuse);

  // calculer la couleur du fragment
  fragment_color = vec4( result, 1.0);
}
