#version 330 core
struct Material
{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
};

in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	vec3 norm = normalize(Normal);
    vec3 ambient  = vec3(texture(material.texture_diffuse, TexCoords));
	vec3 diffuse  = vec3(texture(material.texture_diffuse, TexCoords));  
	vec3 specular = vec3(texture(material.texture_specular, TexCoords));
	FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}