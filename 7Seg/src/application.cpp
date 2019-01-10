#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGL/renderer.h"
#include "OpenGL/vertexBuffer.h"
#include "OpenGL/indexBuffer.h"
#include "OpenGL/vertexArray.h"
#include "OpenGL/shader.h"
//#include "texture.h"

#include "display.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 320, "Seven Segment", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK)
		std::cout << "ERROR!" << std::endl;

	SegDisplay disp;

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		int num = 0;
		/* Loop until the user closes the window */
		while(!glfwWindowShouldClose(window))
		{
			disp.renderDisplay();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}