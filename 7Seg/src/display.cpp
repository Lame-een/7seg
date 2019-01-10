#include "display.h"

void SegDisplay::renderDisplay()
{
	renderer.clear();

	renderBG();

	getTime();
	SevSeg::retIBO(indicies, iboSize, hour / 10);
	renderSingle(vb[0]);
	SevSeg::retIBO(indicies, iboSize, hour % 10);
	renderSingle(vb[1]);
	SevSeg::retIBO(indicies, iboSize, minute / 10);
	renderSingle(vb[2]);
	SevSeg::retIBO(indicies, iboSize, minute % 10);
	renderSingle(vb[3]);
	
	renderSemicolon();
}

void SegDisplay::renderSemicolon()
{
	IndexBuffer IBO(semicolonIndex, 12);
	va.addBuffer(semicolonVB, layout);
	
	if(semiCounter < 60)
	{
		renderer.draw(va, IBO, colorShader);
	}
	else if(semiCounter < 120)
	{
		renderer.draw(va, IBO, BGShader);
	}
	else if(semiCounter > 120)
	{
		semiCounter = 0;
	}
	
	semiCounter++;
}

void SegDisplay::renderBG()
{
	SevSeg::retIBO(indicies, iboSize, 8);
	IndexBuffer IBO(indicies, iboSize);

	va.addBuffer(vb[0], layout);
	renderer.draw(va, IBO, BGShader);
	va.addBuffer(vb[1], layout);
	renderer.draw(va, IBO, BGShader);
	va.addBuffer(vb[2], layout);
	renderer.draw(va, IBO, BGShader);
	va.addBuffer(vb[3], layout);
	renderer.draw(va, IBO, BGShader);

	IndexBuffer IBOSemi(semicolonIndex, 12);
	va.addBuffer(semicolonVB, layout);
	renderer.draw(va, IBOSemi, BGShader);
}

void SegDisplay::renderSingle(VertexBuffer& vb)
{
	IndexBuffer IBO(indicies, iboSize);
	va.addBuffer(vb, layout);
	renderer.draw(va, IBO, colorShader);
}

void SegDisplay::getTime()
{
	std::time_t dura = std::time(nullptr);
	std::tm calTime;
	localtime_s(&calTime, &dura);

	hour = calTime.tm_hour;
	minute = calTime.tm_min;
}
