#pragma once
#include <vector>
#include <iostream>
#include "CMesh.h"
#include "Shader.h"  // here i have to refactor that material provides this data, but rn i just wanna get something on the screen for testing purposes will implement later

//IRENDERER WILL TAKE IRENDERABLES ONLY AND EXTRACT DATA FROM THERE THIS IS ALL TEMPORARY
class IRenderer  //interface is incomplete as of now
{
public:
	//virtual void drawMesh(IMesh* mesh, Shader* shader) = 0;
};