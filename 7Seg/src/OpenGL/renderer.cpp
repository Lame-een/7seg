#include "renderer.h"
#include <iostream>
#include <string>

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.bind();

	//shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

	va.bind();
	ib.bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}