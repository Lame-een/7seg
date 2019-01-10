#pragma once
#include <string>

namespace PREBUILTSHADER
{
	const std::string shader = 
		"#shader vertex \n"
		"#version 330 core \n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"out vec2 v_TexCoord;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"};\n"
		"\n"
		"#shader fragment\n"
		"#version 330 core\n"
		"\n"
		"	layout(location = 0) out vec4 color;\n"
		"uniform vec4 u_Color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = u_Color;\n"
		"}";
}