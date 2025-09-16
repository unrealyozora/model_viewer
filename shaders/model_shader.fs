#version 330 core

const int MAX_POINT_LIGHTS = 10;
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float quadratic;
    float linear;
    float constant;
};

struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform vec3 viewPos;

vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    //for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
    //   result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    //}
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient = dirLight.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = dirLight.specular * spec * vec3(texture(texture_specular1, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 ambient = pointLight.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = pointLight.specular * spec * vec3(texture(texture_specular1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
