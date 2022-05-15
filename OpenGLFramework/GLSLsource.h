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
	layout(location = 0) in vec4 aPos;
	uniform mat4 mvp;
	void main()
	{
		gl_Position = mvp * aPos;
	}
)glsl";

//Cube Fragment shader
static const char* cubeFragmentShaderSource =
R"glsl(
	#version 330 core
	out vec4 fragColor;
	uniform vec4 objectColor;
	uniform vec4 lightColor;
	void main()
	{
		float ambientFactor = 0.1f;
		vec4 ambientColor = ambientFactor * lightColor;
		fragColor = ambientColor * objectColor;
	}
)glsl";

//Light Source Fragment shader
static const char* lightFragmentShaderSource =
R"glsl(
	#version 330 core
	out vec4 fragColor;
	void main()
	{
		fragColor = vec4(1.0f);
	}
)glsl";