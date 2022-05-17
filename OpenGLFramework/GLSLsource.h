static const char* vsDemo =
R"glsl(
	#version 330 core
	layout(location = 0) in vec4 position;
	void main()
	{
		gl_Position = position;
	}
)glsl";

//Fragment shader in GLSL
static const char* fsDemo =
R"glsl(
	#version 330 core
	out vec4 color;
	void main()
	{
		color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)glsl";


//Vertex shader
static const char* vertexShaderSource =
R"glsl(
	#version 330 core
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	out vec3 normal;
	out vec3 fragPos;

	void main()
	{
		fragPos = vec3(model * vec4(aPos, 1.0));
		normal = aNormal;
		gl_Position = projection * view * vec4(fragPos, 1.0);
	}
)glsl";

//Cube Fragment shader
static const char* cubeFragmentShaderSource =
R"glsl(
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
)glsl";

//Light Source Fragment shader
static const char* lightFragmentShaderSource =
R"glsl(
	#version 330 core
	out vec4 fragColor;
	uniform vec3 lightColor;
	void main()
	{
		fragColor = vec4(lightColor, 1.0f);
	}
)glsl";