#version 120  // Replace with the appropriate version for your needs

uniform float u_time;        // Time variable for animation
uniform vec2 u_mousePos;     // Mouse Position

void main()
{
    // Offset value
    float offset = 100.0;

    // Original vertex position
    vec4 originalPosition = gl_Vertex;
    
    // Offset the vertex position
    vec4 offsetPosition = originalPosition + vec4(offset, offset, 0.0, 0.0);

    float amplitude = 5.0;
    float frequency = 10.0;

    offsetPosition.y += sin(offsetPosition.x + u_time * frequency) * amplitude;


    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * offsetPosition;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;



    // forward the vertex color
    gl_FrontColor = gl_Color;
}