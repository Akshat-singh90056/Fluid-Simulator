#version 330 core
out vec4 FragColor;


void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5);
    if(length(coord) <= 0.5)
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        discard;
}

