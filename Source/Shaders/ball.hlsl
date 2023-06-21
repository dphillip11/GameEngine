#version 330
out vec4 FragColor;
in vec4 colorGS;
in vec3 centre;
in vec3 worldPos;

uniform vec3 viewPos;
int shininess = 50;
vec3 lightPos = vec3(0, 100, -200);

void main()
{
	vec3 normal = normalize(worldPos - centre);
	//allignment with direction o
	float diffuseValue = (1 + dot(normal, normalize(lightPos - worldPos))) * 0.5f;

	vec3 lightDir = normalize(lightPos - worldPos);
	//specular component
	vec3 viewDir = normalize(viewPos - worldPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), shininess);


	FragColor = (diffuseValue + specularValue + 0.1f) * colorGS;
}