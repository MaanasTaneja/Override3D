#pragma once
#include "CVertexBuffer.h"

namespace Override
{
	class CMesh
	{
	private:
		unsigned int m_ebo;
	public:
		CVertexBuffer* m_buffer;
		std::vector<Vertex> m_raw;
		std::vector<unsigned int> m_indices;

		void bindbuffer() { glBindBuffer(GL_ARRAY_BUFFER, m_buffer->getBufferID()); }
		void bindvertexarray() { glBindVertexArray(m_buffer->getVAO()); }
		void bindelementbuffer() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo); }

		virtual void build() { m_buffer->generate(m_raw); }

		void modifymesh(std::vector<Vertex>& extra) {
			m_raw.insert(m_raw.end(), extra.begin(), extra.end());
			build();
		}

		void addIndices(const std::vector<unsigned int>& indices)
		{
			m_indices = indices;
			glGenBuffers(1, &m_ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		std::vector<Vertex> spewVertices() { return m_raw; }
		unsigned int vertexcount() { return static_cast<unsigned int>(m_raw.size()); }

		CMesh(std::vector<Vertex> verts) : m_raw{ verts }, m_indices{  }, m_ebo{ 0 } {
			m_buffer = new CVertexBuffer();
			build();
		}

		CMesh() : m_raw{}, m_indices{}, m_ebo{ 0 } { m_buffer = new CVertexBuffer(); }

		virtual ~CMesh() = default;
		virtual void setrawmeshdata(std::vector<Vertex> verts) { m_raw = verts; }
	};
}
