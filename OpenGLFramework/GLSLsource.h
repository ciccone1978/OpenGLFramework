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


static const char* vs01 =
R"glsl(
	#version 330 core
	layout(location = 0) in vec4 aPos;
	layout(location = 1) in vec4 aCol;
	uniform mat4 transform;
	out vec4 theColor;
	void main()
	{
		gl_Position = transform * aPos;
		theColor = aCol;
	}
)glsl";

static const char* fs01 =
R"glsl(
	#version 330 core
	out vec4 color;
	in vec4 theColor;
	void main()
	{
		color = theColor;
	}
)glsl";