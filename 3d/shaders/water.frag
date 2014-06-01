


varying vec3 lightDir, normal;
uniform sampler2D water1tex;
uniform sampler2D water2tex;
uniform float Sine;

void main (void)
{

    vec3 ct,cf;
    float intensity,at,af;
    float alpha = abs(Sine);

    vec4 color = alpha * texture2D(water1tex, gl_TexCoord[0].st) + 
                 (1.0 - alpha) * texture2D(water2tex, gl_TexCoord[0].st);

    intensity = max(dot(lightDir,normalize(normal)), 0.0);
    cf = intensity * (gl_FrontMaterial.diffuse).rgb + 
						  gl_FrontMaterial.ambient.rgb;
    af = gl_FrontMaterial.diffuse.a;

    ct = color.rgb;
    at = color.a;

    gl_FragColor = vec4(ct * cf, 1.0);


}
