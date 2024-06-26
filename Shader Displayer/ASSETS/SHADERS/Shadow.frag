precision mediump float;

uniform float u_time;
uniform sampler2D u_texture;

void main() 
{
    // Set starting color
    vec3 color = vec3(0.85, 0.09, 0.09);

    // Check for transparency
    if (texture2D(u_texture, gl_TexCoord[0].xy).a < 0.1) // This is correct
    {
        discard; // Remove transparent pixels
    }
    
    // Example animation or effects based on time or coordinates
    color *= 0.5 + 0.5 * sin(u_time);

    // Output to screen
    gl_FragColor = vec4(color, 0.5);
}