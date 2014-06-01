


varying vec3 lightDir, normal;
varying vec3 position;

uniform sampler2D coastTex;
uniform sampler2D sandTex;
uniform sampler2D grassTex;
uniform sampler2D mountainTex;


void main (void)
{

    vec3 ct,cf;
    float intensity,at,af;
    float alpha;
    vec4 color;
    const float b1 = 1.0 / 40.0;
    const float b2 = 1.0 / 15.0;
    const float b3 = 1.0 / 10.0;
    const float b4 = 1.0 / 40.0;


    float z = position.z;

    if (z < -60.0)
    {
        color = texture2D(mountainTex, gl_TexCoord[0].st);
    }
    else if (z < -20.0)
    {
        alpha = b1 * (z + 60.0);

        color = (1.0-alpha) * texture2D(mountainTex, gl_TexCoord[0].st) +
                   alpha * texture2D(coastTex, gl_TexCoord[0].st);
    }
    else if (z < -15.0)
    {
        color = texture2D(coastTex, gl_TexCoord[0].st);
    }
    else if (z < 0.0)
    {
        alpha = b2 * (z + 15.0);
        color = (1.0-alpha) * texture2D(coastTex, gl_TexCoord[0].st) +
                   alpha * texture2D(sandTex, gl_TexCoord[0].st);
    }
    else if (z < 5.0)
    {
        color = texture2D(sandTex, gl_TexCoord[0].st);
    }
    else if (z < 15.0)
    {
        alpha = b3 * (z - 5.0);
        color = (1.0-alpha) * texture2D(sandTex, gl_TexCoord[0].st) +
                   alpha * texture2D(grassTex, gl_TexCoord[0].st);
    }
    else if (z < 60.0)
    {
        color = texture2D(grassTex, gl_TexCoord[0].st);
    }
    else if (z < 100.0)
    {
        alpha = b4 * (z - 60.0);
        color = (1.0-alpha) * texture2D(grassTex, gl_TexCoord[0].st) +
                   alpha * texture2D(mountainTex, gl_TexCoord[0].st);
    }
    else
    {
        color = texture2D(mountainTex, gl_TexCoord[0].st);
    }



    intensity = max(dot(lightDir,normalize(normal)), 0.0);
    cf = intensity * (gl_FrontMaterial.diffuse).rgb + 
						  gl_FrontMaterial.ambient.rgb;
    af = gl_FrontMaterial.diffuse.a;

    ct = color.rgb;
    at = color.a;

    gl_FragColor = vec4(ct * cf, 1.0);

}
