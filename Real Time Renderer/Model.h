#pragma once
#include <iostream>
#include <vector>
#include "CRenderable.h"
#include "RenderableList.h"

#include <assimp/include/assimp/Importer.hpp>
#include <assimp/include/assimp/scene.h>
#include <assimp/include/assimp/postprocess.h>

//Renderable builder is the model loader/direct renderable maker using raw data etc/ (all functions that can make renderables or a list of renderables should be here?) for this rendering engine 

//Rn it just loads all renderables on the same level. But when i advnace further ill also make a scene heriacrhy thing, and here while loading all node childrens will be specifed 
//as child renderables 

namespace Override
{
	class Model : public RenderableList
	{
	private:
		std::string m_directory;
		Globals::materialspec m_type;
		Shader* m_shader;

		void loadmodel(const std::string& filepath);		//ARGGHH i forgot to reference alot of string function inputs :////
		void processnode(aiNode* node, const aiScene* scene);
		CRenderable* parseRenderable(aiMesh* mesh, const aiScene* scene); //Does Mesh and Material Parsing together, creates renderable and pushes it into list.

	public:
		Model(std::string name, Globals::materialspec modelMatType, Shader* shader, const Transform& modelTrans = Transform{ 1.0f }) : m_type{ modelMatType }, m_shader{ shader } { 
			m_listroot = modelTrans ;
			loadmodel(name); 
		}
	};

}