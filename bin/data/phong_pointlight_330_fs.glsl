// IFT3100H24 ~ phong_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// proprietes de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;
uniform vec3 material_color_specular;
uniform float brightness;

// propriete de la lumière
uniform vec3 light_position;
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;
uniform vec3 light_color_specular;
uniform float light_range;

void main()
{
  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer la couleur ambiente.
  vec3 color_ambient = light_color_ambient * material_color_ambient;

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // calculer la couleur diffuse.
  vec3 color_diffuse = light_color_diffuse * material_color_diffuse * reflection_diffuse;

  // calculer la direction de la surface vers la caméra (v)
  vec3 v = normalize(-surface_position);

  // calculer la direction de la réflection (r) du rayon incident (-l) en fonction de la normale (n)
  vec3 r = reflect(-l, n);

  // calculer le niveau de réflexion spéculaire (r • v)
  float reflection_specular = pow(max(dot(v, r), 0.0), brightness);

  // calculer la couleur speculaire.
  vec3 color_specular = light_color_specular * material_color_specular * reflection_specular;

  // claculer la distance entre la lumière et le fragment
  //float d = length(light_position - surface_position);
  float d = 10.0;

  // calculer les facteurs d'atténuation
  float kc = 1.0; // facteur d'atténuation constant
  float kl = 2.0 / light_range; // facteur d'atténuation linéaire
  float kq = 1.0 / (light_range * light_range); // facteur d'atténuation quadratique

  // calculer l'atténuation
  float k = 1.0 / (kc + kl * d + kq * d * d);

  // appliquer l'atténuation à la couleur diffuse et spéculaire
  vec3 result = k * (color_ambient + color_diffuse + color_specular);

  // calculer la couleur du fragment
  fragment_color = vec4( result, 1.0);
}
