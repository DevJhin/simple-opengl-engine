#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float range;    

    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 


#define NR_POINT_LIGHTS 1


uniform vec3 viewPos;

//Light Data
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform Material material;


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 color, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform vec4 Times;
uniform vec4 SinTimes;
uniform vec4 CosTimes;
uniform vec4 DeltaTimes;

uniform vec4 tintColor;

void main()
{    
    vec3 mainColor = vec3( texture( material.diffuse, TexCoords + vec2(Times.x, Times.x)));
    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight,mainColor, norm, viewDir);
    
// point lights
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
        //result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
   
    FragColor =  vec4(result, 1.0) + tintColor;
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 color, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * color;
    vec3 diffuse = light.diffuse * diff *  color;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

