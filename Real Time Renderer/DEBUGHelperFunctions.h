#pragma once
#include <iostream>
#include <vector>
#include "CRenderable.h"

namespace DebugHelperToolkit
{
	std::vector<Override::Vertex> pack2vertices(float* positions, float* textureuvs, float* normals, int vertexcount);
	std::vector<Override::Vertex> pack2vertices(std::vector<float> positions, std::vector<float> textureuvs, std::vector<float> normals);
	std::vector<Override::Vertex> pack2vertices(float* data, int vertexcount);

	std::vector<Override::Vertex> pack2vertices_nonormal(float* data, int vertexcount);
}