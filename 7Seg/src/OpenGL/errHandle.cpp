#include "errHandle.h"

void GLClearError()
{
	//while(glGetError() != GL_NO_ERROR);
	while(glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while(GLenum error = glGetError())
	{
		std::string errType;
		switch(error)
		{
			case 0x0500: errType = "GL_INVALID_ENUM";
				break;
			case 0x0501: errType = "GL_INVALID_VALUE";
				break;
			case 0x0502: errType = "GL_INVALID_OPERATION";
				break;
			case 0x0503: errType = "GL_STACK_OVERFLOW";
				break;
			case 0x0504: errType = "GL_STACK_UNDERFLOW";
				break;
			case 0x0505: errType = "GL_OUT_OF_MEMORY";
				break;

		}
		std::cout << "[OpenGl error] (" << error << ") " << errType << " " << function << "\n\t" << file << " " << line << std::endl;

		return false;
	}

	return true;
}