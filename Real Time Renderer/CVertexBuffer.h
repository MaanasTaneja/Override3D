#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#define BUFFER_SIZE sizeof(Vertex)

/*
__________________________________________________________________________________________________________________________________________________________________________________________________________
CVertexBuffer is used to store static (unchanging and simple opaque meshes without complex passes) data. Therefore, it is a prime candidate for batching large amounts of data.
I can, in theory, dump vertex data of mutliple meshes and models into one buffer and load everything into the GPU at once.
_________________________________________________________________________________________________________________________________________________________________________________________________________
*/

namespace Override
{

	struct Vertex		//to rename to Vertex3p2t3n (3 pos 2 tex 3 pos normal
	{
		float position[3];
		float uv[2];
		float normal[3];
	};

	//then i can have other vertex structs for different buffers called 
	//Vertex3p2t3n3b the b for bone weights and stuff


	class CVertexBuffer
	{
	private:
		unsigned int m_vbo;
		unsigned int m_vao;
		std::vector<float> m_packed;

		std::vector<float> m_rawposition;
		std::vector<float> m_rawuv;
		std::vector<float> m_rawnormal;
		long m_vertexcount = 0;

		virtual void packdata(std::vector<float>& position, std::vector<float>& uv, std::vector<float>& normal, int nVerts);
		virtual void formatdata();
		void uploaddata();

	public:
		CVertexBuffer() :m_vbo{ 0 }, m_vao{ 0 } {}
		virtual ~CVertexBuffer() = default;
		void getbufferdata(void* storage) { glGetBufferSubData(GL_ARRAY_BUFFER, 0, BUFFER_SIZE, storage); }  //Probably broken

		virtual void generate(std::vector<Vertex>& vAttribs);

		unsigned int getBufferID() { return m_vbo; }
		unsigned int getVAO() { return m_vao; }

		std::vector<float> spew() {			//Spit out packed data 
			if (!m_packed.empty())
				return m_packed;
		}

		void append(std::vector<Vertex>& vAttribs);			//To draw two meshes with one draw call. (Add any other data to render) 
		void pop(int startIndex, int endINdex);

	};

}