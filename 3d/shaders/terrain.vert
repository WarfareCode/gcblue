

varying vec3 lightDir, normal;
varying vec3 position;

void main(void)
{
    normal = normalize(gl_NormalMatrix * gl_Normal);
    lightDir = normalize(vec3(gl_LightSource[0].position));
    position = vec3(gl_Vertex);

    gl_TexCoord[0] = gl_MultiTexCoord0;

    gl_Position = ftransform();
}

