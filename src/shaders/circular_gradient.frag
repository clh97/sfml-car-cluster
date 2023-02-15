uniform vec2 center;
uniform float radius;
uniform vec4 innerColor;
uniform vec4 outerColor;

void main()
{
    vec2 position = gl_FragCoord.xy - center;
    float distance = length(position);

    if (distance < radius)
    {
        float t = distance / radius;
        vec4 color = mix(innerColor, outerColor, t);
        gl_FragColor = color;
    }
    else
    {
        discard;
    }
}
