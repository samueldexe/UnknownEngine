
#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Light light;
uniform Material material;
uniform sampler2D texture1;

void main()
{
    // Ambient light
    vec3 ambient = light.ambient * material.ambient;       

    // Diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos); 
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse); 

    // Specular light
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
    vec3 specular = light.specular * spec * material.specular;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}