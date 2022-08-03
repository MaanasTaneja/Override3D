#pragma once
#include <iostream>
#include <vector>
#include "IVertexBuffer.h"

class IMesh
{
public:
	//This interface merely exists as a template, for other mesh components to follow
	virtual void bindbuffer() = 0;
	virtual void bindvertexarray() = 0;

	virtual void build() = 0;

	virtual std::vector<Vertex> spewVertices() = 0;
	virtual unsigned int vertexcount() = 0;

};