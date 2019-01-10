#pragma once
#include "OpenGL/renderer.h"
#include "OpenGL/vertexBuffer.h"
#include "OpenGL/indexBuffer.h"
#include "OpenGL/vertexArray.h"
#include "OpenGL/shader.h"
#include "sevenSegment.h"

#include "../res/shaders/builtShader.h"

//#include<thread>
#include<ctime>

class SegDisplay
{
public:
	float sizeMod = 3.0f;
	float pxSize = (16.0f / 592) / sizeMod;
	float xOffset = -1.0f * (45 * 2 * pxSize + 10 * pxSize);
	float yOffset = (-2.0f / sizeMod);

	float x[10] = {0.0f + xOffset, 5 * pxSize + xOffset, 6 * pxSize + xOffset, 10 * pxSize + xOffset, 11 * pxSize + xOffset, 31 * pxSize + xOffset, 32 * pxSize + xOffset, 36 * pxSize + xOffset, 37 * pxSize + xOffset, 42 * pxSize + xOffset};
	float y[17] = {0.0f + yOffset, 5 * pxSize * 2 + yOffset, 6 * pxSize * 2 + yOffset, 10 * pxSize * 2 + yOffset, 11 * pxSize * 2 + yOffset, 31 * pxSize * 2 + yOffset, 32 * pxSize * 2 + yOffset, 36 * pxSize * 2 + yOffset, 37 * pxSize * 2 + yOffset, 38 * pxSize * 2 + yOffset, 
				 42 * pxSize * 2 + yOffset, 43 * pxSize * 2 + yOffset, 63 * pxSize * 2 + yOffset, 64 * pxSize * 2 + yOffset, 68 * pxSize * 2 + yOffset, 69 * pxSize * 2 + yOffset, 74 * pxSize * 2 + yOffset};
	
	float positionsHourTens[84] = {
				x[2], y[15],
				x[4], y[16],
				x[4], y[13],
				x[7], y[15],
				x[5], y[16],
				x[5], y[13],
				x[8], y[14],
				x[6], y[12],
				x[9], y[12],
				x[8], y[9],
				x[6], y[11], //10
				x[9], y[11],
				x[8], y[7],
				x[6], y[5],
				x[9], y[5],
				x[8], y[2],
				x[6], y[4],
				x[9], y[4],
				x[7], y[1],
				x[5], y[3],
				x[5], y[0], //20
				x[2], y[1],
				x[4], y[3],
				x[4], y[0],
				x[1], y[2],
				x[0], y[4],
				x[3], y[4],
				x[1], y[7],
				x[0], y[5],
				x[3], y[5],
				x[1], y[9], //30
				x[0], y[11],
				x[3], y[11],
				x[1], y[14],
				x[0], y[12],
				x[3], y[12],
				x[2], y[8],
				x[4], y[10],
				x[4], y[6],
				x[7], y[8],
				x[5], y[10], //40
				x[5], y[6]
	};

	float positionsHourOnes[84];
	float positionsMinuteTens[84];
	float positionsMinuteOnes[84];

	float semicolon[16] = {
		-1.0f * pxSize * 5, 18 * pxSize * 2,
		pxSize * 5, 18 * pxSize * 2,
		-1.0f * pxSize * 5, 10 * pxSize * 2,
		pxSize * 5, 10 * pxSize * 2,

		-1.0f * pxSize * 5, -18 * pxSize * 2,
		pxSize * 5, -18 * pxSize * 2,
		-1.0f * pxSize * 5, -10 * pxSize * 2,
		pxSize * 5, -10 * pxSize * 2,
	};

	unsigned int semicolonIndex[12] = {
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7
	};

	int hour = 0;
	int minute = 0;

	int semiCounter = 0;

	unsigned int indicies[128];
	unsigned int iboSize = 0;
	VertexBufferLayout layout;
	VertexArray va;
	VertexBuffer vb[4];
	VertexBuffer semicolonVB;
	Shader colorShader;
	Shader BGShader;
	Renderer renderer;

	void renderSingle(VertexBuffer& vb);
	void renderSemicolon();
	void renderBG();
public:
	SegDisplay()
	{
		BGShader.addPBShader(PREBUILTSHADER::shader);
		colorShader.addPBShader(PREBUILTSHADER::shader);

		BGShader.bind();
		BGShader.setUniform4f("u_Color", 0.20f, 0.0f, 0.0f, 1.0f);
		colorShader.bind();
		colorShader.setUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

		layout.push<float>(2);
		for(int i = 0, j = 1; i < 84; i += 2, j += 2)
		{
			positionsHourOnes[i] = positionsHourTens[i] + 45 * pxSize;
			positionsMinuteTens[i] = positionsHourTens[i] + 45 * pxSize * 2 + 24 * pxSize;
			positionsMinuteOnes[i] = positionsHourTens[i] + 45 * pxSize * 3 + 24 * pxSize;
			
			positionsHourOnes[j] = positionsHourTens[j];
			positionsMinuteOnes[j] = positionsHourTens[j];
			positionsMinuteTens[j] = positionsHourTens[j];
		}

		vb[0].addBuffer(positionsHourTens, 42 * 2 * sizeof(float));
		vb[1].addBuffer(positionsHourOnes, 42 * 2 * sizeof(float));
		vb[2].addBuffer(positionsMinuteTens, 42 * 2 * sizeof(float));
		vb[3].addBuffer(positionsMinuteOnes, 42 * 2 * sizeof(float));
		semicolonVB.addBuffer(semicolon, 8 * 2 * sizeof(float));
	}


	void renderDisplay();
	void getTime();
};