#include "CVertexBuffer.h"

namespace Override
{
	void CVertexBuffer::packdata(std::vector<float>& position, std::vector<float>& uv, std::vector<float>& normal, int nVerts)
	{
		//Assuming vertices array has triplets of position data and UV array has duplets, and normals triplets again

		int pos = 0, tex = 0, norm = 0;

		for (int i = 0; i < nVerts; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m_packed.push_back(position.at(pos));
				pos++;
			}

			for (int k = 0; k < 2; k++)
			{
				m_packed.push_back(uv.at(tex));
				tex++;
			}

			for (int l = 0; l < 3; l++)
			{
				m_packed.push_back(normal.at(norm));
				norm++;
			}
		}
	}

	void CVertexBuffer::uploaddata()
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, m_packed.size() * sizeof(float), m_packed.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	void CVertexBuffer::formatdata()
	{
		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, BUFFER_SIZE, reinterpret_cast<void*>(0));		//Informing OpenGL that the position data must be first attribute, to get to next position data,

																						//you must stride over BUFFER_SIZE and that in the array, intital position offest is 0 (first place)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, BUFFER_SIZE, reinterpret_cast<void*>(3 * sizeof(float)));	//Initial position is after position data (3 floats) so thats our offset.

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, BUFFER_SIZE, reinterpret_cast<void*>(5 * sizeof(float)));


		glBindVertexArray(0);

	}

	void CVertexBuffer::generate(std::vector<Vertex>& vAtrribs)
	{
		for (const auto& vertex : vAtrribs)
		{
			m_rawposition.push_back(vertex.position[0]);
			m_rawposition.push_back(vertex.position[1]);
			m_rawposition.push_back(vertex.position[2]);

			m_rawuv.push_back(vertex.uv[0]);
			m_rawuv.push_back(vertex.uv[1]);

			m_rawnormal.push_back(vertex.normal[0]);
			m_rawnormal.push_back(vertex.normal[1]);
			m_rawnormal.push_back(vertex.normal[2]);

			m_vertexcount++;
		}

		packdata(m_rawposition, m_rawuv, m_rawnormal, m_vertexcount);
		uploaddata();
		formatdata();
	}
}

// DATA REPRESENTATION
// P1 P2 P3 U V N1 N2 N3