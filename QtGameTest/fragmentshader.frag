#version 330 core

in vec2 v_texCoord;
out vec4 color;
uniform sampler2D s_texture;

void
main() {
    // Output color = color of the texture at the specified v_texCoord
    color = texture2D(s_texture, v_texCoord);
}
