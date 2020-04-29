// Simple Fragment Shader
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

in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform Light light;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewDir;

void main()
{
    // Ambient light
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse light
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 diffuse = max(dot(lightDir, Normal), 0.0) * material.diffuse;
    diffuse =  light.diffuse * (diffuse);

    // Specular light
    vec3 reflectDir = reflect(lightDir, Normal);
    vec3 specular = vec3(pow(max(dot(reflectDir, viewDir), 0.0), material.shininess));
    specular = light.specular * (specular * material.specular);

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}