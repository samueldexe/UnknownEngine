
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoord;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform sampler2D texture1;

void main()
{
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(LightPos - FragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular light
    float specularStrength = 0.5;
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);
}