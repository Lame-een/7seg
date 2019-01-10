#pragma once
#include "errHandle.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void bind() const;
	void unbind() const;
	void addBuffer(const void * data, unsigned int size);
};
