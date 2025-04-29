#version 330

in vec3 surface_position;
in vec3 surface_normal;

out vec4 fragment_color;

uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;
uniform vec3 material_color_specular;

uniform float brightness;

uniform vec3 light_position;
uniform vec3 light_color_ambient;
uniform vec3 light_color_diffuse;
uniform vec3 light_color_specular;

// J'ai mis une valeur par défaut, mais ça pourrait être modifiable par l'application si on veut
uniform float band_threshold_1 = 0.3;
uniform float band_threshold_2 = 0.6;
uniform float edge_thickness = 0.01;
uniform float specular_threshold = 0.7;

// Function to quantize the lighting into discrete bands
float toonify(float value) {
    if (value < band_threshold_1) {
        return 0.2; // Darkest band
    } else if (value < band_threshold_2) {
        return 0.6; // Middle band
    } else {
        return 1.0; // Brightest band
    }
}

void main()
{
    // re-normaliser la normale après interpolation
    vec3 n = normalize(surface_normal);

    // calculer la direction de la surface vers la lumière (l)
    vec3 l = normalize(light_position - surface_position);

    // calculer la couleur ambiante
    vec3 color_ambient = light_color_ambient * material_color_ambient;

    // calculer le niveau de réflexion diffuse (n • l)
    float reflection_diffuse = max(dot(n, l), 0.0);
    
    // la couleur de la diffuse est "step" pour avoir l'effet toon
    float toon_diffuse = toonify(reflection_diffuse);
    
    // calculer la couleur diffuse (avec la couleur toon)
    vec3 color_diffuse = light_color_diffuse * material_color_diffuse * toon_diffuse;

    // calculer la direction de la surface vers la caméra (v)
    vec3 v = normalize(-surface_position);

    // calculer la direction du demi-vecteur de réflection (h) en fonction du vecteur de vue (v) et de lumière (l)
    vec3 h = normalize(v + l);

    // calculer le niveau de réflexion spéculaire (n • h)
    float reflection_specular = pow(max(dot(n, h), 0.0), brightness);
    
    // on calcule la couleur du spéculaire en fonction du treshold comme pour la diffuse 
    float toon_specular = step(specular_threshold, reflection_specular);
    
    // calculer la couleur speculaire
    vec3 color_specular = light_color_specular * material_color_specular * toon_specular;

    // calcule de la couleur de fragment final
    vec3 final_color = color_ambient + color_diffuse + color_specular;
    
    // on output la couleur
    fragment_color = vec4(final_color, 1.0);
}