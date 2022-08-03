#pragma once
#include <iostream>
#include <vector>

#define BUFFER_SIZE sizeof(Vertex)

struct Vertex		//to rename to Vertex3p2t3n (3 pos 2 tex 3 pos normal
{
	float position[3];
	float uv[2];
	float normal[3];
};

//then i can have other vertex structs for different buffers called 
//Vertex3p2t3n3b the b for bone weights and stuff

class IVertexBuffer
{
private:
	virtual void packdata(std::vector<float>& position, std::vector<float>& uv, std::vector<float>& normal, int nVerts) = 0;
	virtual void uploaddata() = 0;
	virtual void formatdata() = 0;
public:
	virtual void generate(std::vector<Vertex>& vAttribs) = 0;
	virtual unsigned int getBufferID() = 0;
	virtual void getbufferdata(void* storage) = 0;
};