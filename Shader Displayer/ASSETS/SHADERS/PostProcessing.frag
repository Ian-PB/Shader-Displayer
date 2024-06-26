precision mediump float;

uniform float u_time;
uniform sampler2D u_texture;

void main() 
{
    // Set starting color
    vec4 image = texture2D(u_texture, gl_TexCoord[0].xy);

    // Check for transparency
    if (texture2D(u_texture, gl_TexCoord[0].xy).a < 0.1) // This is correct
    {
        discard; // Remove transparent pixels
    }
    
    // Change images rgba
    image += sin(gl_TexCoord[0].x * 90.0 + u_time);
    image += cos(gl_TexCoord[0].y * 90.0 + u_time);

    image.r += sin(gl_TexCoord[0].x + u_time * 2.0);
    image.g += cos(gl_TexCoord[0].x + u_time);
    image.b += sin(gl_TexCoord[0].x + u_time);

    // Output to screen
    gl_FragColor = vec4(image); 

    // Image is the new "color" of fragment shaders if im working with editing an existing sprite
}