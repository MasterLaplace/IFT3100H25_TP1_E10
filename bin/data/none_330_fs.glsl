// IFT3100H24 ~ tone_mapping_330_fs.glsl

#version 330

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

// attributs uniformes
uniform sampler2D image;
uniform float exposure;
uniform float gamma;

void main()
{
  // variable qui va contenir la couleur à corriger
  vec3 color;

  // échantillonner la texture
  vec3 texture_sample = texture(image, surface_texcoord).rgb;

  // valeur initiale de la couleur
  color = texture_sample;

  // conversion de la couleur de l'espace gamma vers l'espace linéaire
  color = pow(color, vec3(gamma));

  // ajustement de l'exposition
  color = vec3(1.0) - exp(-color * exposure);

  // conversion de couleur de l'espace linéaire vers l'espace gamma
  color = pow(color, vec3(1.0 / gamma));

  // couleur du fragment
  fragment_color = vec4(color, 1.0);
}
