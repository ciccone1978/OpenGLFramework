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
	out vec4 color;
	uniform vec4 cubeColor;
	uniform vec4 lightSourceColor;
	void main()
	{
		color = cubeColor * lightSourceColor;
	}
)glsl";

//Light Source Fragment shader
static const char* lightFragmentShaderSource =
R"glsl(
	#version 330 core
	out vec4 color;
	void main()
	{
		color = vec4(1.0f);
	}
)glsl";