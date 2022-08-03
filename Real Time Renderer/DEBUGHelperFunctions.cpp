#include "DEBUGHelperFunctions.h"

namespace DebugHelperToolkit
{
	//Less used
	std::vector<Override::Vertex> DebugHelperToolkit::pack2vertices(float* positions, float* textureuvs, float* normals, int vertexcount)
	{
		std::vector<Override::Vertex> list;

		int pos = 0, tex = 0, norm = 0;

		for (int i = 0; i < vertexcount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				list.at(i).position[j] = positions[pos];
				pos++;
			}

			for (int k = 0; k < 2; k++)
			{
				list.at(i).uv[k] = textureuvs[tex];
				tex++;
			}

			for (int l = 0; l < 3; l++)
			{
				list.at(i).normal[l] = normals[tex];
				norm++;
			}
			
		}

		return list;
	}
	std::vector<Override::Vertex> DebugHelperToolkit::pack2vertices(std::vector<float> positions, std::vector<float> textureuvs, std::vector<float> normals)
	{
		std::vector<Override::Vertex> list;
		int vertexcount = static_cast<int>(positions.size());

		int pos = 0, tex = 0, norm = 0;

		for (int i = 0; i < vertexcount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				list.at(i).position[j] = positions[pos];
				pos++;
			}

			for (int k = 0; k < 2; k++)
			{
				list.at(i).uv[k] = textureuvs[tex];
				tex++;
			}

			for (int l = 0; l < 3; l++)
			{
				list.at(i).normal[l] = normals[tex];
				norm++;
			}

		}

		return list;
	}


	std::vector<Override::Vertex> DebugHelperToolkit::pack2vertices_nonormal(float* data, int vertexcount)
	{
		std::vector<Override::Vertex> list;

		int ptr = 0, tex = 0, norm = 0;

		for (int i = 0; i < vertexcount; i++)
		{
			Override::Vertex vert;
			vert.position[0] = data[ptr];
			vert.position[1] = data[++ptr];
			vert.position[2] = data[++ptr];

			vert.uv[0] = data[++ptr];
			vert.uv[1] = data[++ptr];

			ptr++;
			list.push_back(vert);
		}

		return list;
	}

	std::vector<Override::Vertex> DebugHelperToolkit::pack2vertices(float* data, int vertexcount)
	{
		std::vector<Override::Vertex> list;

		int ptr = 0, tex = 0, norm = 0;

		for (int i = 0; i < vertexcount; i++)
		{
			Override::Vertex vert;
			vert.position[0] = data[ptr];
			vert.position[1] = data[++ptr];
			vert.position[2] = data[++ptr];

			vert.normal[0] = data[++ptr];
			vert.normal[1] = data[++ptr];
			vert.normal[2] = data[++ptr];

			vert.uv[0] = data[++ptr];
			vert.uv[1] = data[++ptr];

			ptr++;
			list.push_back(vert);
		}

		return list;
	}





}