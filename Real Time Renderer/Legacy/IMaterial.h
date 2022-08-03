#pragma once
#include "globals.h"
#include "Shader.h"
#include "CTexture.h"

struct Maps_phong
{
	CTexture diffuse;
	CTexture specular;
};

struct Maps_pbr
{
	CTexture albedo;
	CTexture normal;
	CTexture metallic;
	CTexture roughness;
};

class IMaterial
{
private:

public:
	virtual void setshader(Shader* replace) = 0;
	virtual void textureload_phong() = 0;			//mutually exclusive functions 
	virtual void textureload_pbr() = 0;

	virtual int getmaterialspec() = 0;		//pbr requires different passes, so if material is using a pbr shader, we must know about it 
	virtual void setmaterialspec(Globals::materialspec set) = 0;

	virtual void applymaterial() = 0;
};