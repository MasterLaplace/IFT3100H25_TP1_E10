// IFT3100H24 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// propriete de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;

// propriete de la lumiere
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;
uniform vec3 light_position;
uniform vec3 light_direction;
uniform float light_range;
uniform float light_angle;

void main()
{
  // re-normaliser la normale après interpolation (n)
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer la couleur de la lumiere ambiante.
  vec3 color_ambient = light_color_ambient * material_color_diffuse;

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // calculer la couleur de la reflexion diffuse.
  vec3 color_diffuse = light_color_diffuse * material_color_diffuse * reflection_diffuse;

  // calculer les facteurs d'attenuation.
  float k = 1.0; // facteur d'atténuation constant
  float kl = 2.0 / light_range; // facteur d'atténuation linéaire
  float kq = 1.0 / (light_range * light_range); // facteur d'atténuation quadratique

  // calculer la distance entre la lumière et le fragment
  //float d = length(light_position - surface_position);
  float d = 10.0;

  // calculer l'atténuation
  float attenuation = 1.0 / (k + kl * d + kq * d * d);

  // calculer l'effet du spot.
  vec3 i = normalize(surface_position - light_position);
  float angleAttenuation = max(dot(light_direction, i), 0.0);
  float spotEffect = pow(angleAttenuation, light_angle);

  // appliquer l'effet du spot.
  vec3 result = attenuation * spotEffect * (color_ambient + color_diffuse);

  // calculer la couleur du fragment
  fragment_color = vec4( result, 1.0);
}
