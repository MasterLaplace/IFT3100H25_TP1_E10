// tessellation control shader
#version 410 core

layout(vertices = 3) out;  // On travaille avec des triangles

void main() {
    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = 5.0;  // Nombre de subdivisions des bords
        gl_TessLevelOuter[1] = 5.0;
        gl_TessLevelOuter[2] = 5.0;
        gl_TessLevelInner[0] = 5.0;  // Nombre de subdivisions internes
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
