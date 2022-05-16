#version 330 core
out vec4 fragColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 normal;
in vec3 fragPos;
void main()
{
	//
	//Phong lighting model
	//

	//ambient light
	float ambientFactor = 0.1f;
	vec3 ambient = ambientFactor * lightColor;

	//diffuse light
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diffuseAngle = max(dot(norm, lightDir), 0.0);	
	vec3 diffuse = diffuseAngle * lightColor;

	//specular light
	float specularFactor = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 specular = specularFactor * spec * lightColor; 

	fragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0);
}