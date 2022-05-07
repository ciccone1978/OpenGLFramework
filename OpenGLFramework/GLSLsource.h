//
//Vertex shader in GLSL
//
static const char* vsSource =
R"glsl(
	#version 330 core
	layout(location = 0) in vec4 aPos;
	layout(location = 1) in vec2 aTex;
	out vec2 texCoord;
	uniform mat4 mvp;
	void main()
	{
		gl_Position = mvp * aPos;
		texCoord = aTex;
	}
)glsl";

//
//Fragment shader in GLSL
//
static const char* fsSource =
R"glsl(
	#version 330 core
	in vec2 texCoord;
	uniform sampler2D myTex;
	out vec4 color;
	void main()
	{
		color = texture(myTex, texCoord);
	}
)glsl";
