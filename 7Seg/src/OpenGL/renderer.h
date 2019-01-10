#pragma once
#include <GL/glew.h>
#include "errHandle.h"
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};